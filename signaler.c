#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

int stepper = 1;
int skipper = 0;
unsigned int num = 2;
unsigned int max = UINT_MAX;

void sig_handler(int sig_no)
{
	/*
	if (sig_no == SIGINT) {
		printf("Caught signal %d\n", sig_no);
		exit(sig_no);
	}
	else if(sig_no == SIGHUP) {
		printf("Caught signal %d\n", sig_no);
	}
	*/
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

	/*
	signal(SIGINT, sig_handler);

	signal(SIGHUP, sig_handler);

	signal(SIGUSR1, sig_handler);

	signal(SIGUSR2, sig_handler);
	*/

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

	return EXIT_SUCCESS;
}
