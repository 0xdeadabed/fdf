/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:41:07 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/13 12:17:12 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

static int	slope(int i)
{
	if (i < 0)
		return (-(i));
	return (i);
}

/*
 * Verify the slope to determine wheather increment y or not.
 */

void	init_bresenham(t_point *start, t_point *end, t_point *delta,
		t_point *sign)
{
	delta->x = slope(end->x - start->x);
	delta->y = slope(end->y - start->y);
	sign->x = -1;
	sign->y = -1;
	if (start->x < end->x)
		sign->x = 1;
	if (start->y < end->y)
		sign->y = 1;
}

/*
 * Generalized bresenham algorithm.
 * Decide to wheather increent y or not, 
 * x will be always incremented.
 */

void	bresenham(t_vars *vars, t_point start, t_point end)
{
	t_point	current;
	t_point	sign;
	t_point	delta;
	int		line;
	int		tmp;

	init_bresenham(&start, &end, &delta, &sign);
	line = delta.x - delta.y;
	current = start;
	while (current.x != end.x || current.y != end.y)
	{
		img_pixel_put(vars, current.x, current.y,
			get_color(current, start, end, delta));
		tmp = line * 2;
		if (tmp > -delta.y)
		{
			line -= delta.y;
			current.x += sign.x;
		}
		if (tmp < delta.x)
		{
			line += delta.x;
			current.y += sign.y;
		}
	}
}

/*
 * Simply get the coordinates for the given vectors.
 */

t_point	get_coordinates(t_vars *vars, t_point point)
{
	point.x *= vars->zoom;
	point.y *= vars->zoom;
	point.z *= (vars->zoom / 10) * vars->flat;
	rotate_x(vars, &point.y, &point.z);
	rotate_y(vars, &point.x, &point.z);
	rotate_z(vars, &point.x, &point.y);
	isometric(vars, &point.x, &point.y, point.z);
	point.x += vars->shift_x;
	point.y += vars->shift_y;
	return (point);
}

/*
 * Set the image to 0, devide the height * width
 * by bytes, 1 bit per pixel.
 * Iterate through y, and iterate through x,
 * while there is width, while there is height, apply the bresenham
 * algorithm if x or y isn't reached the end.
 * Before bresenham starts, it needs the start and end points,
 * therefore we need to call the get_coordinations function
 * with all the neccessire vectors.
 */

void	draw(t_vars *vars)
{
	int	x;
	int	y;

	ft_bzero(vars->img->addr, WIN_H * WIN_W * (vars->img->bpp / 8));
	if (vars->zoom)
	{
		y = -1;
		while (++y < vars->map->h)
		{
			x = -1;
			while (++x < vars->map->w)
			{
				if (x < vars->map->w - 1)
					bresenham(vars,
						get_coordinates(vars, get_point(x, y, vars)),
						get_coordinates(vars, get_point(x + 1, y, vars)));
				if (y < vars->map->h - 1)
					bresenham(vars,
						get_coordinates(vars, get_point(x, y, vars)),
						get_coordinates(vars, get_point(x, y + 1, vars)));
			}
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	draw_menu(vars);
}
