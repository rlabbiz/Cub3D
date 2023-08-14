/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:54:54 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/14 15:02:27 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
 
// DDA Function for line generation
void DDA(t_mlx *mlx, int X0, int Y0, int X1, int Y1)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
        mlx_put(mlx, round(X), round(Y), 0xE74C3C);
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
        // delay(100); // for visualization of line-
                    // generation step by step
    }
}

void	draw_pixel(t_mlx *mlx, int x, int j)
{
	int y = j;
	int len = 0;
	int len1 = 0;
	while (len < TAIL_SIZE)
	{
		y = j;
		len1 = 0;
		while (y < TAIL_SIZE && len1 < TAIL_SIZE)
		{
			mlx_put(mlx, x, y, 0xE4FD);
			y++;
			len1++;
		}
		x++;
		len++;
	}
}

char	**get_map(t_list *lst)
{
	int		len;
	int		i;
	char	**map;
	
	len = 0;
	i = 0;
	while (lst && len < 6)
	{
		lst = check_empty_line(lst);
		if (!lst)
			break ;
		lst = lst->next;
		len++;
	}
	lst = check_empty_line(lst);
	if (!lst)
		return (NULL);
	len = ft_lstsize(lst);
	map = malloc(sizeof(char *) * len + 1);
	if (!map)
		return (NULL);
	while (lst && i < len)
	{
		map[i] = ft_strdup(lst->content);
		lst = lst->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

void    draw_map(t_mlx *mlx, int player)
{
	t_list *lst;
	int		i;
	int		j;
	int		x;
	int		y;
	
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_lenght, &mlx->endian);
	i = 0;
	lst = mlx->lst;
	while (mlx->map[i])	
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (mlx->map[i][j] == '1')
			{
				x = 0;
				y = 0;
				while (x < TAIL_SIZE)
				{
					y = 0;
					while (y < TAIL_SIZE)
					{
						mlx_put(mlx, j * TAIL_SIZE + y, i * TAIL_SIZE + x, 0x979A9A);
						y++;
					}
					x++;
				}
			}
			else if (player && ft_strchr("NWSE", mlx->map[i][j]))
			{
				mlx->player.x = (j * TAIL_SIZE) + 25;
				mlx->player.y = (i * TAIL_SIZE) + 25;
			}
			j++;
		}
		i++;
	}
	j = TAIL_SIZE;
	while (j < mlx->height)
	{
		i = 0;
		while (i < mlx->width)
		{
			mlx_put(mlx, i, j, 0xE74C3C);
			i += 1;
		}
		j += TAIL_SIZE;
	}
	i = TAIL_SIZE;
	while (i < mlx->width)
	{
		j = 0;
		while (j < mlx->height)
		{
			mlx_put(mlx, i, j, 0xE74C3C);
			j += 1;
		}
		i += TAIL_SIZE;
	}
}

void	draw_player(t_mlx *mlx)
{
	int x = -3;
	int y = -3;
	while (x < 3)
	{
		y = -3;
		while (y < 3)
		{
			mlx_put(mlx, mlx->player.x + y, mlx->player.y + x, 0xE74C3C);
			y++;
		}
		x++;
	}
	
	int start_x, start_y;
	// int len_x, len_y;
	
	start_y = (mlx->player.y / TAIL_SIZE) * TAIL_SIZE;
	start_x = mlx->player.x + (mlx->player.y - start_y) / tan(mlx->player.rotate);
	
	DDA(mlx, mlx->player.x, mlx->player.y, start_x, start_y);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}