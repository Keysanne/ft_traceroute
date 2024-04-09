NAME= ft_traceroute
COMPILER= gcc 
OBJS=	${FILES:.c=.o}
ARG_LIB= argparse_C/argparse
FILES=	main.c \
		utils.c 

all: ${NAME}

${NAME}: ${OBJS}
		make -C argparse_C
		${COMPILER} ${OBJS} ${ARG_LIB} -o ${NAME} -g -lm -pthread 

${OBJS}: ${FILES}
		${COMPILER} -c ${FILES} -g -lm -pthread

submodules:
		git submodule update --init

clean:
		make -C argparse_C clean
		rm -f ${OBJS}

fclean: clean
		make -C argparse_C fclean
		rm -f ${NAME}

re: fclean all