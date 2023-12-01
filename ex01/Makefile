NAME = RPN
SRC = main.cpp RPN.cpp
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
	./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	./$(NAME) "7 7 * 7 -"
	./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	-./$(NAME) "(1 + 1)"

.PHONY : all clean fclean re test
