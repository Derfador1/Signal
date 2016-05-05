#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

void sig_handler(int sig_no)
{
	if (sig_no == SIGINT) {
		printf("Caught signal %d\n", sig_no);
		exit(sig_no);
	}
	else if(sig_no == SIGHUP) {
		printf("Caught signal %d\n", sig_no);
	}
}

int main(int argc, char *argv[])
{
	signal(SIGINT, sig_handler);

	signal(SIGHUP, sig_handler);

	signal(SIGUSR1, sig_handler);

	signal(SIGUSR2, sig_handler);
	
	unsigned int *prime = calloc(SHRT_MAX, sizeof(*prime));

	if(!prime) {
		perror("Error: malloc failed.\n");
		exit(1);
	}

	//code found on stackoverflow.com/questions/4809051/prime-number-algorithm
	//might change this to a different type
	for(unsigned int j = 0, i = 2; i < SHRT_MAX; i++, j++) {
		prime[j] = i;
	}

	for(unsigned int i = 0; i < SHRT_MAX; i++) {
		int num = prime[i];

		if(num != 0) {
			for(unsigned int j = i + 1; j < SHRT_MAX; j++) {
				if( (prime[j]%num == 0) ) {
					prime[j] = 0;
				}
			}
		}
	}

	for(unsigned int i = 0; i < SHRT_MAX; i++) {
		if(prime[i] != 0) {
			sleep(1);
			printf("%d\n", prime[i]);
		}

	}

	free(prime);

	return EXIT_SUCCESS;
}
