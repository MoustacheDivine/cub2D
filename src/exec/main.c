/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:59:47 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 21:15:31 by tle-dref         ###   ########.fr       */
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

void	key_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		clean_game(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	render(game);
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	rotation_speed;
	double	old_dir_x;
	double	old_plane_x;

	(void)ypos;
	game = (t_game *)param;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	rotation_speed = (xpos - (WIDTH / 2)) * 0.002;
	game->player.dir_x = game->player.dir_x * cos(rotation_speed)
		- game->player.dir_y * sin(rotation_speed);
	game->player.dir_y = old_dir_x * sin(rotation_speed) + game->player.dir_y
		* cos(rotation_speed);
	game->player.plane_x = game->player.plane_x * cos(rotation_speed)
		- game->player.plane_y * sin(rotation_speed);
	game->player.plane_y = old_plane_x * sin(rotation_speed)
		+ game->player.plane_y * cos(rotation_speed);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
}

int	main(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game = init_game();
	render(game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_cursor_hook(game->mlx, &mouse_hook, game);
	mlx_loop_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
