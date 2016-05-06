#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int stepper = 1;
int skipper = 0;
unsigned int num = 2;
unsigned int max = UINT_MAX;

int prime_code();

static void sig_handler(int sig_no, siginfo_t *siginfo, void *context)
{
	printf("PID: %ld ; UID: %ld ; context: %p\n", (long)siginfo->si_pid, (long)siginfo->si_uid, context);

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

	prime_code();

	return EXIT_SUCCESS;
}

int prime_code() 
{
	int prime = 0;

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

