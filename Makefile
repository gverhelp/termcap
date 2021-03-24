NAME 			= test
LIBFT_PATH 		= ./libft
SRCS 			= main.c \
					what_key.c \
					utils_termcap.c

OBJS			= ${SRCS:.c=.o}
INCLUDE 		= include/test.h
#FOLDER			= srcs
LIBFT 			= libft
CC				= gcc -Wall -Wextra -Werror -g  #-fsanitize=address
RM				= rm -f
LIBFLAGS 		= -I ./libft -L ./libft -L . ./libft/*.c 
# -I Add the directory dir to the list of directories to be searched for header files
# -L Searches the library when linking

all:			libft_all ${NAME}
$(NAME):		${OBJS} 
				@$(CC) $(LIBFLAGS) libft/libft.a -I./ $(OBJS) -ltermcap -o $@ 
clean:			libft_clean
				@${RM} ${OBJS}
fclean:			libft_fclean clean
				@${RM} ${NAME} ./.minishell_history.txt
re:				fclean all

# In this last section we make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command
libft_all:
	make -C $(LIBFT_PATH) all

libft_clean:
	make -C $(LIBFT_PATH) clean

libft_fclean:
	make -C $(LIBFT_PATH) fclean
	$(RM) libft/libft.a

.PHONY: all fclean clean re