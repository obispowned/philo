# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/19 18:57:47 by agutierr          #+#    #+#              #
#    Updated: 2021/07/20 15:47:47 by agutierr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
SRCS			=	main.c\
					srcs/free.c\
					srcs/utils.c\
					srcs/msg.c\
					srcs/fill_nd_parse.c\

OBJS 			=	$(SRCS:.c=.o)

GCC 			=	gcc
CFLAGS			=	#-Wall -Wall -Werror

#############################
detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
ifeq ($(detected_OS),Darwin)
    INCLUDE = -I headers/philo.h
endif
ifeq ($(detected_OS),Linux)
    INCLUDE = -I headers/philo.h headers/linux.h
endif

#############################
RED 			= \033[0;31m
PURPLE			= \033[0;35m
GREEN			= \033[1;32m
RESET			= \033[0m
#############################

all: $(NAME)

%.o: %.c
	$(GCC) $(CFLAGS) $(INCLUDES) -o $@ -c $^

$(NAME): $(OBJS)
	@echo "${PURPLE}  Iniciando Compilacion ...${RESET}"
	$(GCC) $(CFLAGS) $(OBJS) -o $(NAME)
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
