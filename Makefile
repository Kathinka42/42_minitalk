# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 13:50:30 by kczichow          #+#    #+#              #
#    Updated: 2022/10/04 15:25:30 by kczichow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	server
BNAME		= 	client

SRCS		=	server.c \
				client.c
							
OBJS		= 	${SRCS:%.c=%.o}
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

LIBFT		=	./libft/libft.a
LIBFT_D		=	./libft/

# remove files and do not display error message/ stop if it does not
# exist (-f);
RM			= 	rm -f

all: 		$(NAME) $(BNAME)

# -L links libft library

$(NAME):	$(LIBFT) server.o
			$(CC) $(CFLAGS) -o $(NAME) server.o -L $(LIBFT_D) -l ft

$(BNAME):	$(LIBFT) client.o
			$(CC) $(CFLAGS) -o $(BNAME) client.o -L $(LIBFT_D) -l ft

# I<directory> Add the specified directory to the search path for include files.

%.o: %.c
	$(CC) $(CFLAGS) -I minitalk.h -I $(LIBFT_D)libft.h -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_D)
	
clean:
		$(RM) -f $(OBJS)
		make clean -C $(LIBFT_D)

fclean:		clean
			$(RM) $(NAME) $(BNAME)
			make fclean -C $(LIBFT_D)

re:	fclean	all

.PHONY:	all clean fclean re