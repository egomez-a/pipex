# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 14:37:38 by egomez-a          #+#    #+#              #
#    Updated: 2021/11/17 13:38:48 by egomez-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	pipex
SRCS_DIR	=	sources/
OBJ_DIR		= 	obj/
INC_DIR		= 	include/

SRCS 		=	pipex.c \
				lib/ft_putendl_fd.c \
				lib/ft_split.c \
				lib/ft_putstr_fd.c \
				lib/ft_strlcpy.c \
				lib/ft_strlen.c

NOW			=	$(shell date +"%d-%m-%y %H:%M")

OBJS 		= 	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

CFLAGS 		= 	-Wall -Wextra -Werror
DEBUGGING	= 	-g
LFLAGS		= 	-I$(INC_DIR)
CC 			= 	gcc
RM 			= 	rm -rf			#-f es para evitar que borre si no hay nada que borrar
NORM		= 	/usr/bin/norminette

NONE		=	'\033[0m'
GREEN		=	'\033[32m'
YELLOW		=	'\033[0;33m'
BLUE		=	'\033[0;34m'
PURPLE		=	'\033[0;35m'

all: $(NAME)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(DEBUGGING) $(LFLAGS) $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS)
	@echo $(BLUE) "======== COMPILED  ==========" $(NONE)

clean:
		@echo $(YELLOW) "========== CLEAN ==========" $(NONE)
		$(RM) $(OBJ_DIR)
		$(RM) $(OBJS)
		@echo $(GREEN) "=========== DONE ===========" $(NONE)
		
fclean: clean
		@echo $(PURPLE) "========== FCLEAN ==========" $(NONE)
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