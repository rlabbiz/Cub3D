/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 10:17:10 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/31 18:44:48 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_valid_map(t_mlx *mlx, char *curr, char *next, int tmp[2])
{
	if (curr[tmp[0]] != '0' && curr[tmp[0]] != '1' && curr[tmp[0]] != ' ' \
		&& curr[tmp[0]] != 'N' && curr[tmp[0]] != 'S' \
		&& curr[tmp[0]] != 'W' && curr[tmp[0]] != 'E')
		return (0);
	if (curr[tmp[0]] == '0' && tmp[0] > tmp[1])
		return (0);
	if (curr[tmp[0]] == '0' && (curr[tmp[0] + 1] && curr[tmp[0] + 1] == ' '))
		return (0);
	if (curr[tmp[0]] == ' ' && (curr[tmp[0] + 1] && curr[tmp[0] + 1] == '0'))
		return (0);
	if (curr[tmp[0]] == '0' && next[tmp[0]] == ' ')
		return (0);
	if (curr[tmp[0]] == ' ' && tmp[0] <= tmp[1] && next[tmp[0]] == '0')
		return (0);
	if (curr[tmp[0]] == 'N')
		mlx->player.rotate = 3 * M_PI / 2;
	else if (curr[tmp[0]] == 'S')
		mlx->player.rotate = M_PI / 2;
	else if (curr[tmp[0]] == 'W')
		mlx->player.rotate = M_PI;
	else if (curr[tmp[0]] == 'E')
		mlx->player.rotate = 0;
	return (1);
}

int	check_color_string(const char *line)
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
	int	nbr;

	i = 0;
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
		if (!split)
			return (0);
		if (check_color_int(split, mlx, c))
		{
			ft_free_split(split);
			return (1);
		}
		ft_free_split(split);
	}
	return (0);
}

int	check_texture(const char *line, t_mlx *mlx, char c)
{
	char	*file;
	int		i;
	int		fd;

	i = 3;
	if (!line[i])
		return (0);
	file = ft_strtrim(line + 3, " ");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	if (c == 'N')
		mlx->texture.no = file;
	else if (c == 'S')
		mlx->texture.so = file;
	else if (c == 'W')
		mlx->texture.we = file;
	else if (c == 'E')
		mlx->texture.ea = file;
	return (1);
}
