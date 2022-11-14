# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 02:52:38 by bcoenon           #+#    #+#              #
#    Updated: 2022/10/12 02:52:39 by bcoenon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *======== SOURCES ========*

SRCS_1	=	\
			

SRCSD	= srcs/

OBJS_1	= ${addprefix ${SRCSD}, ${SRCS_1:.c=.o}}

# *======== INCLUDES ========*

INC = -I ./includes
INC<lib> = -I <path_to_lib.h>

# *======== LIBS ========*

<lib>_DIR = <path_to_lib>
<lib>_FLAGS = -L$(<lib>_DIR) -l <name_of_lib>

# *======== OTHERS ========*

NAME_1	= <nom_du_projet>

CC		= clang
RM		= rm -rf

CFLAGS	= -g -Wall -Wextra -Werror

# *======== RULES ========*

all:		${NAME_1}

.c.o:	
		@clang ${CFLAGS} ${INC<lib>} ${INC} -c $< -o $(<:.c=.o)

${NAME_1}:	${OBJS_1}
					make -C ${<lib>_DIR}
			${CC} ${INC<lib>} ${INC} ${CFLAGS} ${OBJS_1} ${<lib>_FLAGS} -o ${NAME_1}

clean:
			${RM} ${OBJS_1}
					make clean -C ${<lib>_DIR}

fclean:		clean
			${RM} ${NAME_1}
					make fclean -C ${<lib>_DIR}

re:			fclean all

.PHONY:		all clean fclean re
