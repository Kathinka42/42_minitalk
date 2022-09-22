# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 13:50:30 by kczichow          #+#    #+#              #
#    Updated: 2022/09/22 16:28:12 by kczichow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS		=	server.c \
				client.c				

OBJS		= 	$(SRCS:%.c=%.o)

CC			=	gcc
#CFLAGS		=	-Wall -Wextra -Werror

#LIBFT		=	./libft/libft.a

RM			= 	rm -f

all:	server	client

server:	libft server.o
			$(CC) $(CFLAGS) -o $@ $< -Llibft -lft

client:	$(LIBFT) client.o
			$(CC) $(CFLAGS) -o $@ $< -Llibft -lft

libft:
	make -C libft
	
clean:
		@$(RM) -rf $(OBJS) \
		@$(RM) -rf $(OBJS_LIBFT);

fclean:		clean
			$(RM) server client
			$(RM) libft/libft.a

re:	fclean	all

.PHONY:	all clean fclean re