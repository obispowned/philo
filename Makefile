# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/04 16:53:08 by agutierr          #+#    #+#              #
#    Updated: 2021/10/07 18:12:19 by agutierr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#				EJECUTABLE
NAME			=	philo

#				RUTAS
OBJ_PATH = ./objs
SRC_PATH = ./srcs

#				ARCHIVOS
SRCS			=	srcs/main.c srcs/free.c srcs/utils.c srcs/msg.c\
					srcs/fill_nd_parse.c srcs/timers.c srcs/create_threads.c\
					srcs/utils_rutine.c\
					
OBJS 			=	$(SRCS:.c=.o)

#				OBJS
OBJ = $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))

GCC 			=	gcc
CFLAGS			=	-Wall -Wall -Werror -O3
TFLAG			=	-pthread

#############################
RED 			= \033[0;31m
PURPLE			= \033[0;35m
GREEN			= \033[1;32m
RESET			= \033[0m
#############################

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@$(GCC) -g $(CFLAGS) -o $@  -c $^

all: $(NAME)

%.o: %.c
	$(GCC) $(CFLAGS) -o $@ -c $^

$(NAME): $(OBJS)
	@echo "${PURPLE} Iniciando Compilacion ...${RESET}"
	$(GCC) $(CFLAGS) $(TFLAG) $(OBJS) -o $(NAME)
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
