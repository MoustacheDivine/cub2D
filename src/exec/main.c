/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:59:47 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/14 03:56:39 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, -ROTA_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, ROTA_SPEED);
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

void	door_hook(mlx_key_data_t keydata, void *param)
{
	int		target_x;
	int		target_y;
	t_game	*game;

	game = param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_SPACE)
		{
			target_x = (int)(game->player.x + game->player.dir_x);
			target_y = (int)(game->player.y + game->player.dir_y);
			if (game->map[target_y][target_x] == 'D')
				game->map[target_y][target_x] = 'O';
			else if (game->map[target_y][target_x] == 'O')
				game->map[target_y][target_x] = 'D';
		}
		if (keydata.key == MLX_KEY_E)
			game->teleport = 1;
	}
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	check_cub(av[1]);
	game = init_game(av[1]);
	render(game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_cursor_hook(game->mlx, mouse_hook, game);
	mlx_key_hook(game->mlx, door_hook, game);
	mlx_close_hook(game->mlx, cross_hook, (void *)game);
	mlx_loop_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
