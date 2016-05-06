#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

int stepper = 1;
int skipper = 0;
unsigned int num = 2;
unsigned int max = UINT_MAX;

int prime_code();
int args(int argc, char *argv[]);
static void sig_handler(int sig_no, siginfo_t *siginfo, void *context);
int isprime(int num);

int main(int argc, char *argv[])
{	
	//www.linuxprogrammingblog.com/code-examples/sigaction
	struct sigaction new;

	memset(&new, '\0', sizeof(new));

	new.sa_sigaction = &sig_handler;

	new.sa_flags = SA_SIGINFO;

	if (sigaction(SIGINT, &new, NULL) < 0) {
		perror("SIGINT error.\n");
	}
	if (sigaction(SIGHUP, &new, NULL) < 0) {
		perror("SIGHUP error.\n");
	}
	if (sigaction(SIGUSR1, &new, NULL) < 0) {
		perror("SIGUSR1 error.\n");
	}
	if (sigaction(SIGUSR2, &new, NULL) < 0) {
		perror("SIGUSR2 error.\n");
	}

	if (args(argc, argv) == -1) {
		fprintf(stderr, "The arguments given are invalid\n");
		return 1;
	}

	prime_code();

	return EXIT_SUCCESS;
}

int args(int argc, char *argv[])
{
	//I got help with the opt args part from exsickness from
	//www.github.com/ExSickness/signals/blob/master/signaler.c
	int options = -1;
	while((options = getopt(argc, argv, "r:s:e:")) != -1) {
		char *end = NULL;
		
		switch(options)
		{
			//use this to specify the start of the next prime number then n
			case 's':
				//to check if we are starting from the beginning
				if(num != 2) {
					fprintf(stderr, "'s' or 'r' not compatible with each other\n");
					return -1;
				}
				num = strtoll(optarg, &end, 10);
				if (end == optarg) {
					fprintf(stderr, "Could not get number");
					return -1;
				}

				num += 1;
				break;
			//use this to emit decreasing values from number n
			case 'r':
				stepper *= -1;
				//to check if we are starting from the beginning
				if(num != 2) {
					fprintf(stderr, "'s' or 'r' not compatible with each other\n");
					return -1;
				}
				num = strtoll(optarg, &end, 10);
				if (end == optarg || num < 2) {
					fprintf(stderr, "Could not get number\n");
					return -1;
				}

				break;
			//use this to exit program if a prime number greater then n
			case 'e':
				max = strtoll(optarg, &end, 10);
				if(end == optarg) {
					fprintf(stderr, "Could not get specified end number\n");
					return -1;
				}
				break;
			default:
				fprintf(stderr, "No flags given\n");
				return -1;
		}
	}

	return 0;
}

int prime_code() 
{
	int prime = 0;
	//code to get prime numbers
	//https://www.daniweb.com/programming/software-development/threads/255212/
	//prime-number-using-sqrt
	while (num < max && num > 1) {
		while (!prime) {
			prime = isprime(num);

			if (prime) {
				if (skipper) {
					skipper = 0;
					num += stepper;
					prime = 0;
					continue;
				}
				printf("%d\n", num);
				prime = 0;
				break;
			}

			num += stepper;
			if (num >= max) {
				printf("You have reached the max number\n");
				break;
			}
			prime = 0;
		}
		sleep(1);
		num += stepper;
	}

	return 0;
}

static void sig_handler(int sig_no, siginfo_t *siginfo, void *context)
{
	printf("PID: %ld ; UID: %ld ; context: %p\n", (long)siginfo->si_pid, (long)siginfo->si_uid, context);

	//used to catch signals needed
	if (sig_no == SIGINT) {
		printf("Caught signal %d\n", sig_no);
		exit(sig_no);
	}
	else if(sig_no == SIGHUP) {
		printf("Caught signal %d\n", sig_no);
		num = 2;
	}
	else if(sig_no == SIGUSR1) {
		printf("Caught signal %d\n", sig_no);
		skipper = 1;
	}
	else if(sig_no == SIGUSR2) {
		printf("Caught signal %d\n", sig_no);
		stepper *= -1;
	}
	else {
		//break;
	}
}

//https://www.daniweb.com/programming/software-development/threads/255212/
//prime-number-using-sqrt
int isprime(int num) 
{
	int sq = (int) sqrt(num);

	int i;	

	for (i = 2; i <= sq; i++) {
		if(num % i == 0) {
			break;
		}
	}

	if (i <= sq) {
		return 0;
	}
	return 1;
}
