/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:21:07 by ael-amin          #+#    #+#             */
/*   Updated: 2023/09/01 17:50:29 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char **stock_map(t_list *var)
{
	int i = 0;
	int len = 0;
	char **map;

	while(var && len < 6)
	{
		var = check_line_map(var);
		if(!var)
			break;
		var = var->next;
		len++;
	}
	int count = ft_lstsize(var);
	map = malloc(sizeof(char *) * count + 1);
	if(!map)
		return(NULL);
	while(var && i < count)
	{
		map[i] = ft_strdup(var->content);
		var = var->next;
		i++;
	}
	map[i] = NULL;
	return(map);
}

// void	set_map(t_map *road)
// {
// 	road->map = stock_map(road->coll);
// }
