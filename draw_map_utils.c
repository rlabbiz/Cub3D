/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 10:50:20 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/31 18:08:23 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_mlx *mlx, int top, int bottom, int col)
{
	int		i;
	int		new_top;
	t_xpm	*xpm;

	xpm = &mlx->xpm[get_deroction(mlx)];
	i = top;
	if (mlx->ray.vertical)
		mlx->ray.texture_x = xpm->width / TAIL_SIZE * \
			(mlx->ray.wall_y - (int)(mlx->ray.wall_y / TAIL_SIZE) * TAIL_SIZE);
	else
		mlx->ray.texture_x = xpm->width / TAIL_SIZE * \
			(mlx->ray.wall_x - (int)(mlx->ray.wall_x / TAIL_SIZE) * TAIL_SIZE);
	while (i < bottom)
	{
		new_top = i + ((int)mlx->ray.wall_height / 2) - (mlx->height / 2);
		mlx->ray.texture_y = new_top * \
			((float)xpm->height / (int)(mlx->ray.wall_height));
		if ((mlx->ray.texture_x > 0 && mlx->ray.texture_x \
			< xpm->width) && (mlx->ray.texture_y < xpm->height))
		{
			mlx_put(mlx, col, i, \
				mlx_get_color(xpm, mlx->ray.texture_x, mlx->ray.texture_y));
		}
		i++;
	}
}

void	draw_floor(t_mlx *mlx, int bottom, int col)
{
	while (bottom < mlx->height)
	{
		mlx_put(mlx, col, bottom, create_rgb(mlx->color.f));
		bottom++;
	}
}

void	draw_ceiling(t_mlx *mlx, int top, int col)
{
	while (top >= 0)
	{
		mlx_put(mlx, col, top, create_rgb(mlx->color.c));
		top--;
	}
}

void	draw_player(t_mlx *mlx)
{
	int	x;
	int	y;

	x = -2;
	y = -2;
	while (x < 2)
	{
		y = -2;
		while (y < 2)
		{
			mlx_put(mlx, mlx->player.x + y, mlx->player.y + x, 0xE74C3C);
			y++;
		}
		x++;
	}
}

t_xpm	*get_textures(t_mlx *mlx)
{
	t_xpm	*xpm;

	xpm = malloc(sizeof(t_xpm) * 4);
	xpm[0].img = mlx_xpm_file_to_image(mlx->mlx, \
		mlx->texture.ea, &xpm[0].width, &xpm[0].height);
	xpm[0].addr = mlx_get_data_addr(xpm[0].img, \
		&xpm[0].bits_per_pixel, &xpm[0].line_lenght, &xpm[0].endian);
	xpm[1].img = mlx_xpm_file_to_image(mlx->mlx, \
		mlx->texture.no, &xpm[1].width, &xpm[1].height);
	xpm[1].addr = mlx_get_data_addr(xpm[1].img, \
		&xpm[1].bits_per_pixel, &xpm[1].line_lenght, &xpm[1].endian);
	xpm[2].img = mlx_xpm_file_to_image(mlx->mlx, \
		mlx->texture.so, &xpm[2].width, &xpm[2].height);
	xpm[2].addr = mlx_get_data_addr(xpm[2].img, \
		&xpm[2].bits_per_pixel, &xpm[2].line_lenght, &xpm[2].endian);
	xpm[3].img = mlx_xpm_file_to_image(mlx->mlx, \
		mlx->texture.we, &xpm[3].width, &xpm[3].height);
	xpm[3].addr = mlx_get_data_addr(xpm[3].img, \
		&xpm[3].bits_per_pixel, &xpm[3].line_lenght, &xpm[3].endian);
	return (xpm);
}
