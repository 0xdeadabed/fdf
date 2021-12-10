/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:24:42 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/10 17:26:10 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

static double	percent(int start, int end, int current)
{
	double	place;
	double	distance;

	place = current - start;
	distance = end - start;
	if (!distance)
		return (1.0);
	return (place / distance);
}

static int	get_light(int start, int end, double percent)
{
	return ((int)((1 - percent) * start + percent * end));
}

int	get_color(t_point current, t_point start, t_point end, t_point delta)
{
	int		r;
	int		g;
	int		b;
	double	percentage;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	r = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
	g = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
	b = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((r << 16) | (g << 8) | b);
}

int	get_z_color(t_vars *vars, int current_z)
{
	double percentage;

	percentage = percent(vars->map->min_z, vars->map->max_z, current_z);
	if (percentage < 0.2)
		return (COLOR_1);
	else if (percentage < 0.4)
		return (COLOR_2);
	else if (percentage < 0.6)
		return (COLOR_3);
	else if (percentage < 0.8)
		return (COLOR_4);
	else
		return (COLOR_5);
}
