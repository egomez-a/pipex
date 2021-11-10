# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 14:37:38 by egomez-a          #+#    #+#              #
#    Updated: 2021/11/10 14:41:44 by egomez-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	pipex
SRCS_DIR	=	sources/
OBJ_DIR		= 	obj/

SRCS 		=	pipex.c

NOW			=	$(shell date +"%d-%m-%y %H:%M")

OBJS 		= 	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

CFLAGS 		= 	-Wall -Wextra -Werror #-g3 -fsanitize=address
DEBUGGING	= 	-g
CC 			= 	gcc
RM 			= 	rm -rf
NORM		= 	/usr/bin/norminette

NONE		=	'\033[0m'
GREEN		=	'\033[32m'
YELLOW		=	'\033[33m'
GRAY		=	'\033[2;37m'
CURSIVE		=	'\033[3m'
RED			=	'\033[0;31m'
ORANGE		=	'\033[0;33m'
BLUE		=	'\033[0;34m'
PURPLE		=	'\033[0;35m'
CYAN		=	'\033[0;36m'
LIGHTGRAY	=	'\033[0;37m'
DARKGRAY	=	'\033[1;30m'
LIGHTRED	=	'\033[1;31m'
LIGHTGREEN	=	'\033[1;32m'
YELLOW		=	'\033[1;33m'
LIGHTBLUE	=	'\033[1;34m'
LIGHTPURPLE	=	'\033[1;35m'
LIGHTCYAN	=	'\033[1;36m'
WHITE		=	'\033[1;37m'

all: $(NAME)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(DEBUGGING) $< -o $@

clean:
		@echo $(ORANGE) "========== CLEAN ==========" $(NONE)
		$(RM) $(OBJ_DIR)
		$(RM) $(OBJS)
		@echo $(GREEN) "=========== DONE ===========" $(NONE)
		
fclean: clean
		@echo $(ORANGE) "========== FCLEAN ==========" $(NONE)
		$(RM) $(NAME)
		@echo $(GREEN) "=========== DONE ===========" $(NONE)

re: fclean all

git: fclean
	@echo $(PURPLE) "===== PUSHING to GITHUB ===="  $(NONE)
	git add .
	git commit -m "Pipex - $(NOW)"
	git push origin master
	@echo $(GREEN)"=============== DONE ================"$(NONE)

norm: 
		$(NORM) $(SRC);

.PHONY: all, clean, fclean, re