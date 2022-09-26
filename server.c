/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:20:50 by kczichow          #+#    #+#             */
/*   Updated: 2022/09/26 17:35:06 by kczichow         ###   ########.fr       */
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
    static unsigned char	character;
	int						i;
	
	character = 0;
	ft_putstr_fd("TEST", 1);
	if (signal == SIGUSR1)
	{
		character 
	}
}

/*	Sigaction is to be preferred over the signal function according to the
*	manual, because the behaviour of signal varies across UNIX versions and
*	has varied across Linux versions as well.
*	To use the sigaction function, you have to create a struct.
*	The sigaction function reacts, whenever a specific signal is sent and calls
*	the handler, to which the sigaction fucntion is bound.
*	The signals SIGUSR1 and SIGUSR2 are not used by Linux for generic process
*	operations and can be used by the user.
*/

int	main()
{
	struct sigaction	server;
	
	server.sa_handler = &signal_handler;
	//server.sa_flags = SA_RESTART; // needed in combination with scanf;

	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &server, NULL);
	sigaction(SIGUSR2, &server, NULL);
	sleep(100);
	return (0);
}