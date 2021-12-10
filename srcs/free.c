/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:10:45 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/10 17:50:04 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->z_matrix)
	{
		i = -1;
		while (++i < map->h)
		{
			if (map->z_matrix[i])
				free(map->z_matrix[i]);
		}
		free(map->z_matrix);
	}
	if (map->colors)
	{
		i = -1;
		while (++i < map->h)
		{
			if (map->colors[i])
				free(map->colors[i]);
		}
		free(map->colors);
	}
	free(map);
}

void	free_all(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img->img);
	free_map(vars->map);
	if (vars->img)
		free(vars->img);
	free(vars);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
