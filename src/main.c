/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:59:47 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 10:48:50 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_game(t_game *game)
{
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	exit(0);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		clean_game(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, ROTA_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, -ROTA_SPEED);
}

int	main(void)
{
	t_game		*game;

	game = malloc(sizeof(t_game));
	game = init_game();
	render(game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
