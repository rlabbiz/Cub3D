/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:47:54 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/25 19:44:11 by rlabbiz          ###   ########.fr       */
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

# define TAIL_SIZE 10
# define WIDTH 1800
# define HEIGHT 800

# define FOV 60 * (M_PI / 180)
# define RAYS WIDTH
# define ANGLE_INCREMENT FOV / RAYS

// define the keys of keyboard 
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define KEY_A 0
# define KEY_W 13
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

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
	double	x;
	double	y;
}	t_angle;

typedef struct s_ray
{
	int		is_up;
	int		is_down;
	int		is_right;
	int		is_left;
	int 	texture_width;
	int 	texture_height;
	double	wall_height;
	int		vertical;
	int		texture_y;
	int		texture_x;
	double	wall_x;
	double	wall_y;
}	t_ray;

// typedef struct s_mini
// {
// 	int width;
// 	int	height;
// }	t_mini;

typedef struct s_player
{
	double	x;
	double	y;
	double	rotate;
}	t_player;

typedef struct s_xpm
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}	t_xpm;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	void		*img_ptr;
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
	t_ray		ray;
	t_xpm		xpm;
}	t_mlx;

// cub3d
int		skip_spaces(const char *str);
void	mlx_put(t_mlx *mlx, int x, int y, int color);
void	mlx_put_rgb(t_mlx *mlx, int x, int y, int *color);
void	ft_free_split(char **split);

// handle_key
int ft_key_hook(int key, t_mlx *mlx);

// chech_map
int		check_map(const char *path, t_mlx *mlx);
t_list	*read_map(const char *path);
t_list	*check_empty_line(t_list *lst);

// draw_map
void	DDA(t_mlx *mlx, int X0, int Y0, int X1, int Y1, int color);
void    draw_map(t_mlx *mlx, int player);
char	**get_map(t_list *lst);
void	draw_player(t_mlx *mlx);

#endif