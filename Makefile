## Makefile for generic Makefile in /home/hegedu_e/Projets/Generic
##
## Made by Eric Hegedus
## Login   <hegedu_e@epitech.net>
##
## Started on  Fri Oct 25 11:54:03 2013 Eric Hegedus
## Last update Thu Feb 26 11:08:11 2015 hegedu_e
##

NAME		=	avm

SRC		=	src/main.cpp \
			src/Type.cpp \
			src/InputOutput.cpp \
			src/CentralProcessingUnit.cpp \
			src/Chipset.cpp \
			src/OperandCreator.cpp

OBJ_MAINS	=	$(MAINS:src/%.cpp=build/%.o)

OBJ		=	$(SRC:src/%.cpp=build/%.o)

CFLAGS		=	-Iinclude $(if $(DEBUG), -ggdb3, -Wall -Werror -Wextra)

ECHO		=	echo -e

RM_FORMAT	=	$(ECHO) "\033[31m[RM]\t\t\033[0m"

CC_FORMAT	=	$(ECHO) "\033[32m[CC]"$(MODE)"\t\033[0m"

LD_FORMAT	=	$(ECHO) "\033[33m[LD]\t\t\033[0m"

DONE_FORMAT	=	$(ECHO) "\033[36m[DONE]  \t\033[0m"

ifeq ($(DEBUG), 1)
	MODE	=	"\033[35m[DEBUG]"
else
	MODE	=	"\033[35m[NORMAL]"
endif

$(NAME)		:	$(OBJ)
			@clang++ -o $(NAME) $(OBJ) $(LDFLAGS)
			@$(LD_FORMAT) $^
			@$(DONE_FORMAT) $@

build/%.o	:	src/%.cpp
			@mkdir -pv build
			@clang++ -c $(CFLAGS) $^ -o $@
			@$(CC_FORMAT) $^ "->" $@

all		:	$(NAME)

clean		:
			@rm -f $(OBJ_MAINS)
			@$(RM_FORMAT) $(OBJ_MAINS) | sed 's/o /o\n\t\t /g'
			@rm -f $(OBJ)
			@$(RM_FORMAT) $(OBJ) | sed 's/o /o\n\t\t /g'

fclean		:	clean
			@rm -f $(NAMES)
			@$(RM_FORMAT) $(NAMES)
			@rm -f $(NAME)
			@$(RM_FORMAT) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
