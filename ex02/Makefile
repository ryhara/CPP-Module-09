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

test :
	./$(NAME) 0
	./$(NAME) 0.0
	./$(NAME) 0.0f
	./$(NAME) nan
	./$(NAME) nanf
	./$(NAME) +inf
	./$(NAME) -inf
	./$(NAME) +inff
	./$(NAME) -inff
	./$(NAME) 42
	./$(NAME) -42
	./$(NAME) 42.0
	./$(NAME) -42.0
	./$(NAME) 42.0f
	./$(NAME) -42.0f

.PHONY : all clean fclean re test
