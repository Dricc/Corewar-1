NAME = ../corewar

FLAGS = -Wall -Werror -Wextra -g

SRCS =	vm_main.c \
		op.c \
		vm_pars_param.c \
		vm_pars_param2.c \
		vm_data.c \
		vm_read_champ.c \
		vm_init_map.c \
		vm_fight.c \
		vm_op/vm_live.c \
		vm_op/vm_get_param.c \
		vm_op/vm_add.c \
		vm_op/vm_and.c \
		vm_op/vm_check_param.c \
		vm_op/vm_fork.c \
		vm_op/vm_get_nb_octet.c \
		vm_op/vm_ld.c \
		vm_op/vm_ldi.c \
		vm_op/vm_lld.c \
		vm_op/vm_lldi.c \
		vm_op/vm_or.c \
		vm_op/vm_st.c \
		vm_op/vm_sti.c \
		vm_op/vm_sub.c \
		vm_op/vm_xor.c \
		vm_op/vm_zjmp.c \
		vm_op/vm_aff.c \
		vm_op/vm_lfork.c \
		vm_op/vm_verb.c \
		vm_ncurses.c \
		vm_ncurses_print.c \
		vm_ncurses_print_process.c \
		vm_exec_op.c\
		ft_say.c\
		vm_print_winner.c

INCLUDES = -I ../libft

DEP = Makefile vm_header.h

LIB = -L ../libft

OBJS = $(SRCS:.c=.o)

all: mylibft $(NAME)

$(NAME): $(OBJS)
	gcc $(LIB) $(FLAGS) $(OBJS) -o $(NAME) -lft -lncurses

mylibft:
	make -C ../libft/

%.o: %.c $(DEP)
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C ../libft/ fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.NOTPARELLEL: all clean fclean re
