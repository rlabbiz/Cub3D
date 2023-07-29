/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:47:54 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/07/28 17:32:01 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "libft/libft.h"
# include <mlx.h>
# include <fcntl.h>

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define reset "\e[0m"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	
}	t_texture;

typedef struct s_color
{
	int f[3];
	int c[3];
}	t_color;



#endif