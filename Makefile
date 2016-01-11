# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/16 15:08:59 by rbernand          #+#    #+#              #
#    Updated: 2016/01/11 15:30:36 by rbernand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=Corewar
ASM=asm
# VM=vm
CC=	cc
FLAGS=-Wall -Wextra -Werror -g -Ofast
LIBFT=libft/
LIBVECT=libvect/
LIBMLX11=minilibx/
LIBMLXOSX=minilibxosx/
LIBOPT=libopt/
INCLUDES=include/
DIROBJ=obj/
DIRLIB=lib/
DIRSRC=src/
DIRBIN=bin/
DIRCOMMON=common/
DIRVM=vm/
DIRASM=asm/
SRC_COMMON=op.c \
			list_new.c \
			list_push_front.c \
			list_push_back.c \
			list_iter.c \
			list_back.c
SRC_ASM=main.c \
		parse.c \
		get_octet_code.c \
		is_correct_label.c \
		add_instruction.c \
		put_hexa.c \
		get_op_by_id.c \
		store_params.c \
		link_labels.c \
		write_header.c
SRC_VM=main.c
OBJ_ASM=$(SRC_ASM:%.c=$(DIROBJ)$(DIRASM)%.o)
OBJ_COMMON=$(SRC_COMMON:%.c=$(DIROBJ)$(DIRCOMMON)%.o)

all: init $(NAME) end

init:
	@mkdir -p $(DIRBIN)
	@mkdir -p $(DIRLIB)
	@mkdir -p $(DIROBJ)
	@mkdir -p $(DIROBJ)$(DIRASM)
	@mkdir -p $(DIROBJ)$(DIRCOMMON)
	@mkdir -p $(DIROBJ)$(DIRVM)
	@git submodule init
	@git submodule update
	@make -s -C $(LIBFT)
	@cd $(DIRLIB) && ln -f ../$(LIBFT)/libft.a .
	@ln -f $(LIBFT)includes/libft.h $(INCLUDES)/

end:
	@printf "\033[2K\033[1;36m%-20s\033[0;32m[Ready]\033[0m\n" $(NAME)

$(NAME): $(OBJ_COMMON) $(ASM) $(VM)

$(ASM): $(OBJ_ASM) $(OBJ_COMMON)
	@printf "\033[2aKCompiling %s\r" $(NAME)
	@$(CC) $(FLAGS) -o $(DIRBIN)$@ $^ -I$(INCLUDES) -L$(DIRLIB) -lft
	@ln -f $(DIRBIN)$@ $@

$(DIROBJ)$(DIRASM)%.o: $(DIRSRC)$(DIRASM)%.c
	@printf "\r\033[2KLinking %s" $@
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES)

$(DIROBJ)$(DIRCOMMON)%.o: $(DIRSRC)$(DIRCOMMON)%.c
	@printf "\r\033[2KLinking %s" $@
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES)

$(DIROBJ)$(DIRVM)%.o: $(DIRSRC)$(DIRVM)%.c
	@printf "\r\033[2KLinking %s" $@
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(ASM)
	@rm -rf $(VM)
	@rm -rf $(DIROBJ)
	@rm -rf $(DIRLIB)

re: fclean all
