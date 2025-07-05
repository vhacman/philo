# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 11:23:24 by vhacman           #+#    #+#              #
#    Updated: 2025/07/05 19:15:12 by vhacman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME specifies the name of the compiled binary.
NAME	= philo

# Compiler and flags:
# CC defines the compiler to use.
# CFLAGS sets compilation flags:
# -Wall: enable all warnings
# -Wextra: enable extra warnings
# -Werror: treat warnings as errors
# -g: enable debugging symbols
# -Iincludes: add 'includes' directory to include path
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -Iincludes

SRC = \
	entry/main.c \
	parsing/parse_args.c \
	parsing/parse_utils.c \
	utils/libft_utils.c \
	clean/clean.c \
	initialization/initialization.c \
	initialization/init_mutexes_and_forks.c \
	threads/thread_utils.c \
	utils/fork_utils.c \
	utils/death_utils.c \
	utils/print_utils.c \
	utils/time_utils.c \
	routine/routine.c \
	routine/routine_utils.c \
	monitor/monitor.c \
	monitor/monitor_utils.c \

# OBJ defines the object files built from the source files.
OBJ		= $(SRC:.c=.o)

# RM defines the command to remove files.
RM		= rm -f

# 'all' is the default rule that builds the executable.
all: $(NAME)

# Rule to link all object files into the final binary.
# Also prints a success message.
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[0;32m[build] completed.\033[0m"

# Rule to compile .c files into .o files.
%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

# Rule to remove all object files.
clean:
	@$(RM) $(OBJ)
	@echo "\033[0;31m[clean] completed.\033[0m"

# Rule to remove object files and the binary.
fclean: clean
	@$(RM) $(NAME)
	@echo "\033[1;35m[fclean] completed.\033[0m"

# Rule to force full rebuild: fclean followed by all.
re: fclean all
	@echo "\033[1;34m[rebuild]Project rebuild from scratch\033[0m"

# Declare all custom rules that do not create files as .PHONY targets.
.PHONY: all clean fclean re
