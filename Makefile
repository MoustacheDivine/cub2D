# Nom de l'exécutable final
NAME = cub3D

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCDIR) -I $(MLX) -I $(LIB) -g
CLINKS = -ldl -lglfw -pthread -lm

# MLX42 et Libft
MLX = lib/MLX42
LIBMLX = $(MLX)/libmlx42.a
LIB = lib/libft
LIBFT = $(LIB)/libft.a

# Dossiers
SRCDIR = src
INCDIR = inc
OBJDIR = obj

# Récupération des fichiers sources
SRC = main.c \
		parsing.c \
		utils.c \
		utils2.c \

# Chemin complet pour les fichiers objets dans obj/
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# Règle par défaut
all: $(LIBFT) $(LIBMLX) $(NAME)

# Compilation de l'exécutable avec les bibliothèques
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBMLX) $(LIBFT) -o $(NAME) $(CLINKS)
	@echo "Compilation de $(NAME) terminée."

# Compilation de la libft
$(LIBFT):
	@$(MAKE) --quiet -C $(LIB)
	@echo "Libft compilée."

# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier obj si nécessaire
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) --quiet -C $(LIB) clean
	@echo "Nettoyage des fichiers objets."

# Nettoyage complet (objets + exécutable + bibliothèques)
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --quiet -C $(LIB) fclean
	@echo "Nettoyage complet."

# Recompile tout depuis zéro
re: fclean all

# Vérification de la norme avec norminette
norm:
	@echo "Norminette de $(NAME) dans $(SRCDIR) et $(INCDIR)..."
	@if norminette $(SRCDIR)/*.c $(INCDIR)/*.h | grep -v "OK!" | grep -q "Error!"; then \
		norminette $(SRCDIR)/*.c $(INCDIR)/*.h | grep -v "OK!" | \
		while read line; do \
			if echo $$line | grep -q "Error!"; then \
				echo "\033[0;31m$$line\033[0m"; \
			else \
				echo "$$line"; \
			fi; \
		done; \
	else \
		echo "\033[0;32mAll files are norminette friendly !\033[0m"; \
	fi

# Ignorer les erreurs sur ces règles
.PHONY: all clean fclean re norm
