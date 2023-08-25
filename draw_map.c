/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:54:54 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/08/25 20:43:10 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mlx_get_color(t_mlx *mlx, int x, int y)
{
	char	*dst;

	dst = mlx->xpm.addr + (y * mlx->xpm.line_lenght + x * (mlx->xpm.bits_per_pixel / 8));
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

// DDA Function for line generation
void	DDA(t_mlx *mlx, int X0, int Y0, int X1, int Y1, int color)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    double Xinc = dx / (double)steps;
    double Yinc = dy / (double)steps;
 
    // Put pixel for each step
    double X = X0;
    double Y = Y0;
    for (int i = 0; i <= steps; i++) {
        mlx_put(mlx, round(X), round(Y), color);
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
	// char	*line;
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

// function to draw mini map please call this function after finish the ray casting.
void	draw_mini_map(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	while (mlx->map[i])	
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (mlx->map[i][j] == '1')
				draw_square(mlx, i, j, 0x979A9A);
			else if (mlx->map[i][j] == '0' || ft_strchr("NWSE", mlx->map[i][j]))
				draw_square(mlx, i, j, 0x000000);
			j++;
		}
		i++;
	}
	draw_player(mlx);
}

void	get_player_postion(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (mlx->map[i])	
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (ft_strchr("NWSE", mlx->map[i][j]))
			{
				mlx->player.x = (j * TAIL_SIZE) + TAIL_SIZE / 2;
				mlx->player.y = (i * TAIL_SIZE) + TAIL_SIZE / 2;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	is_wall(t_mlx *mlx, int x, int y)
{
	int len = 0;
	if (x < 0 || y < 0 || x > mlx->width || y > mlx->height)
	{
		return (-1);
	}
	while (mlx->map[len])
		len++;
	if (y >= len)
		return (-1);
	if (x >= (int )ft_strlen(mlx->map[y]))
		return (-1);
	if (mlx->map[y][x] == '1')
		return (1);
	return (0);
}

double dest_point(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 -y1)));	
}

double	horezontal(t_mlx *mlx, double *hor_x, double *hor_y, double angle)
{
	double start_x, start_y;
	double step_x, step_y;
	int check = 0;

	start_y = ((int)(mlx->player.y) / TAIL_SIZE) * TAIL_SIZE;
	start_y += mlx->ray.is_down ? TAIL_SIZE : 0;
	start_x = (int)(mlx->player.x) + (start_y - (int)(mlx->player.y)) / tan(angle);

	step_y = TAIL_SIZE;
	// step_y *= mlx->ray.is_up ? -1 : 1;
	step_y *= 1 - 2 * (mlx->ray.is_up != 0);
	step_x = TAIL_SIZE / tan(angle);
	step_x *= (mlx->ray.is_left && step_x > 0) ? -1 : 1;
	step_x *= (mlx->ray.is_right && step_x < 0) ? -1 : 1;
	while (1)
	{
		if (mlx->ray.is_up)
			check = is_wall(mlx, start_x / TAIL_SIZE, (start_y - 1) / TAIL_SIZE);
		else 
			check = is_wall(mlx, start_x / TAIL_SIZE, start_y / TAIL_SIZE);
		if (check == 1)
		{
			*hor_x = start_x;
			*hor_y = start_y;
			break ;
		}
		else if (check == -1)
			break ;
		start_x += step_x;
		start_y += step_y;
	}
	return (dest_point(mlx->player.x, mlx->player.y, *hor_x, *hor_y));
}

double	vertical(t_mlx *mlx, double *ver_x, double *ver_y, double angle)
{
	double start_x, start_y;
	double step_x, step_y;
	int check = 0;

	start_x = ((int)(mlx->player.x) / TAIL_SIZE) * TAIL_SIZE;
	start_x += mlx->ray.is_right ? TAIL_SIZE : 0;
	start_y = (int)(mlx->player.y) + (start_x - (int)(mlx->player.x)) * tan(angle);
	
	step_x = TAIL_SIZE;
	step_x *= mlx->ray.is_left ? -1 : 1;
	step_y = TAIL_SIZE * tan(angle);
	step_y *= mlx->ray.is_up && step_y > 0 ? -1 : 1;
	step_y *= mlx->ray.is_down && step_y < 0 ? -1 : 1;
	while (1)
	{
		if (mlx->ray.is_left)
			check = is_wall(mlx, (start_x - 1) / TAIL_SIZE, start_y / TAIL_SIZE);
		else 
			check = is_wall(mlx, start_x / TAIL_SIZE, start_y / TAIL_SIZE);
		if (check == 1)
		{
			*ver_x = start_x;
			*ver_y = start_y;
			break ;
		}
		else if (check == -1)
			break ;
		start_x += step_x;
		start_y += step_y;
	}
	return (dest_point(mlx->player.x, mlx->player.y, *ver_x, *ver_y));
}

