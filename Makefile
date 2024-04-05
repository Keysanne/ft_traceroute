NAME= ft_traceroute
COMPILER= gcc 
OBJS=	${FILES:.c=.o}
FILES=	main.c

all: ${NAME}

${NAME}: submodules ${OBJS}
		${COMPILER} ${OBJS} -o ${NAME} -g -lm -pthread

${OBJS}: ${FILES}
		${COMPILER} -c ${FILES} -g -lm -pthread

submodules:
		git submodule update --init

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all