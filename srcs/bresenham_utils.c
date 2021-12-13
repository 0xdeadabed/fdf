/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:18:36 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/13 12:24:23 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

t_point	get_point(int x, int y, t_vars *vars)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = vars->map->z_matrix[y][x];
	if (vars->map->iscolor)
		point.color = vars->map->colors[y][x];
	else
		point.color = get_z_color(vars, point.z);
	return (point);
}

void	isometric(t_vars *vars, int *x, int *y, int z)
{
	int	prev_y;
	int	prev_x;

	if (!vars->iso)
		return ;
	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

void	rotate_x(t_vars *vars, int *y, int *z)
{
	float	prev_y;

	prev_y = *y;
	*y = (prev_y * cos(vars->rotate_x)) + (*z * sin(vars->rotate_x));
	*z = (-prev_y * sin(vars->rotate_x)) + (*z * cos(vars->rotate_x));
}

void	rotate_y(t_vars *vars, int *x, int *z)
{
	float	prev_x;

	prev_x = *x;
	*x = (*x * cos(vars->rotate_y)) + (*z * sin(vars->rotate_y));
	*z = (-prev_x * sin(vars->rotate_y)) + (*z * cos(vars->rotate_y));
}

void	rotate_z(t_vars *vars, int *x, int *y)
{
	float	prev_x;

	prev_x = *x;
	*x = (*x * cos(vars->rotate_z)) - (*y * sin(vars->rotate_z));
	*y = (prev_x * sin(vars->rotate_z)) + (*y * cos(vars->rotate_x));
}
