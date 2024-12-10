#-----------------------Flags_and_Name---------------------
NAME	=	cub3D
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -Iinc -Ilibft/inc -IMLX42/include -g
CREAD	=	-lreadline -lncursesw
LIB			=	libft
LIBFT		=	$(LIB)/libft.a
MLX			=	MLX42
LIBMLX	 =	$(MLX)/build/libmlx42.a
LIBS = $(LIBFT) $(LIBMLX) -lglfw -pthread -lm

#------------------------Source-----------------------------

# Sources and objects
FILES = main init render draw raycasting moves player

SRCS = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJS = $(addprefix obj/, $(addsuffix .o, $(FILES)))

#------------------------Rules------------------------------
#VALGRIND_SUPP = valgrind.supp

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
	$(CC) $(CFLAGS) -c $< -o $<:.c=.o) $(CREAD) $(LIBS)

$(NAME): obj ${OBJS}
	@$(call generate_random_color, $(CC) $(CFLAGS) -o $@ $(OBJS))
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(CREAD) $(LIBS)

obj/%.o: src/%.c
	@$(call generate_random_color, $(CC) $(CFLAGS) -c $< -o $@)
	@$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(NAME)
	valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=mlx42.supp ./$(NAME)

clean:
	@$(MAKE) --quiet -C $(LIB) clean
	rm -f ${OBJS}

fclean: clean
	@$(MAKE) --quiet -C $(LIB) fclean
	rm -f ${NAME}
	rm -rf obj
	rm -rf $(MLX)/build

re: fclean all

.PHONY: all clean fclean re valgrind