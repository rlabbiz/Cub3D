/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:12:46 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/31 18:12:58 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mlx_get_color(t_xpm *xpm, int x, int y)
{
	char	*dst;

	dst = xpm->addr + (y * xpm->line_lenght + x * (xpm->bits_per_pixel / 8));
	return (*(int *)dst);
}

double	uniform_angle(double angle)
{
	if (angle > 2.0 * M_PI)
		angle -= 2.0 * M_PI;
	else if (angle < 0.0)
		angle += 2.0 * M_PI;
	return (angle);
}

t_list	*skip_first_lines(t_list *list)
{
	int		len;
	t_list	*lst;

	len = 0;
	lst = list;
	while (lst && len < 6)
	{
		lst = check_empty_line(lst);
		if (!lst)
			break ;
		lst = lst->next;
		len++;
	}
	lst = check_empty_line(lst);
	return (lst);
}

char	**get_map(t_list *lst)
{
	int		len;
	int		i;
	char	**map;

	len = 0;
	i = 0;
	lst = skip_first_lines(lst);
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

void	draw_square(t_mlx *mlx, int i, int j, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < TAIL_SIZE)
	{
		y = 0;
		while (y < TAIL_SIZE)
		{
			mlx_put(mlx, j * TAIL_SIZE + y, i * TAIL_SIZE + x, color);
			y++;
		}
		x++;
	}
}
