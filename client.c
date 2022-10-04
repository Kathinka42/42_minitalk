/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:19:58 by kczichow          #+#    #+#             */
/*   Updated: 2022/10/04 15:27:05 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*	MT_CLIENT_HANDLER
*	-------------------
*	The handle is called by sigaction in the main function, when the main
*	receives a signal.
*/

pid_t				g_server_pid;

void	mt_client_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (g_server_pid == info->si_pid && signal == SIGUSR1)
		ft_putstr_fd("server to client: message received\n", 1);
}

/*	MT_TRANSFER_SIGNAL
*	--------------------	
*	The function mt_transfer_signal encodes the character string into binary
*	and sends the single bits to the server function, using the signals SIGUSR1
*	(equals 1) and SIGUSR2 (equals 0).
*	The outer while loop loops through each character of the string. The inner
*	while loop encodes the charcater into binary, containing of 8 bits (ASCII):
*	Example: the character 'a' equals the decimal 97, which is in binary
*	0	1	1	0	0	0	0	1
*	128	64	32	16	8	4	2	1
*	The loop loops 8 times to look at each bit.
*	In the first loop, the function looks at the first bit (first position):
*	i equals 0 in this loop, so no bit shifting is done. Then the bitwise
*	operator & is applied to that bit:
*	0	1	1	0	0	0	0	1 (97)
*	1	0	0	0	0	0	0	0 (128)
*	---------------------------------- &
*	0	0	0	0	0	0	0	0
*	The result of the & operation is 0, so the if statement is not true and the
*	else statement sends SIGUSR2;
*	In the second loop, i equals 1, so the character binary is shifted to the
*	left by one bit. This operation results in the following:
*	1	1	0	0	0	0	1	0 (97 after bit shift to the left by 1);
*	1	0	0	0	0	0	0	0 (128)
*	----------------------------------	&
*	1	0	0	0	0	0	0	0
*	The result of the & operation is 1, so the if statement is true and sends
*	SIGUSR1 to the server function.
*	The encoding could also be done the other way round: starting with a bit
*	shift by seven bits and comparing to to decimal one, which only holds a
*	1 in the leftmost position in binary (00000001);
*	Once, the string is sent, a terminating 0 (00000000 in binary) is sent to
*	the server, to let it know that the transfer is finished.
*
*	Signals don't queue, therefore a microsecond break (usleep) is needed.
*	The kill() function sends a signal to a process or process group specified
*	by PID.
*/

void	mt_transfer_signal(char *str)
{
	int				bit;
	unsigned char	c;

	while (*str)
	{
		c = *str;
		bit = 0;
		while (bit < 8)
		{
			if (c << bit & 128)
				kill(g_server_pid, SIGUSR1);
			else
				kill(g_server_pid, SIGUSR2);
			usleep(200);
			bit++;
		}
	str++;
	}
	while (bit--)
	{
		kill(g_server_pid, SIGUSR2);
		usleep(200);
	}
}

/*	MAIN
*	-----------------
*	The main function in this file takes two arguments, the server PID and a
*	user defined string.
*/

int	main(int argc, char *argv[])
{
	struct sigaction			client;

	client.sa_sigaction = &mt_client_handler;
	g_server_pid = ft_atoi(argv[1]);
	if (argc != 3 || argv[2][0] == '\0' || g_server_pid < 1)
		return (0);
	sigaction(SIGUSR1, &client, NULL);
	mt_transfer_signal(argv[2]);
}
