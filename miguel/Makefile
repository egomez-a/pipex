# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 19:30:14 by mangarci          #+#    #+#              #
#    Updated: 2021/11/15 22:52:36 by mangarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LM = -lm 
RM = rm -rfv
DEBUG_FLAG = -g 
SRCS_DIR:=srcs/
SRCS := $(wildcard $(SRCS_DIR)*.c)
OBJS = $(SRCS:%.c=%.o)
LIBFT_PATH = lib/libft
LIBFT_LIB:= -L$(LIBFT_PATH) $(LIBFT_PATH)/libft.a

all:	libft $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LM) $(LIBFT_LIB)

$(%.o): $(%.c)
				$(CC) -c $^-o $@
				@echo "Creating objects"

libft:
				make -C $(LIBFT_PATH)
				
debug:	$(OBJS)
		$(CC) $(DEBUG_FLAG) $(LM) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
				@echo "Removing objects"
				$(RM) $(OBJS)
				
fclean:
				make clean
				cd lib/libft && $(MAKE) fclean
				$(RM) $(NAME)

re:
		make fclean all
		@echo "All files has been deleted and recompiled"
		
.PHONY: clean fclean all re objects debug bonus libft
