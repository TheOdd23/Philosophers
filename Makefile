NAME			=	philo
HEAD			=	includes/philo.h
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
SRCS			=	srcs/philo.c srcs/philo_utils.c srcs/init_philo.c srcs/do_actions.c
OBJS			=	${SRCS:.c=.o}
RM				=	rm -f

.c.o		:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) -pthread  -lpthread -o $(NAME) $(OBJS)
				echo Pret!

all			:	$(NAME)

clean		:	
				${RM} ${OBJS}

fclean		:	clean
				$(RM) $(NAME)
				echo Tout propre

re			:	fclean all

.PHONY		:	all clean fclean re
.SILENT		:	all clean fclean .c.o $(NAME) $(OBJS) $(CC) $(FLAGS)
