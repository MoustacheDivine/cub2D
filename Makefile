NAME	=	cub3D
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -Iinc -Ilibft/inc -IMLX42/include -g
CREAD	=	-lreadline -lncursesw
LIB			=	libft
LIBFT		=	$(LIB)/libft.a
MLX			=	MLX42
LIBMLX		=	$(MLX)/build/libmlx42.a
LIBS = $(LIBFT) $(LIBMLX) -lglfw -pthread -lm

#------------------------Source-----------------------------

# Sources and objects
EXECDIR		=	src/exec
PARSDIR		=	src/parsing
OBJDIR		=	obj

EXEC = main init render raycasting moves player walls draw colors minimap teleport particles positions
PARS = parsing utils check free map scam valid

SRCS		=	$(addprefix $(EXECDIR)/, $(addsuffix .c, $(EXEC))) \
				$(addprefix $(PARSDIR)/, $(addsuffix .c, $(PARS)))
OBJS		=	$(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

#------------------------Rules------------------------------
all: $(LIBFT) $(LIBMLX) $(NAME)

obj:
	mkdir -p obj

$(LIBFT):
	@$(MAKE) --quiet -C $(LIB)
	@echo "Libft compilée."

$(LIBMLX):
	@if [ ! -d "$(MLX)" ]; then \
		echo "Clonage de MLX42 library..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX); \
	fi
	@echo "Compilation de MLX42 library..."
	@cmake -S $(MLX) -B $(MLX)/build
	@cmake --build $(MLX)/build

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/exec/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/parsing/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): obj $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(CREAD) $(LIBS)

clean:
	@$(MAKE) --quiet -C $(LIB) clean
	rm -f ${OBJS}

fclean: clean
	@$(MAKE) --quiet -C $(LIB) fclean
	rm -f ${NAME}
	rm -rf obj
	rm -rf $(MLX)/build

re: fclean all

.PHONY: all clean fclean re