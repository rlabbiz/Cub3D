/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:47:54 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/12 12:10:14 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define reset "\e[0m"
# define TAIL_SIZE 50
typedef struct s_texture
{
	int	no;
	int	so;
	int	we;
	int	ea;
}	t_texture;

typedef struct s_color
{
	int *f;
	int *c;
}	t_color;

typedef struct s_angle
{
	float	x;
	float	y;
}	t_angle;

typedef struct s_player
{
	int	x;
	int	y;
	float	rotate;
}	t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_lenght;
	int			endian;
	char		**map;
	t_list		*lst;
	t_color		color;
	t_texture	texture;
	t_player	player;
	t_angle		angle;
}	t_mlx;

// cub3d
int		skip_spaces(const char *str);
void	mlx_put(t_mlx *mlx, int x, int y, int color);

// chech_map
int		check_map(const char *path, t_mlx *mlx);
t_list	*read_map(const char *path);
t_list	*check_empty_line(t_list *lst);

// draw_map
void    draw_map(t_mlx *mlx, int player);
char	**get_map(t_list *lst);
void	draw_player(t_mlx *mlx);

#endif