#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        printf("Received SIGUSR1!\n");
    }
}

int main(int argc, char *argv[])
{
	size_t pid;
	//pid_t getpid(void);
	pid = getpid();
	//printf("%zu", pid);
	kill(pid, SIGUSR1);
	kill(pid, SIGUSR2);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	return (0);
}