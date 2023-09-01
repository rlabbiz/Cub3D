/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:18:07 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/09/01 16:56:40 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_valid_maps_line(t_mlx *mlx, char *curr, char *next)
{
	char	*line;
	int		curr_len;
	int		next_len;
	int		i;
	int		tmp[2];

	curr_len = ft_strlen(curr) - 1;
	next_len = ft_strlen(next) - 1;
	if (!curr_len || !next_len)
		return (0);
	i = 0;
	line = ft_strtrim(curr, " ");
	if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	free(line);
	while (curr[i])
	{
		tmp[0] = i;
		tmp[1] = next_len;
		if (!check_valid_map(mlx, curr, next, tmp))
			return (0);
		i++;
	}
	return (1);
}

int	check_last_lines(t_mlx *mlx, t_list *list)
{
	char	*curr;
	char	*next;
	int		len;

	if (!check_first_and_last_line(list))
		return (0);
	list = check_empty_line(list);
	list = list->next;
	len = 0;
	while (list->next)
	{
		curr = list->content;
		next = list->next->content;
		if (curr[0] == '\0')
			break ;
		if (!check_valid_maps_line(mlx, curr, next))
			return (0);
		len++;
		list = list->next;
	}
	if (mlx->player.player == 0)
		return (0);
	return (1);
}

int	check_enter_all(t_mlx *mlx)
{
	if (mlx->color.c[3] == 0 || mlx->color.f[3] == 0)
	{
		printf("Error\n\tNeed the color range\n");
		return (0);
	}
	if (!mlx->texture.ea || !mlx->texture.no || !mlx->texture.so || !mlx->texture.we)
	{
		printf("Error\n\tNeed all textures\n");
		return (0);
	}
	return (1);
}

t_list	*map_color_init(t_mlx *mlx, const char *path)
{
	t_list	*lst;

	mlx->lst = read_map(path);
	lst = mlx->lst;
	mlx->color.c = malloc(sizeof(int ) * 4);
	mlx->color.f = malloc(sizeof(int ) * 4);
	mlx->color.f[3] = 0;
	mlx->color.c[3] = 0;
	return (lst);
}

int	check_map(const char *path, t_mlx *mlx)
{
	t_list	*lst;
	int		len;

	len = 0;
	lst = map_color_init(mlx, path);
	if (!lst)
		return (printf("Error\n\tcan't open %s\n", path), 0);
	while (lst && len < 6)
	{
		lst = check_empty_line(lst);
		if (!lst)
			break ;
		if (!check_first_lines(lst->content, mlx))
		{
			printf("Error\n\tThis line is not valid : %s\n", lst->content);
			return (0);
		}
		lst = lst->next;
		len++;
	}
	if (!check_enter_all(mlx))
		return (0);
	if (!check_last_lines(mlx, lst))
		return (printf("Error\n\tThe Map not valid\n"), 0);
	return (1);
}
