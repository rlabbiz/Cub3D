/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hendle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:06:46 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/19 17:53:59 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	handle_key_D(t_mlx *mlx)
{
	if (mlx->map[mlx->player.y  / TAIL_SIZE][(mlx->player.x + 6)/ TAIL_SIZE] != '1')
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx->player.x += 5;
		draw_map(mlx, 0);
		// draw_player(mlx);
	}
}

void	handle_key_A(t_mlx *mlx)
{
	if (mlx->map[mlx->player.y / TAIL_SIZE][(mlx->player.x - 6) / TAIL_SIZE] != '1')
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx->player.x -= 5;
		draw_map(mlx, 0);
		// draw_player(mlx);
	}
}

void	handle_key_W(t_mlx *mlx)
{
	if (mlx->map[(mlx->player.y - 6) / TAIL_SIZE ][mlx->player.x / TAIL_SIZE ] != '1')
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		float pdx = cos(mlx->player.rotate) * 2;
		float pdy = sin(mlx->player.rotate) * 2;
		mlx->player.y += pdy;
		mlx->player.x += pdx;
		draw_map(mlx, 0);
		// draw_player(mlx);
	}
}

void	handle_key_S(t_mlx *mlx)
{
	if (mlx->map[(mlx->player.y + 6) / TAIL_SIZE][mlx->player.x / TAIL_SIZE] != '1')
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		float pdx = cos(mlx->player.rotate) * -2;
		float pdy = sin(mlx->player.rotate) * -2;
		mlx->player.y += pdy;
		mlx->player.x += pdx;
		draw_map(mlx, 0);
		// draw_player(mlx);
	}
}

void	handle_key_left(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	// mlx->player.rotate += 0.1;
	// if (mlx->player.rotate > 2 * M_PI)
	mlx->player.rotate += -1 * (2 * (M_PI / 180));
	draw_map(mlx, 0);
	// draw_player(mlx);
}

void	handle_key_right(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	// mlx->player.rotate -= 0.1;
	// if (mlx->player.rotate < 0)
	mlx->player.rotate += 2 * (M_PI / 180);
	draw_map(mlx, 0);
	// draw_player(mlx);
}

int	ft_key_hook(int key, t_mlx *mlx)
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
		handle_key_W(mlx);
	else if (key == KEY_S)
		handle_key_S(mlx);
	else if (key == LEFT_ARROW)
		handle_key_left(mlx);
	else if (key == RIGHT_ARROW)
		handle_key_right(mlx);
	return (0);
}