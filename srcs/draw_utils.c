/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:43:54 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/10 15:05:17 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	isometric(t_vars *vars, int *x, int *y, int *z)
{
	int	prev_y;
	int	prev_x;

	if (!vars->iso)
		return ;
	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) *  cos(0.523599);
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

void	rot_x(t_vars *vars, int *y, int *z)
{
	float	prev_y;

	prev_y = *y;
	*y = (prev_y * cos(vars->rot_x)) + (*z * sin(vars->rot_x));
	*z = (-prev_y * sin(vars->rot_x)) + (*z * cos(vars->rot_x));
}

void	rot_y(t_vars *vars, int *x, int *z)
{
	float	prev_x;

	prev_x = *x;
	*x = (*x * cos(vars->rot_y)) + (*z * sin(vars->rot_y));
	*z = (-prev_x * sin(vars->rot_y)) + (*z * cos(vars->rot_y));
}

void	rot_z(t_vars *vars, int *x, int *y)
{
	float	prev_x;

	prev_x = *x;
	*x = (*x * cos(vars->rot_z)) - (*y * sin(vars->rot_z));
	*y = (prev_x * sin(vars->rot_z)) + (*z * cos(vars->rot_x));
}

t_point	get_coords(t_vars *vars, t_point point)
{
	point.x *= vars->zoom;
	point.y *= vars->zoom;
	point.z *= (vars->zoom / 10) * vars->flat;
	rot_x(vars, &point.y, &point.z);
	rot_y(vars, &point.x, &point.z);
	rot_z(vars, &point.x, &point.y);
	isometric(vars, &point.x, &point.y, point.z);
	point.x += vars->shift_x;
	point.y += vars->shift_y;
	return (point);
}

void	img_pixel_put(t_vars *vars, int x, int y, int color)
{
	int	pixel;

	if (y  >= WIN_H || x >= WIN_W || y < 0 || x < 0)
		return ;
	pixel = (y * vars->img->sz_l) + (x * (vars->img->bpp / 8));
	if (vars->img->endian == 1)
	{
		vars->img->addr[pixel + 0] = (color >> 24);
		vars->img->addr[pixel + 1] = (color >> 16) & 0xFF;
		vars->img->addr[pixel + 2] = (color >> 8) & 0xFF;
		vars->img->addr[pixel + 3] = (color) & 0xFF;
	}
	else if (vars->img->endian == 0)
	{
		vars->img->addr[pixel + 0] = (color) & 0xFF;
		vars->img->addr[pixel + 1] = (color >> 8) & 0xFF;
		vars->img->addr[pixel + 2] = (color >> 16) & 0xFF;
		vars->img->addr[pixel + 3] = (color >> 24);
	}
}

t_point	new_point(int x, int y, t_vars *vars)
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