NAME= argparse
COMPILER= gcc 
OBJS=	${FILES:.c=.o}
FILES=	arg.c	 \
		utils.c	  \
		argparse.c \
		arg_start.c \
		libft.c

all: ${NAME}

${NAME}: ${OBJS}
		ar rcs ${NAME} ${OBJS} 

${OBJS}: ${FILES}
		${COMPILER} -c ${FILES}

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all