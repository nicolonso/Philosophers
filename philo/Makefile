# Makefile

#Standard
NAME				= philosophers


# Directories
HDR					= include/
SRC_DIR				= src/
OBJ_DIR				= obj/

# Compiler and CFlags 

CC					= cc
CFLAGS				= -Wall -Wextra -Werror -I$(HDR) -Iinclude
RM					= rm -f

# Source Files

PHILOSOPHERS_DIR	= $(SRC_DIR)main.c

PARSING_DIR			= $(SRC_DIR)Parsing/parsing.c	

# Concatenate all source files

SRCS 				= $(PHILOSOPHERS_DIR) $(PARSING_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules

all: 				$(NAME)

$(LIBFT):
					@make -C ./Lib

$(NAME): 			$(OBJ)
					@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
					@echo "philo compiled"

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)

fclean: 			clean
					@$(RM) $(NAME)
					
re: 				fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re