# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 17:18:22 by vtavitia          #+#    #+#              #
#    Updated: 2023/06/14 12:56:20 by vtavitia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BONUS_NAME = pipex_bonus

GREEN = \033[3;32m
RED = \033[3;31m
RESET = \033[0m

SRCS = main.c\
		find_path.c\
		ft_split.c\
		pipex_utils.c\
		check_commands.c\
		free_all.c

BONUS_SRCS = pipex_bonus.c\
		find_path.c\
		ft_split.c\
		pipex_utils.c\
		here_doc.c\
		check_commands.c\
		set_files.c\
		free_all.c

SRCPATH = mandatory/
OBJPATH = objects/

BONUS_SRCPATH = bonus_sources/
BONUS_OBJPATH = bonus_objects/

SOURCES = $(addprefix $(SRCPATH), $(SRCS))
OBJECTS = $(addprefix $(OBJPATH), $(SRCS:.c=.o))

BONUS_SOURCES = $(addprefix $(BONUS_SRCPATH), $(BONUS_SRCS))
BONUS_OBJECTS = $(addprefix $(BONUS_OBJPATH), $(BONUS_SRCS:.c=.o))

CC = cc

FLAGS = -Wall -Werror -Wextra

HEADER = includes/pipex.h
BONUS_HEADER = includes/pipex_bonus.h

MANDATORY = @echo "$(GREEN)Creating mandatory Pipex file!$(RESET)"
BONUSTEXT = @echo "$(GREEN)Creating bonus Pipex file!$(RESET)"
REMOVETEXT = @echo "$(RED)CLEANING UP!$(RESET)"

all: $(OBJPATH) $(NAME)

$(OBJPATH)%.o: $(SRCPATH)%.c
	@$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

$(OBJPATH):
	@mkdir $(OBJPATH)
	
$(NAME):  $(OBJECTS) 
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS)
	$(MANDATORY)

bonus: $(BONUS_OBJPATH) $(BONUS_NAME)

$(BONUS_OBJPATH)%.o: $(BONUS_SRCPATH)%.c
	@$(CC) $(CFLAGS) -I $(BONUS_HEADER) -c $< -o $@

$(BONUS_OBJPATH):
	@mkdir $(BONUS_OBJPATH)
	
$(BONUS_NAME):  $(BONUS_OBJECTS) 
	@$(CC) $(FLAGS) -o $(BONUS_NAME) $(BONUS_OBJECTS)
	$(BONUSTEXT)

clean:
	@rm -rf $(OBJPATH)
	@rm -rf $(BONUS_OBJPATH)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	$(REMOVETEXT)

re: fclean all

.PHONY: all clean fclean re
