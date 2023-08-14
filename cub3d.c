/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:47:51 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/05 21:51:30 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int ft_key_hook(int key, t_mlx *mlx)
{
	if (key == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	else if (key == 2)
	{
		if (mlx->map[mlx->player.y  / TAIL_SIZE][(mlx->player.x + 6)/ TAIL_SIZE] != '1')
		{
			mlx_destroy_image(mlx->mlx, mlx->img);
			draw_map(mlx, 0);
			mlx->player.x += 5;
			draw_player(mlx);
		}
	}
	else if (key == 0)
	{
		if (mlx->map[mlx->player.y / TAIL_SIZE][(mlx->player.x - 6) / TAIL_SIZE] != '1')
		{
			mlx_destroy_image(mlx->mlx, mlx->img);
			draw_map(mlx, 0);
			mlx->player.x -= 5;
			draw_player(mlx);
		}
	}
	else if (key == 13)
	{
		if (mlx->map[(mlx->player.y - 6) / TAIL_SIZE ][mlx->player.x / TAIL_SIZE ] != '1')
		{
			mlx_destroy_image(mlx->mlx, mlx->img);
			draw_map(mlx, 0);
			float pdx = cos(mlx->player.rotate) * TAIL_SIZE;
			float pdy = sin(mlx->player.rotate) * TAIL_SIZE;
			mlx->player.y += pdy / 10;
			mlx->player.x += pdx / 10;
			draw_player(mlx);
		}
	}
	else if (key == 1)
	{
		if (mlx->map[(mlx->player.y + 6) / TAIL_SIZE][mlx->player.x / TAIL_SIZE] != '1')
		{
			mlx_destroy_image(mlx->mlx, mlx->img);
			draw_map(mlx, 0);
			mlx->player.y += 5;
			draw_player(mlx);
		}
	}
	else if (key == 123)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		draw_map(mlx, 0);
		mlx->player.rotate -= 0.2;
		draw_player(mlx);
	}
	else if (key == 124)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		draw_map(mlx, 0);
		mlx->player.rotate += 0.2;
		draw_player(mlx);
	}
	return (0);
}

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
	mlx->width = len * 50;
	i = 0;
	while (mlx->map && mlx->map[i])
		i++;
	mlx->height = i * 50;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "CUB3D");
}

int main(void)
{
	t_mlx	mlx;

	if (check_map("maps/map.cub", &mlx))
	{
		init_mlx(&mlx);
		mlx_hook(mlx.win, 2, 0, ft_key_hook, &mlx);
		mlx_hook(mlx.win, 17, 0, ft_close_hook, &mlx);
		draw_map(&mlx, 1);
		draw_player(&mlx);
		mlx_loop(mlx.mlx);
		return (0);
	}
	return (1);
}