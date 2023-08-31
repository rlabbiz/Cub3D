/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:38:03 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/31 18:40:57 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hor_init(t_mlx *mlx, t_rays *rays, double angle)
{
	rays->start_y = ((int)(mlx->player.y) / TAIL_SIZE) * TAIL_SIZE;
	if (mlx->ray.is_down)
		rays->start_y += TAIL_SIZE;
	rays->start_x = (int)(mlx->player.x) + \
		(rays->start_y - (int)(mlx->player.y)) / tan(angle);
	rays->step_y = TAIL_SIZE;
	rays->step_y *= 1 - 2 * (mlx->ray.is_up != 0);
	rays->step_x = TAIL_SIZE / tan(angle);
	if (mlx->ray.is_left && rays->step_x > 0)
		rays->step_x *= -1;
	if (mlx->ray.is_right && rays->step_x < 0)
		rays->step_x *= -1;
}

void	ver_init(t_mlx *mlx, t_rays *rays, double angle)
{
	rays->start_x = ((int)(mlx->player.x) / TAIL_SIZE) * TAIL_SIZE;
	if (mlx->ray.is_right)
		rays->start_x += TAIL_SIZE;
	rays->start_y = (int)(mlx->player.y) + \
		(rays->start_x - (int)(mlx->player.x)) * tan(angle);
	rays->step_x = TAIL_SIZE;
	rays->step_x *= 1 - 2 * (mlx->ray.is_left != 0);
	rays->step_y = TAIL_SIZE * tan(angle);
	if (mlx->ray.is_up && rays->step_y > 0)
		rays->step_y *= -1;
	if (mlx->ray.is_down && rays->step_y < 0)
		rays->step_y *= -1;
}

double	horezontal(t_mlx *mlx, double *hor_x, double *hor_y, double angle)
{
	int		check;
	t_rays	rays;

	check = 0;
	hor_init(mlx, &rays, angle);
	while (1)
	{
		if (mlx->ray.is_up)
			check = is_wall(mlx, rays.start_x / TAIL_SIZE, \
				(rays.start_y - 1) / TAIL_SIZE);
		else
			check = is_wall(mlx, rays.start_x / TAIL_SIZE, \
				rays.start_y / TAIL_SIZE);
		if (check == 1)
		{
			*hor_x = rays.start_x;
			*hor_y = rays.start_y;
			break ;
		}
		else if (check == -1)
			break ;
		rays.start_x += rays.step_x;
		rays.start_y += rays.step_y;
	}
	return (dest_point(mlx->player.x, mlx->player.y, *hor_x, *hor_y));
}

double	vertical(t_mlx *mlx, double *ver_x, double *ver_y, double angle)
{
	int		check;
	t_rays	rays;

	check = 0;
	ver_init(mlx, &rays, angle);
	while (1)
	{
		if (mlx->ray.is_left)
			check = is_wall(mlx, (rays.start_x - 1) / TAIL_SIZE, \
				rays.start_y / TAIL_SIZE);
		else 
			check = is_wall(mlx, rays.start_x / TAIL_SIZE, \
				rays.start_y / TAIL_SIZE);
		if (check == 1)
		{
			*ver_x = rays.start_x;
			*ver_y = rays.start_y;
			break ;
		}
		else if (check == -1)
			break ;
		rays.start_x += rays.step_x;
		rays.start_y += rays.step_y;
	}
	return (dest_point(mlx->player.x, mlx->player.y, *ver_x, *ver_y));
}
