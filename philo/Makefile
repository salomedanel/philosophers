DIRSRC = ./srcs/

DIRCINC = ./includes/

SRC =	main \
		init \
		routine \
		utils \
		check_end \
		free \

SRCS = $(addprefix ${DIRSRC}, $(addsuffix .c, ${SRC}))

OBJS = ${SRCS:.c=.o}

NAME = philo
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -pthread -g

.c.o:
	@${CC} ${CFLAGS} -c -I${DIRCINC} $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS}
	@echo "✅ philo created"

all: ${NAME}

clean:
	@${RM} ${OBJS}
	@echo "🧽 Directory is clean"

fclean:
	@${RM} ${OBJS}
	@${RM} ${NAME}
	@echo "🧹 Directory is fclean"

re : fclean all

.PHONY : all clean fclean re
