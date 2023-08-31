/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:47:54 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/31 19:32:44 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define RESET "\e[0m"

# define TAIL_SIZE 15
# define WIDTH 1800
# define HEIGHT 900

# define RAYS WIDTH
# define MOVE_SPEAD 0.80
# define ROTATE_SPEAD 0.2
# define UP 1
# define DOWN -1
# define RIGHT 1
# define LEFT -1

# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define KEY_A 0
# define KEY_W 13
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_color
{
	int	*f;
	int	*c;
}	t_color;

typedef struct s_angle
{
	double	x;
	double	y;
}	t_angle;

typedef struct s_ray
{
	int		is_up;
	double	dest;
	int		is_down;
	int		is_right;
	int		is_left;
	int		texture_width;
	int		texture_height;
	double	wall_height;
	int		vertical;
	int		texture_y;
	int		texture_x;
	double	wall_x;
	double	wall_y;
}	t_ray;

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
	int		width;
	int		height;
}	t_xpm;

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
	t_ray		ray;
	t_xpm		*xpm;
}	t_mlx;

typedef struct s_rays
{
	double	start_x;
	double	start_y;
	double	step_x;
	double	step_y;
	double	hor_x;
	double	hor_y;
	double	ver_x;
	double	ver_y;
	double	ver_dest;
	double	hor_dest;
	double	col;
	double	ray_angle;
	double	dest_project_plane;
	double	new_dest;
	double	top_pixel;
	double	bottom_pixel;
	double	fov;
	double	angle_increment;
}	t_rays;

int		skip_spaces(const char *str);
void	mlx_put(t_mlx *mlx, int x, int y, int color);
void	ft_free_split(char **split);
int		create_rgb(int *color);
int		ft_close_hook(t_mlx *mlx);
void	ft_del(void *ptr);
int		skip_spaces(const char *str);
void	mlx_put(t_mlx *mlx, int x, int y, int color);
int		create_rgb(int *color);
int		ft_key_hook(int key, t_mlx *mlx);
int		check_map(const char *path, t_mlx *mlx);
t_list	*read_map(const char *path);
t_list	*check_empty_line(t_list *lst);
int		check_color_string(const char *line);
int		check_color_int(char **split, t_mlx *mlx, char c);
int		check_color(const char *line, t_mlx *mlx, char c);
int		check_texture(const char *line, t_mlx *mlx, char c);
int		check_valid_map(t_mlx *mlx, char *curr, char *next, int tmp[2]);
t_list	*check_empty_line(t_list *map);
t_list	*read_map(const char *path);
int		check_first_lines(const char *line, t_mlx *mlx);
int		check_first_and_last_line(t_list *list);
void	draw_map(t_mlx *mlx, int player);
char	**get_map(t_list *lst);
void	draw_player(t_mlx *mlx);
int		is_wall(t_mlx *mlx, int x, int y);
int		mlx_get_color(t_xpm *xpm, int x, int y);
double	uniform_angle(double angle);
t_list	*skip_first_lines(t_list *list);
void	draw_square(t_mlx *mlx, int i, int j, int color);
void	get_player_postion(t_mlx *mlx);
int		get_deroction(t_mlx *mlx);
void	draw_wall(t_mlx *mlx, int top, int bottom, int col);
void	draw_floor(t_mlx *mlx, int bottom, int col);
void	draw_ceiling(t_mlx *mlx, int top, int col);
t_xpm	*get_textures(t_mlx *mlx);
double	dest_point(double x1, double y1, double x2, double y2);
double	horezontal(t_mlx *mlx, double *hor_x, double *hor_y, double angle);
double	vertical(t_mlx *mlx, double *ver_x, double *ver_y, double angle);
double	cast_rays(t_mlx *mlx, double angle);
void	rays_casting(t_mlx *mlx);

#endif