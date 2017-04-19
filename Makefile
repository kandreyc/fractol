#[----PROJECT NAME----]#
NAME		=	fractol

#[----PATH TO HEADERS----]#
FRL_H		=	./includes/

#[---COMPILE---]#
ACT			=	gcc
FLAGS		=	-Wall -Wextra -Werror -O2

#[----ATTACH THE HEADERS----]#
GCC_MLX_H	=	-lmlx -framework OpenGL -framework AppKit
GCC_FRL_H	=	-I $(FRL_H)
GCC_ALL_H	=	$(GCC_FRL_H) $(GCC_MLX_H)

#[----FDF SOURCES----]#
SRC_FRL_C		=	./functions/main.c					\
					./functions/pixel.c					\
					./functions/control.c				\
					./functions/render.c				\
					./functions/straight.c				\
					./functions/fractol.c				\
					./functions/error.c					\
					./functions/tree.c					\
					./functions/structure_fill.c

SRC_FRL_O		=	./functions/main.o					\
					./functions/pixel.o					\
					./functions/control.o				\
					./functions/render.o				\
					./functions/straight.o				\
					./functions/fractol.o				\
					./functions/error.o					\
					./functions/tree.o					\
					./functions/structure_fill.o

#[----COLORS]----#
GREEN			=	\033[32m
DEFAULT			=	\033[39m


all: $(NAME)

$(NAME): $(SRC_FRL_O)
	@ $(ACT) $(FLAGS) $(GCC_ALL_H) $(SRC_FRL_O) -o $(NAME)
	@ echo "$(GREEN)[fractol]$(DEFAULT)"

%.o : %.c $(FRL_H)
	@ $(ACT) $(FLAGS) -c -o $@ $<

norm:
	norminette -R CheckForbiddenSourceHeader $(SRC_FRL_C) $(FRL_H)fractol.h
	@ echo "$(GREEN)[norminette]$(DEFAULT)"

clean:
	@ rm -f $(SRC_FRL_O)
	@ echo "$(GREEN)[clean]$(DEFAULT)"

fclean: clean
	@ rm -f $(NAME)
	@ echo "$(GREEN)[fclean]$(DEFAULT)"

re: fclean all
