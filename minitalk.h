/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:18:54 by kczichow          #+#    #+#             */
/*   Updated: 2022/09/21 11:28:20 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>
#include <unistd.h>

struct  sigaction
{
	union __sigaction_u __sigaction_u;  /* signal handler */
    sigset_t sa_mask;               /* signal mask to apply */
    int     sa_flags;               /* see signal options below */
};

union __sigaction_u {
    void    (*__sa_handler)(int);
    void    (*__sa_sigaction)(int, siginfo_t *, void *);
};

     #define sa_handler      __sigaction_u.__sa_handler
     #define sa_sigaction    __sigaction_u.__sa_sigaction


     int
     sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact);

#endif
