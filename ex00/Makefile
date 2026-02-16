# -------------------------------------------------------------------
# VARIABLES
# -------------------------------------------------------------------

# Source file directories
SRCS_DIR			= ./

INCLUDES_DIR		= ./

# Other directories
OBJS_DIR			= ./objs/

# Source files
CFILES_ROOT			= main.cpp \
					  BitcoinExchange.cpp


OBJ_FILES 			:= $(CFILES_ROOT:.cpp=.o)

DEP_FILES 			:= $(CFILES_ROOT:.cpp=.d)

OBJS				:= $(addprefix $(OBJS_DIR), $(OBJ_FILES))
DEPENDENCIES		:= $(addprefix $(OBJS_DIR), $(DEP_FILES))

# Compilation variables
NAME				= btc
CXX 				= c++
CXXFLAGS 			= -Wall -Werror -Wextra -std=c++98 -MMD -MP
RM 					= rm -rf
INCLUDES			:= $(INCLUDES_DIR)

# -------------------------------------------------------------------
# RULES
# -------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

debug: $(OBJS)
	$(CXX) -g $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) objs

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug

# -------------------------------------------------------------------
# OBJECT RULES
# -------------------------------------------------------------------
# // These have to be implemented for each directory in the project

-include $(DEPENDENCIES)
$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
