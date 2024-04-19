NAME= ft_traceroute
COMPILER= gcc 
OBJS=	${FILES:.c=.o}
ARG_LIB= argparse/argparse
FILES=	main.c  \
		utils.c  \
		options.c \
		check_ip.c 

all: ${NAME}

${NAME}: ${OBJS}
		make -C argparse
		${COMPILER} ${OBJS} ${ARG_LIB} -o ${NAME} -g3 -lm -pthread 

${OBJS}: ${FILES}
		${COMPILER} -c ${FILES} -g3 -lm -pthread

clean:
		make -C argparse clean
		rm -f ${OBJS}

fclean: clean
		make -C argparse fclean
		rm -f ${NAME}

re: fclean all