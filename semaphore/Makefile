# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 10:32:04 by vvoronts          #+#    #+#              #
#    Updated: 2025/05/21 12:23:02 by vvoronts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -Wunreachable-code -g -MMD -MF
RM					=	rm -rf

# Name of the output library
NAME				=	philo

# Source directories
VPATH				=	\
						./src/:\
						./src/init:\
						./src/simulate:\
						./src/destroy:\
						./utils/:\

# Include directories
INCLUDE_DIRS		=	\
						./include \

# Source files
SRC 				=	\
						main.c \
						validator.c \
						initer.c \
						eat.c \
						monitor.c \
						routine.c \
						simulator.c \
						sleep.c \
						think.c \
						destroyer.c \
						\
						atol.c \
						exit.c \
						print.c \
						strlen.c \
						time.c \
						mutex.c \
						\

# Object and Dependency files
OBJ					=	$(SRC:%.c=obj/%.o)
DEP					=	$(SRC:%.c=dep/%.d)

INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))

# Make flags
MFLAGS				=	 --no-print-directory -C

# Build all targets
all: lib $(NAME)

# Link mandatory object files
$(NAME): $(OBJ)
	@echo "$(YELLOW)Building $(NAME)..."
	@$(CC) $(OBJ) -o $@
	@echo "$(GREEN)$(NAME) has been built"

# Compile mandatory object files
obj/%.o: %.c | obj_dir dep_dir
	@$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@ && printf "$(GRAY)Compiling: $(RESET)$(notdir $< \n)"

# Create mandatory object directories
obj_dir:
	@mkdir -p obj

# Create mandatory dependency directories
dep_dir:
	@mkdir -p dep

# Clean build files
clean:
	@echo "$(YELLOW)Cleaning $(NAME)..."
	@$(RM) obj
	@$(RM) dep
	@echo "$(RED)$(NAME) has been cleaned$(RESET)"

# Clean build files and executables
fclean: clean
	@$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re lib
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)

# set colors
RED					= 	\033[0;31m
GREEN				= 	\033[0;32m
YELLOW				= 	\033[0;33m
GRAY				= 	\033[0;37m
RESET				= 	\033[0m
