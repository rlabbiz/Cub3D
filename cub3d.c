/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:47:51 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/20 18:04:42 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int ft_close_hook(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

void	ft_del(void *ptr)
{
	free(ptr);
}

int skip_spaces(const char *str)
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

void	init_mlx(t_mlx *mlx)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	mlx->map = get_map(mlx->lst);
	while (mlx->map && mlx->map[i])
	{
		if (ft_strlen(mlx->map[i]) > len)
			len = ft_strlen(mlx->map[i]);
		i++;
	}
	mlx->width = len * TAIL_SIZE;
	i = 0;
	while (mlx->map && mlx->map[i])
		i++;
	mlx->height = i * TAIL_SIZE;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "CUB3D");
}

int main(void)
{
	t_mlx	mlx;

	ft_bzero(&mlx, sizeof(t_mlx));
	if (check_map("maps/map.cub", &mlx))
	{
		init_mlx(&mlx);
		mlx_hook(mlx.win, 2, 0, ft_key_hook, &mlx);
		mlx_hook(mlx.win, 17, 0, ft_close_hook, &mlx);
		draw_map(&mlx, 1);
		mlx_loop(mlx.mlx);
		return (0);
	}
	return (1);
}