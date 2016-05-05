#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_handler(int sig_no)
{
	if (sig_no == SIGINT) {
		printf("Caught signal %d\n", sig_no);
		exit(signum);
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
	
	while(1) {
		printf("Program\n");
		sleep(1);
	}
	return EXIT_SUCCESS;
}
