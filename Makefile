NAME = libftprintf.a

SRCS = srcs/printf.c srcs/ft_utils.c srcs/ft_flags.c

D_LIBFT = libft/
D_SRCS = srcs/
INCLUDES = -Iincludes/ -Ilibft/

OBJS := ${patsubst %.c, %.o, ${SRCS}}

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all :		$(NAME)

$(NAME) :	${OBJS}
	$(MAKE) all -C $(D_LIBFT)
	cp libft/libft.a $(NAME)
	ar -crs ${NAME} ${OBJS}

clean :
	$(MAKE) clean -C $(D_LIBFT)
	rm -f ${OBJS}

fclean :	clean
	$(MAKE) fclean -C $(D_LIBFT)
	rm -f ${NAME}

re :		fclean all

%.o : %.c
	${CC} ${CFLAGS} $(INCLUDES) -c $< -o $@

.PHONY: all clean fclean re test
