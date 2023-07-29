/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:47:51 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/07/29 09:56:59 by rlabbiz          ###   ########.fr       */
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
		if (!sub_line || !sub_line[0])
			break ;
		ft_lstadd_back(&lst, ft_lstnew(line));
	}
	return (lst);
}

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

char *skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (str + i);
}

int	check_all_texture(t_texture *texture)
{
	if (texture->ea == NULL)
	{
		printf("Error\n\tWe need the east texture\n");
		return (1);
	}
	else if (texture->no == NULL)
	{
		printf("Error\n\tWe need the north texture.\n");
		return (1);
	}
	else if (texture->so == NULL)
	{
		printf("Error\n\tWe need the south texture\n");
		return (1);
	}
	else if (texture->we == NULL)
	{
		printf("Error\n\tWe need the west texture\n");
		return (1);
	}
	return (0);
}

int fill_texture(t_texture *texture, const char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		texture->no = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		texture->so = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		texture->we = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		texture->ea = ft_strdup(line + 3);
	else
	{
		printf("Error\n");
		printf("\tWe dont know this line : %s", line);
		return (1);
	}
	return (0);
}

int check_valid_texture(t_list *map, t_texture *texture)
{
	const char	*line;
	int			len;

	len = 0;
	while (map)
	{
		if (len == 4)
			break ;
		map = check_empty_line(map);
		if (map == NULL)
			return (check_all_texture(texture));
		line = skip_spaces(map->content);
		if (fill_texture(texture, line))
			return (1);
		map = map->next;
		len++;
	}
	return (check_all_texture(texture));
}

int is_color_range(const char *line)
{
	int	i;
	int	len;
	int	j;

	i = 2;
	j = 0;
	printf("%s", line);
	if (ft_strncmp(line, "F ", 2) && ft_strncmp(line, "C ", 2))
		return (0);
	while (line[i])
	{
		len = 0;
		while (line[i] && (line[i] >= '0' && line[i] <= '9'))
		{
			i++;
			len++;
		}
		if (!line[i])
			break ;
		if (line[i] != ',')
		{
			printf("%d%c", i, line[i]);
			return (0);
		}
		if (len > 4)
			return (0);
		i++;
		j++;
	}
	if (j > 3)
		return (0);
	return (1);
}

// int fill_color_range(const char *line)
// {
// 	int i;

// 	i = 0;
// 	while (line[i] && (line[i] < '0' && line[i] > '9'))
// 		i++;
// 	if (!line[i])
// 		return (0);
// 	if (!ft_strncmp(line, "F ", 2))
// 	{
		
// 	}
// 	else if (!ft_strncmp(line, "F ", 2))
// 	{
		
// 	}
// }

int	check_color_range(const char *line)
{
	if (is_color_range(line))
		return (1);
	return (0);
}

int check_valid_color(t_list *map)
{
	const char	*line;
	int			len;

	len = 0;
	while (map && len < 4)
	{
		map = check_empty_line(map);
		if (!map)
			break ;
		map = map->next;
		map = check_empty_line(map);
		len++;
	}
	len = 0;
	while (map && len < 2)
	{
		map = check_empty_line(map);
		if (!map)
			return (1);
		line = skip_spaces(map->content);
		if (check_color_range(line))
			return (0);
		map = map->next;
	}
	return (1);
}

int check_valid_map(t_list *map)
{
	(void)map;
	return (0);
}

int check_map(void)
{
	t_list		*map;
	t_texture	texture;

	texture.ea = NULL;
	texture.we = NULL;
	texture.no = NULL;
	texture.so = NULL;
	map = read_map("maps/map.cub");
	if (check_valid_texture(map, &texture) || check_valid_color(map) || check_valid_map(map))
		return (1);
	ft_lstclear(&map, ft_del);
	return(0);
}

int main(void)
{
	t_mlx mlx;
	
	if (check_map())
		return (1);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1200, 2100, "CUB3D");
	mlx_key_hook(mlx.win, &ft_key_hook, &mlx);
	mlx_hook(mlx.win, 17, 0, ft_close_hook, &mlx);

	mlx_loop(mlx.mlx);
	return (0);
}