NAME = PmergeMe
SRC = main.cpp PmergeMe.cpp
SRCDIR = ./srcs/
SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJDIR = ./obj/
OBJS = $(addprefix $(OBJDIR), $(SRC:%.cpp=%.o))
INC = -I ./includes/
CXX = c++
RM = rm -rf
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all : $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)

clean :
	$(RM) $(OBJDIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

debug : CXXFLAGS += -D DEBUG
debug : re

test :
	@ echo "-- ./$(NAME) --"
	@-./$(NAME)

	@ echo "\n-- ./$(NAME) 1 --"
	@-./$(NAME) 1
	@echo "\n-- ./$(NAME) 1 2 3 4 5 --"
	@-./$(NAME) 1 2 3 4 5
	@ echo "\n-- ./$(NAME) 2 -1 --"
	@-./$(NAME) 2 -1
	@ echo "\n-- ./$(NAME) 3 5 9 7 4 --"
	@-./$(NAME) 3 5 9 7 4
	@ echo "\n-- ./$(NAME) `jot -r 100 1 100000 | tr '\n' ' '` --"
	@-./$(NAME) `jot -r 100 1 100000 | tr '\n' ' '`
	@ echo "\n-- ./$(NAME) `jot -r 3000 1 100000 | tr '\n' ' '` --"
	@-./$(NAME) `jot -r 3000 1 100000 | tr '\n' ' '`


.PHONY : all clean fclean re debug test
