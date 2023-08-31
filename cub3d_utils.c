/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:35:25 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/31 12:38:42 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close_hook(t_mlx *mlx)
{
	if (mlx->img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

void	ft_del(void *ptr)
{
	free(ptr);
}

int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

void	mlx_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_lenght + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_rgb(int *color)
{
	return (color[0] << 16 | color[1] << 8 | color[2]);
}
