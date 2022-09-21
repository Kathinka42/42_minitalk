The objective is to send any kind of message from client to server, using only two UNIX signals, respectively
SIGUSR1 and SIGUSR2. Each character can be translated into its bit equivalant, usually containing of 8
bits. the preferred method to complete this task is to use bitshifting.
#include <signal.h>

kill(pid, SIGUSR1);


#include <signal.h>

void my_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        printf("Received SIGUSR1!\n");
    }
}

signal(SIGUSR1, my_handler);

SYNOPSIS
     #include <unistd.h>

     pid_t
     getpid(void);

DESCRIPTION
     getpid() returns the process ID of the calling process.  The ID is guaranteed to be unique and is useful for constructing temporary file names.

#include <signal.h>

SIGNAL:

typedef void (*sig_t) (int);

     sig_t signal(int sig, sig_t func);

     The sig argument specifies which signal was received.  The func procedure allows a user to choose the action upon receipt of a signal.  To set the default action of the signal to occur as listed above, func should
     be SIG_DFL.  A SIG_DFL resets the default action.  To ignore the signal, func should be SIG_IGN.  This will cause subsequent instances of the signal to be ignored and pending instances to be discarded.  If SIG_IGN
     is not used, further occurrences of the signal are automatically blocked and func is called.

	 The handled signal is unblocked when the function returns and the process continues from where it left off when the signal occurred.  Unlike previous signal facilities, the handler func() remains installed after a
     signal has been delivered.

RETURN VALUES
     The previous action is returned on a successful call.  Otherwise, SIG_ERR is returned and the global variable errno is set to indicate the error.

SIGACTION:

to be preferred over signal.


 int sigaddset(sigset_t *set, int signo);
 int sigemptyset(sigset_t *set);

 DESCRIPTION
     These functions manipulate signal sets, stored in a sigset_t.  Either sigemptyset() or sigfillset() must be called for every object of type sigset_t before any other use of the object.

     The sigemptyset() function initializes a signal set to be empty.
     The sigaddset() function adds the specified signal signo to the signal set.

 usleep -- suspend thread execution for an interval measured in microseconds

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <unistd.h>

     int
     usleep(useconds_t microseconds);

DESCRIPTION
     The usleep() function suspends execution of the calling thread until either microseconds microseconds have elapsed or a signal is delivered to the thread and its action is to invoke a signal-catching function or to
     terminate the process.  System activity or limitations may lengthen the sleep by an indeterminate amount.

     This function is implemented using nanosleep(2) by pausing for microseconds microseconds or until a signal occurs.  Consequently, in this implementation, sleeping has no effect on the state of process timers, and
     there is no special handling for SIGALRM.  Also, this implementation does not put a limit on the value of microseconds (other than that limited by the size of the useconds_t type); some other platforms require it
     to be less than one million.

NOTE
     The usleep() function is obsolescent.  Use nanosleep(2) instead.

RETURN VALUES
     The usleep() function returns the value 0 if successful; otherwise the value -1 is returned and the global variable errno is set to indicate the error.

ERRORS
     The usleep() function will fail if:

     [EINTR]            A signal was delivered to the process and its action was to invoke a signal-catching function.