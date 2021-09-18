# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/04 16:53:08 by agutierr          #+#    #+#              #
#    Updated: 2021/09/18 19:22:49 by agutierr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
SRCS			=	main.c\
					srcs/free.c\
					srcs/utils.c\
					srcs/msg.c\
					srcs/fill_nd_parse.c\
					srcs/timers.c\
					srcs/create_threads.c\
					srcs/utils_rutine.c\

OBJS 			=	$(SRCS:.c=.o)


GCC 			=	gcc
CFLAGS			=	-Wall -Wall -Werror -O3

#############################
RED 			= \033[0;31m
PURPLE			= \033[0;35m
GREEN			= \033[1;32m
RESET			= \033[0m
#############################


all: $(NAME)

%.o: %.c
	$(GCC) $(CFLAGS) -o $@ -c $^

$(NAME): $(OBJS)
	@echo "${PURPLE}  Iniciando Compilacion ...${RESET}"
	$(GCC) $(CFLAGS) -pthread $(OBJS) -o $(NAME)
	@echo "${GREEN}[.oOo.oOo.oOo.oOo.]"
	@echo "[ C O M P I L A O ]"
	@echo "[.oOo.oOo.oOo.oOo.]${RESET}"

norminette:
	norminette main.c srcs/* headers/*

fclean: clean
	@echo "${RED}  Limpiando ejecutable ... ${RESET}"
	rm -f $(NAME)

clean:
	@echo "${RED}  Limpiando OBJs ... ${RESET}"
	$(RM) $(OBJS)

re: fclean all

.PHONY: clean all
