/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:19:58 by kczichow          #+#    #+#             */
/*   Updated: 2022/09/26 17:37:58 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*	The main function in this file takes two arguments, the server PID and a
*	user defined string.
*?
// void	client_handler (int signal)
// {
// 	printf("Clienthandler");
// }
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

void	mt_transfer_signal(pid_t pid, char *str)
{
	int				bit_position;
	unsigned char	c;

	while (*str)
	{
		c = *str;
		bit_position = 0;
		while (bit_position < 8)
		{
			if (c << bit_position & 128)
			{
				printf("1");
				kill(pid, SIGUSR1);
			}
			else
			{
				printf("0");
				kill(pid, SIGUSR2);
			}
			usleep(200);
			bit_position++;
		}
	str++;
	}
	while (bit_position--)
		printf("0");
		kill(pid, SIGUSR2);
}

int	main(int argc, char *argv[])
{
	// struct sigaction	client;
	pid_t				server_pid;

	// client.sa_handler = &client_handler;
	server_pid = atoi(argv[1]);

	if (argc != 3)
		return (0);
	// behaviour of server function to be clarified

	mt_transfer_signal(server_pid, argv[2]);
}
