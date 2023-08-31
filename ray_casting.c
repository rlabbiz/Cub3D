/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:36:00 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/31 19:29:33 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	dest_point(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	check_small_dest(t_mlx *mlx, t_rays rays)
{
	if (rays.ver_dest < rays.hor_dest)
	{
		mlx->ray.vertical = 1;
		mlx->ray.wall_x = rays.ver_x;
		mlx->ray.wall_y = rays.ver_y;
		return (rays.ver_dest);
	}
	mlx->ray.vertical = 0;
	mlx->ray.wall_x = rays.hor_x;
	mlx->ray.wall_y = rays.hor_y;
	return (rays.hor_dest);
}

double	cast_rays(t_mlx *mlx, double angle)
{
	t_rays	rays;

	mlx->ray.is_down = angle > 0 && angle < M_PI;
	mlx->ray.is_up = !mlx->ray.is_down;
	mlx->ray.is_right = angle < M_PI / 2.0 || angle > 3.0 * M_PI / 2.0;
	mlx->ray.is_left = !mlx->ray.is_right;
	rays.hor_x = mlx->width;
	rays.hor_y = mlx->height;
	rays.ver_x = mlx->width;
	rays.ver_y = mlx->height;
	rays.hor_dest = horezontal(mlx, &rays.hor_x, &rays.hor_y, angle);
	rays.ver_dest = vertical(mlx, &rays.ver_x, &rays.ver_y, angle);
	return (check_small_dest(mlx, rays));
}

void	rays_casting(t_mlx *mlx)
{
	t_rays	rays;

	rays.col = 0;
	rays.fov = 60 * (M_PI / 180);
	rays.angle_increment = rays.fov / RAYS;
	rays.ray_angle = mlx->player.rotate - (rays.fov / 2);
	rays.dest_project_plane = (mlx->height / 2) / tan(rays.fov / 2);
	while (rays.col < RAYS)
	{
		mlx->ray.dest = cast_rays(mlx, uniform_angle(rays.ray_angle));
		rays.new_dest = mlx->ray.dest * \
			cos(rays.ray_angle - mlx->player.rotate);
		mlx->ray.wall_height = (TAIL_SIZE / rays.new_dest) * \
			rays.dest_project_plane;
		rays.top_pixel = (mlx->height / 2) - (mlx->ray.wall_height / 2);
		if (rays.top_pixel < 0)
			rays.top_pixel = 0;
		rays.bottom_pixel = (mlx->height / 2) + (mlx->ray.wall_height / 2);
		if (rays.bottom_pixel > mlx->height)
			rays.bottom_pixel = mlx->height;
		draw_ceiling(mlx, rays.top_pixel, rays.col);
		draw_wall(mlx, rays.top_pixel, rays.bottom_pixel, rays.col);
		draw_floor(mlx, rays.bottom_pixel, rays.col);
		rays.ray_angle += rays.angle_increment;
		rays.col++;
	}
}
