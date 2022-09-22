/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:20:50 by kczichow          #+#    #+#             */
/*   Updated: 2022/09/22 15:45:57 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*	With signals you cannot send any data, just communicate between processes
*	i.e. send notifications. The kill function sends the signal.
*/


/*	Signal handlers run asyncronously, which means they can interrupt the code
*	at any point. Therefore you can only use signal-save functions, i.e. write.
*	The manual lists save functions.
*	https://www.youtube.com/watch?v=PErrlOx3LYE
*/

void signal_handler(int signal)
{
    write(STDOUT_FILENO, "Seg Fault", 20);
}

/*	Sigaction is to be preferred over the signal function according to the
*	manual, because the behavious of signal varies across UNIX versions and
*	has varied across Linux versions as well.
*	To use the sigaction function, you have to create a struct.
*	The sigaction function reacts, whenever a specific signal is sent and calls
*	the handler, to which the sigaction fucntion is bound.
*	The signals SIGUSR1 and SIGUSR2 are not used by Linux for generic process
*	operations and can be used by the user.
*/

int	main()
{
	struct sigaction	sa;
	
	ft_putnbr_fd(getpid(), 1);

	sa.sa_handler = &signal_handler;
	//sa.sa_flags = SA_RESTART; // needed in combination with scanf;

	sigaction(SIGUSR1, &sa, NULL);


	// size_t pid;
	// int	x;
	// int	y;
	// x = 'a';
	// y = x << 1;

	// printf("x = %c\n", x);
	// printf("y = %c\n", y);


	//pid_t getpid(void);
	// pid = getpid();
	//printf("%zu", pid);
	// kill(pid, SIGUSR1);
	// kill(pid, SIGUSR2);
	// signal(SIGINT, signal_handler);
	// signal(SIGTERM, signal_handler);
	// while (1)
	// {
	// 	printf("I won't die %d\n", getpid());
	// }
	// signal(SIGUSR2, signal_handler);
	return (0);
	
	return (0);
}