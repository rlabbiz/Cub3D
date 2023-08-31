/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:54:54 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/31 18:12:32 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_map(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (mlx->map[i])
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (mlx->map[i][j] == '1')
				draw_square(mlx, i, j, 0x979A9A);
			else if (mlx->map[i][j] == '0' || ft_strchr("NWSE", mlx->map[i][j]))
				draw_square(mlx, i, j, 0x000000);
			j++;
		}
		i++;
	}
	draw_player(mlx);
}

void	get_player_postion(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (mlx->map[i])
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (ft_strchr("NWSE", mlx->map[i][j]))
			{
				mlx->player.x = (j * TAIL_SIZE) + TAIL_SIZE / 2;
				mlx->player.y = (i * TAIL_SIZE) + TAIL_SIZE / 2;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	is_wall(t_mlx *mlx, int x, int y)
{
	int	len;

	len = 0;
	if (x < 0 || y < 0 || x > mlx->width || y > mlx->height)
	{
		return (-1);
	}
	while (mlx->map[len])
		len++;
	if (y >= len)
		return (-1);
	if (x >= (int )ft_strlen(mlx->map[y]))
		return (-1);
	if (mlx->map[y][x] == '1')
		return (1);
	return (0);
}

int	get_deroction(t_mlx *mlx)
{
	if (!mlx->ray.vertical && mlx->ray.is_up)
		return (0);
	if (!mlx->ray.vertical && mlx->ray.is_down)
		return (1);
	if (mlx->ray.vertical && mlx->ray.is_left)
		return (2);
	return (3);
}

void	draw_map(t_mlx *mlx, int player)
{
	int	check_map;

	check_map = 0;
	if (!mlx->img)
	{
		mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
		mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, \
			&mlx->line_lenght, &mlx->endian);
		check_map = 1;
	}
	if (player)
	{
		mlx->xpm = get_textures(mlx);
		get_player_postion(mlx);
	}
	rays_casting(mlx);
	if (check_map)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
