/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:06:46 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/28 18:39:34 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
#define ROT 0.04

void	handle_key_D(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = NULL;
	if (mlx->map[(int )(mlx->player.y  / TAIL_SIZE)][(int )((mlx->player.x + 6)/ TAIL_SIZE)] != '1')
	{
		mlx->player.x += 5;
	}
}

void	handle_key_A(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = NULL;
	if (mlx->map[(int )(mlx->player.y / TAIL_SIZE)][(int )(mlx->player.x / TAIL_SIZE)] != '1')
	{
		mlx->player.x -= 5;
	}
}

void	handle_up_down(t_mlx *mlx, int key)
{
	double	dx;
	double	dy;
	double	change_y;
	double	px, py;

	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = NULL;
	px = mlx->player.x / TAIL_SIZE;
	py = mlx->player.y / TAIL_SIZE;
	
	dx = key * cos(mlx->player.rotate) / (double)MOVE_SPEAD;
	dy = key * sin(mlx->player.rotate) / (double)MOVE_SPEAD;

	change_y = 0;
	if (mlx->map[(int)(py + dy)][(int)(px + dx)] == '1')
		return ;
	if (mlx->map[(int)(py + dy)][(int)px] != '1')
		change_y = 1;
	if (mlx->map[(int)py][(int)(px + dx)] != '1')
		px += dx;
	if (change_y)
		py += dy;
	mlx->player.x = px * TAIL_SIZE;
	mlx->player.y = py * TAIL_SIZE;
}

void	handle_key_left(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->player.rotate += -1 * (1 * (M_PI / 180));
	if ((int )mlx->player.rotate < 0)
		mlx->player.rotate += 2 * M_PI;
}

void	handle_key_right(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->player.rotate += 1 * (M_PI / 180);
	if (mlx->player.rotate >= 2 * M_PI - (30 * (M_PI / 180)))
		mlx->player.rotate -= 2 * M_PI;
}

void	rotate(t_mlx *mlx, int dir)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = NULL;
	mlx->player.rotate += (double) dir * ROT;
	if (mlx->player.rotate >= 2 * M_PI)
		mlx->player.rotate -= 2 * M_PI;
	else if (mlx->player.rotate < 0.0)
		mlx->player.rotate += 2 * M_PI;
}

int ft_key_hook(int key, t_mlx *mlx)
{	
	if (key == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	else if (key == KEY_D)
		handle_key_D(mlx);
	else if (key == KEY_A)
		handle_key_A(mlx);
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