double	cast_rays(t_mlx *mlx, double angle)
{
	double	hor_x;
	double	hor_y;
	double	ver_x;
	double	ver_y;
	double	ver_dest;
	double	hor_dest;

	mlx->ray.is_down = angle > 0 && angle < M_PI;
	mlx->ray.is_up = !mlx->ray.is_down;

	mlx->ray.is_right = angle < M_PI / 2.0 || angle > 3.0 * M_PI / 2.0;
	mlx->ray.is_left = !mlx->ray.is_right;
	
	hor_x = mlx->width;
	hor_y = mlx->height;
	ver_x = mlx->width;
	ver_y = mlx->height;
	
	hor_dest = horezontal(mlx, &hor_x, &hor_y, angle);
	ver_dest = vertical(mlx, &ver_x, &ver_y, angle);
	if (ver_dest < hor_dest)
	{
		mlx->ray.vertical = 1;
		mlx->ray.wall_x = ver_x;
		mlx->ray.wall_y = ver_y;
		return (ver_dest);
	}
	else
	{
		mlx->ray.vertical = 0;
		mlx->ray.wall_x = hor_x;
		mlx->ray.wall_y = hor_y;
		return (hor_dest);
	}
}

void	draw_angle(t_mlx *mlx)
{
	double	x;
	double	y;

	x = cos(mlx->player.rotate) * TAIL_SIZE;
	y = sin(mlx->player.rotate) * TAIL_SIZE;
	DDA(mlx, mlx->player.x, mlx->player.y, mlx->player.x + x, mlx->player.y + y, 0xE74C3C);
}

void	draw_wall(t_mlx *mlx, int top, int bottom, int col)
{
	int i;
	
	i = top;
	while (i < bottom)
	{
		mlx->ray.texture_y = (i - top) * ((float)mlx->ray.texture_height / mlx->ray.wall_height);
		// printf("%d %d\n", mlx->ray.texture_x, mlx->ray.texture_y);
		// if ((mlx->ray.texture_x > 0 && mlx->ray.texture_x < mlx->ray.texture_width) && (mlx->ray.texture_y > 0 && mlx->ray.texture_y < mlx->ray.texture_height))
		mlx_put(mlx, col, i, 0xE74C3C);
		i++;
	}
}

void	draw_floor(t_mlx *mlx, int bottom, int col)
{
	while (bottom < mlx->height)
	{
		mlx_put_rgb(mlx, col, bottom, mlx->color.f);
		bottom++;
	}
}

void	draw_ceiling(t_mlx *mlx, int top, int col)
{
	while (top >= 0)
	{
		mlx_put_rgb(mlx, col, top, mlx->color.c);
		top--;
	}
}

void	rays_casting(t_mlx *mlx)
{
	double	col;
	double	ray_angle;
	double	dest;
	double	dest_project_plane;
	double	new_dest;
	double	top_pixel;
	double	bottom_pixel;

	col = 0;
	ray_angle = mlx->player.rotate - (FOV / 2);
	dest_project_plane = (mlx->height / 2) / tan(FOV / 2);
	while (col < RAYS)
	{
		// get the smallest destion of ray 
		dest = cast_rays(mlx, uniform_angle(ray_angle));
		
		// get the new destion with cos
		new_dest = dest * cos(ray_angle - mlx->player.rotate);
		
		// get the wall height
		mlx->ray.wall_height = (TAIL_SIZE / new_dest) * dest_project_plane;
		top_pixel = (mlx->height / 2) - (mlx->ray.wall_height / 2);
		
		if (top_pixel < 0)
			top_pixel = 0;
		bottom_pixel = (mlx->height / 2) + (mlx->ray.wall_height / 2);
		if (bottom_pixel > mlx->height)
			bottom_pixel = mlx->height;
		draw_ceiling(mlx, top_pixel, col);
		mlx->ray.texture_x = (int)mlx->ray.wall_x / TAIL_SIZE;
		if (mlx->ray.vertical)
			mlx->ray.texture_x = (int)mlx->ray.wall_y / TAIL_SIZE;
		draw_wall(mlx, top_pixel, bottom_pixel, col);
		draw_floor(mlx, bottom_pixel, col);
		ray_angle += ANGLE_INCREMENT;
		col++;
	}
}

void	draw_player(t_mlx *mlx)
{
	int x = -2;
	int y = -2;

	while (x < 2)
	{
		y = -2;
		while (y < 2)
		{
			mlx_put(mlx, mlx->player.x + y, mlx->player.y + x, 0xE74C3C);
			y++;
		}
		x++;
	}
	draw_angle(mlx);
}

void    draw_map(t_mlx *mlx, int player)
{
	t_list	*lst;
	
	if (mlx->img == NULL)
	{
		mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
		mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_lenght, &mlx->endian);
	}
	lst = mlx->lst;
	if (player)
		get_player_postion(mlx);
	rays_casting(mlx);
	draw_mini_map(mlx);
	mlx->xpm.img = mlx_xpm_file_to_image(mlx->mlx, "img/image.xpm", &mlx->ray.texture_width, &mlx->ray.texture_height);
	mlx->xpm.addr = mlx_get_data_addr(mlx->xpm.img, &mlx->xpm.bits_per_pixel, &mlx->xpm.line_lenght, &mlx->xpm.endian);
	// int color = mlx_get_color(mlx, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_ptr, 0, 0);
}