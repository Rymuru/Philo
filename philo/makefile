# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 02:52:38 by bcoenon           #+#    #+#              #
#    Updated: 2022/11/16 16:35:03 by bcoenon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *======== SOURCES ========*

SRCS_1	=	\
			philo.c			\
			philo_utils.c	\
			

SRCSD	= srcs/

OBJS_1	= ${addprefix ${SRCSD}, ${SRCS_1:.c=.o}}

# *======== INCLUDES ========*

INC = -I ./include

# *======== OTHERS ========*

NAME_1	= philo

CC		= clang
RM		= rm -rf

CFLAGS	= -g -Wall -Wextra -Werror

# *======== RULES ========*

all:		${NAME_1}

.c.o:	
		@clang ${CFLAGS} ${INC} -c $< -o $(<:.c=.o)

${NAME_1}:	${OBJS_1}
			${CC} ${INC} ${CFLAGS} ${OBJS_1} -o ${NAME_1}

clean:
			${RM} ${OBJS_1}

fclean:		clean
			${RM} ${NAME_1}

re:			fclean all

.PHONY:		all clean fclean re
