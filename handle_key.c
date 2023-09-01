/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:06:46 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/09/01 16:38:15 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_key_d(t_mlx *mlx)
{
		double	dx;
	double	dy;
	double	change_y;
	double	px;
	double	py;

	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = NULL;
	px = mlx->player.x;
	py = mlx->player.y;
	dx = cos(((3 * M_PI) / 2) - mlx->player.rotate) * MOVE_SPEAD;
	dy = - sin(((3 * M_PI) / 2) - mlx->player.rotate) * MOVE_SPEAD;
	change_y = 0;
	if (mlx->map[(int)((py + dy) + MARGE) / TAIL_SIZE][(int)(px + dx) / TAIL_SIZE] == '1')
		return ;
	else if (mlx->map[(int)((py + dy) - MARGE) / TAIL_SIZE][(int)(px + dx) / TAIL_SIZE] == '1')
		return ;
	else if (mlx->map[(int)((py + dy)) / TAIL_SIZE][(int)(px + dx + MARGE) / TAIL_SIZE] == '1')
		return ;
	else if (mlx->map[(int)((py + dy)) / TAIL_SIZE][(int)(px + dx - MARGE) / TAIL_SIZE] == '1')
		return ;
	mlx->player.x = px + dx;
	mlx->player.y = py + dy;
}

void	handle_key_a(t_mlx *mlx)
{
	double	dx;
	double	dy;
	double	change_y;
	double	px;
	double	py;

	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = NULL;
	px = mlx->player.x;
	py = mlx->player.y;
	dx = - cos(((3 * M_PI) / 2) - mlx->player.rotate) * MOVE_SPEAD;
	dy = sin(((3 * M_PI) / 2) - mlx->player.rotate) * MOVE_SPEAD;
	change_y = 0;
	if (mlx->map[(int)((py + dy) + MARGE) / TAIL_SIZE][(int)(px + dx) / TAIL_SIZE] == '1')
		return ;
	else if (mlx->map[(int)((py + dy) - MARGE) / TAIL_SIZE][(int)(px + dx) / TAIL_SIZE] == '1')
		return ;
	else if (mlx->map[(int)((py + dy)) / TAIL_SIZE][(int)(px + dx + MARGE) / TAIL_SIZE] == '1')
		return ;
	else if (mlx->map[(int)((py + dy)) / TAIL_SIZE][(int)(px + dx - MARGE) / TAIL_SIZE] == '1')
		return ;
	mlx->player.x = px + dx;
	mlx->player.y = py + dy;
}

void	handle_up_down(t_mlx *mlx, int key)
{
	double	dx;
	double	dy;
	double	change_y;
	double	px;
	double	py;

	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = NULL;
	px = mlx->player.x;
	py = mlx->player.y;
	dx = key * cos(mlx->player.rotate) * MOVE_SPEAD;
	dy = key * sin(mlx->player.rotate) * MOVE_SPEAD;
	change_y = 0;
	if (mlx->map[(int)((py + dy) + MARGE) / TAIL_SIZE][(int)(px + dx) / TAIL_SIZE] == '1')
		return ;
	else if (mlx->map[(int)((py + dy) - MARGE) / TAIL_SIZE][(int)(px + dx) / TAIL_SIZE] == '1')
		return ;
	else if (mlx->map[(int)((py + dy)) / TAIL_SIZE][(int)(px + dx + MARGE) / TAIL_SIZE] == '1')
		return ;
	else if (mlx->map[(int)((py + dy)) / TAIL_SIZE][(int)(px + dx - MARGE) / TAIL_SIZE] == '1')
		return ;
	mlx->player.x = px + dx;
	mlx->player.y = py + dy;
}

void	rotate(t_mlx *mlx, int dir)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = NULL;
	mlx->player.rotate += (double) dir * ROTATE_SPEAD;
	if (mlx->player.rotate >= 2 * M_PI)
		mlx->player.rotate -= 2 * M_PI;
	else if (mlx->player.rotate < 0.0)
		mlx->player.rotate += 2 * M_PI;
}

int	ft_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	else if (key == KEY_D)
		handle_key_d(mlx);
	else if (key == KEY_A)
		handle_key_a(mlx);
	else if (key == KEY_W)
		handle_up_down(mlx, UP);
	else if (key == KEY_S)
		handle_up_down(mlx, DOWN);
	else if (key == LEFT_ARROW)
		rotate(mlx, -1);
	else if (key == RIGHT_ARROW)
		rotate(mlx, 1);
	else
		return (0);
	return (draw_map(mlx, 0), 0);
}
