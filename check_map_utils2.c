/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:05:55 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/31 13:40:26 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*check_empty_line(t_list *map)
{
	const char	*line;
	int			i;

	line = NULL;
	while (map)
	{
		i = 0;
		line = map->content;
		if (!line)
			break ;
		while (line[i] && (line[i] == ' ' \
			|| line[i] == '\t' || line[i] == '\n'))
			i++;
		if (line[i] != '\0')
			break ;
		map = map->next;
	}
	return (map);
}

t_list	*read_map(const char *path)
{
	t_list	*lst;
	char	*line;
	int		fd;
	char	*sub_line;

	lst = NULL;
	line = NULL;
	sub_line = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		sub_line = ft_strtrim(line, "\n");
		free(line);
		line = NULL;
		if (sub_line)
			ft_lstadd_back(&lst, ft_lstnew(sub_line));
	}
	return (lst);
}

int	check_first_lines(const char *line, t_mlx *mlx)
{
	int	i;

	if (!line || !mlx)
		return (0);
	i = skip_spaces(line);
	if (!ft_strncmp(line + i, "F ", 2))
		return (check_color(line + i, mlx, 'F'));
	else if (!ft_strncmp(line + i, "C ", 2))
		return (check_color(line + i, mlx, 'C'));
	else if (!ft_strncmp(line + i, "NO ", 3))
		return (check_texture(line + i, mlx, 'N'));
	else if (!ft_strncmp(line + i, "SO ", 3))
		return (check_texture(line + i, mlx, 'S'));
	else if (!ft_strncmp(line + i, "WE ", 3))
		return (check_texture(line + i, mlx, 'W'));
	else if (!ft_strncmp(line + i, "EA ", 3))
		return (check_texture(line + i, mlx, 'E'));
	return (0);
}

int	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_first_and_last_line(t_list *list)
{
	t_list	*lst;
	char	*line;

	lst = check_empty_line(list);
	if (!lst)
		return (0);
	line = lst->content;
	if (!is_valid_map_line(line))
		return (0);
	while (lst)
	{
		lst = check_empty_line(lst);
		if (!lst)
			break ;
		line = lst->content;
		lst = lst->next;
	}
	return (is_valid_map_line(line));
}
