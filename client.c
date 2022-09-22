/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:19:58 by kczichow          #+#    #+#             */
/*   Updated: 2022/09/22 16:17:51 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*	Wie viele Argumente darf der client nehmen? Zaehlt ein Signal als Argument?
*	
*/

void	transfer_signal(int pid)
{
	kill(pid, SIGUSR1);
}

int	main(int argc, char *argv[])
{
	if (argc != 4)
		return (0);

	transfer_signal(getpid());
}