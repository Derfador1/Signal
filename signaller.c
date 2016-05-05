#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_handler(int sig_no)
{
	if (sig_no == SIGINT) {
			print("Caught signal %d\n", sig_no);
			exit(sig_no);
	}
}

int main(int argc, char *argv[])
{
	signal(SIGINT, sig_handler);
	
	while(l) {
			printf("Program\n");
			sleep(l);
	}
	return EXIT_SUCCESS;
}
