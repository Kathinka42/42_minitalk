/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:20:50 by kczichow          #+#    #+#             */
/*   Updated: 2022/09/27 10:05:57 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*	With signals you cannot send any data, just communicate between processes
*	i.e. send notifications. The kill function sends the signal.
*/


/*	MT_SIGNAL_HANDLER
*	--------------------
*	The function is called by sigaction, whenever the server receives a signal
*	from the client.
*	Signal handlers run asyncronously, which means they can interrupt the code
*	at any point. Therefore you can only use signal-save functions, i.e. write.
*	The manual lists save functions.
*	https://www.youtube.com/watch?v=PErrlOx3LYE
*/

void mt_signal_handler(int signal)
{
    static unsigned char	c = 0;
	static int				bit = 0;
	
	// c = 0;
	// bit	= 0;
	if (bit < 8 && signal == SIGUSR1)
		c += 128 >> bit;
	bit++; 
	if (bit == 8)
	{
		write(1, &c, 1);
		// ft_putchar_fd(c, 1);
		bit = 0;
		c = 0;
	}
	if (c == '\0')
		{
			
		}
}

/*	https://linuxhint.com/c-sigaction-function-usage/
*	Sigaction is to be preferred over the signal function according to the
*	manual, because the behaviour of signal varies across UNIX versions and
*	has varied across Linux versions as well.
*	To use the sigaction function, you have to create a struct.
*	The sigaction function reacts, whenever a specific signal is sent and calls
*	the handler, to which the sigaction function is bound.
*	The signals SIGUSR1 and SIGUSR2 are not used by Linux for generic process
*	operations and can be used by the user.
*	The signal() function does not block other signals when the current
*	handler’s execution is under process. At the same time, the sigaction
*	function can block other signals until the current handler has returned.
*/

int	main()
{
	struct sigaction	server;
	
	server.sa_handler = &mt_signal_handler;
	server.sa_flags = SA_RESTART;
	// server.sa_flags = SA_SIGINFO;

	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &server, NULL);
	sigaction(SIGUSR2, &server, NULL);
	while (1)
		pause();
	return (0);
}

//  static unsigned char	c = 0;
// 	static int				bit = 7;
	
// 	// c = 0;
// 	// bit	= 7;
// 	if (signal == SIGUSR1)
// 		c += 1 << bit;
// 	bit--; 
// 	if (bit < 0)
// 	{
// 		write(1, &c, 1);
// 		// ft_putchar_fd(c, 1);
// 		bit = 7;
// 		c = 0;
// 	}