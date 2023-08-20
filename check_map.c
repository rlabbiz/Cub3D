/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:18:07 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/15 11:12:10 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_list *check_empty_line(t_list *map)
{
	const char	*line;
	int			i;

	line = NULL;
	while (map)
	{
		i = 0;
		line = map->content;
		while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
			i++;
		if (line[i] != '\0')
			break ;
		map = map->next;
	}
	return (map);
}

t_list *read_map(const char *path)
{
	t_list	*lst;
	char	*line;
	int		fd;
	char	*sub_line;

	lst = NULL;
	line = NULL;
	sub_line = NULL;
	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		sub_line = ft_strtrim(line, "\n");
        // free(line);
		line = NULL;
		if (sub_line || sub_line[0])
			ft_lstadd_back(&lst, ft_lstnew(sub_line));
	}
	return (lst);
}

int check_color_string(const char *line)
{
	int	i;
	int	len;
	int	j;

	i = 2;
	j = 1;
	if (line[i] == '\0')
		return (0);
	while (line[i])
	{
		len = 0;
		while (line[i] && ft_isdigit(line[i]))
		{
			i++;
			len++;
		}
		if (len <= 0 || len > 3 || (j < 3 && line[i] == '\0'))
			return (0);
		if (line[i] == ',')
			i++;
		j++;
	}
	if (j != 4)
		return (0);
	return (1);
}

int	check_color_int(char **split, t_mlx *mlx, char c)
{
	int	i;
	int nbr;

	i = 0;
	mlx->color.c = malloc(sizeof(int ) * 4);
	mlx->color.f = malloc(sizeof(int ) * 4);
	mlx->color.f[3] = 0;
	mlx->color.c[3] = 0;
	while (split[i])
	{
		nbr = ft_atoi(split[i]);
		if (nbr > 255)
			return (0);
		if (c == 'C')
		{
			mlx->color.c[i] = nbr;
			mlx->color.c[3] = 1;
		}
		else if (c == 'F')
		{
			mlx->color.f[i] = nbr;
			mlx->color.f[3] = 1;
		}
		i++;
	}
	return (1);
}

int	check_color(const char *line, t_mlx *mlx, char c)
{
	char	**split;

	if (check_color_string(line))
	{
		split = ft_split(line + 2, ',');
		if (check_color_int(split, mlx, c))
			return (1);
	}
	return (0);
}

int	check_texture(const char *line, t_mlx *mlx, char c)
{
	int	i;
	int	fd;

	i = 3;
	if (!line[i])
		return (0);
	// if (line[i] == '.')
	// 	i++;
	// if (line[i] && line[i] == '/')
	// 	i++;
	// if (!line[i])
	// 	return (0);
	fd = open(line + 3, O_RDONLY);
	if (fd == -1)
		return (0);
	if (c == 'N')
		mlx->texture.no = fd;
	else if (c == 'S')
		mlx->texture.so = fd;
	else if (c == 'W')
		mlx->texture.we = fd;
	else if (c == 'E')
		mlx->texture.ea = fd;
	return (1);
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

// char	*cnv_lst_to_string(t_list *lst)
// {
// 	char	*lines;
// 	int		i;
// 	char	*line;
// 	i = 0;
// 	while (lst)
// 	{
// 		lst = check_empty_line(lst);
// 		if (!lst)
// 			break ;
// 		line = lst->content;
// 		i = 0;
// 		while (line[i])
// 		{
// 			if ()
// 		}
// 	}
// }

int	check_first_and_last_line(t_list *list)
{
	t_list	*lst;
	char	*line;
	int		i;

	lst = check_empty_line(list);
	if (!lst)
		return (0);
	line = lst->content;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '\t')
			return (0);
		i++;
	}
	while (lst)
	{
		lst = check_empty_line(lst);
		if (!lst)
			break ;
		line = lst->content;
		lst = lst->next;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_valid_map(t_mlx *mlx, char *curr, char *next, int next_len, int i)
{
	if (curr[i] != '0' && curr[i] != '1' && curr[i] != ' ' && curr[i] != 'N' && curr[i] != 'S' && curr[i] != 'W' && curr[i] != 'E')
		return (0);
	if (curr[i] == '0' && i > next_len)
		return (0);
	if (curr[i] == '0' && (curr[i + 1] && curr[i + 1] == ' '))
		return (0);
	if (curr[i] == ' ' && (curr[i + 1] && curr[i + 1] == '0'))
		return (0);
	if (curr[i] == '0' && next[i] == ' ')
		return (0);
	if (curr[i] == ' ' && i <= next_len && next[i] == '0')
		return (0);
	if (curr[i] == 'N')
		mlx->player.rotate = 3 * M_PI / 2;
	else if (curr[i] == 'S')
		mlx->player.rotate = M_PI / 2;
	else if (curr[i] == 'W')
		mlx->player.rotate = M_PI;
	else if (curr[i] == 'E')
		mlx->player.rotate = 0;
	return (1);
}

int	check_valid_maps_line(t_mlx *mlx, char *curr, char *next)
{
	int curr_len;
	int	next_len;
	int	i;

	curr_len = ft_strlen(curr) - 1;
	next_len = ft_strlen(next) - 1;
	if (!curr_len || !next_len)
		return (0);
	i = 0;
	char *line = ft_strtrim(curr, " ");
	if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	// free(line);
	while (curr[i])
	{
		if (!check_valid_map(mlx, curr, next, next_len, i))
			return (0);
		i++;
	}
	return (1);
}

int check_last_lines(t_mlx *mlx, t_list *list)
{
	char	*curr;
	char	*next;

	if (!check_first_and_last_line(list))
		return (0);
	list = check_empty_line(list);
	list = list->next;
	while (list->next)
	{
		curr = list->content;
		next = list->next->content;
		if (!check_valid_maps_line(mlx, curr, next))
			return (0);
		list = list->next;
	}
	return (1);
}

int check_map(const char *path, t_mlx *mlx)
{
	t_list *lst;
	int		len;

	len = 0;
    mlx->lst = read_map(path);
	lst = mlx->lst;
	if (!lst)
		return (0);
    while (lst && len < 6)
	{
		lst = check_empty_line(lst);
		if (!lst)
			break ;
		if (!check_first_lines(lst->content, mlx))
		{
			printf("Error\n");
			printf("\tThis line is not valid : %s\n", lst->content);
			return (0);
		}
		lst = lst->next;
		len++;
	}
	if (!check_last_lines(mlx, lst))
	{
		printf("Error\n");
		printf("\tThe Map not valid\n");
		return (0);
	}
	return (1);
}