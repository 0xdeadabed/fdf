/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:41:07 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/10 17:33:55 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

static void	draw_menu(t_vars *vars)
{
	int		y;
	void	*mlx;
	void	*win;

	mlx = vars->mlx;
	win = vars->win;
	y = 0;
	mlx_string_put(mlx, win, 15, y += 15, WHITE, "Controls:");
	mlx_string_put(mlx, win, 15, y += 50, WHITE, "Reset: R");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Move: W, A, S, D");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Zoom: Arrows");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Flattening: + / -");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Rotate:");
	mlx_string_put(mlx, win, 30, y += 25, WHITE, "  x (+ / -): U / J");
	mlx_string_put(mlx, win, 30, y += 25, WHITE, "  y (+ / -): I / K");
	mlx_string_put(mlx, win, 30, y += 25, WHITE, "  z (+ / -): O / L");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Toggle Perspective: P");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "(Isometric and Parallel)");
}

static int	slope(int i)
{
	if (i < 0)
		return (-(i));
	return (i);
}

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
		img_pixel_put(vars, current.x, current.y, get_color(current, start, end, delta));
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
					bresenham(vars, get_coordinations(vars, new_point(x, y, vars)),
							get_coordinations(vars, new_point(x + 1, y, vars)));
				if (y < vars->map->h - 1)
					bresenham(vars, get_coordinations(vars, new_point(x, y, vars)),
							get_coordinations(vars, new_point(x, y + 1, vars)));
			}
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	draw_menu(vars);
}
