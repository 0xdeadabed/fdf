/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:41:28 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/10 12:22:00 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

int	ft_max(int x, int y)
{
	if (x > y)
		return (a);
	return (b);
}

void	reset_vars(t_vars *vars)
{
	vars->zoom = ft_max((WIN_W / vars->map->w / 2), (WIN_H / vars->map->h) / 2);
	vars->shift_x = WIN_W / 2;
	vars->shift_y = (WIN_H - vars->map->h * vars->zoom) / 2;
	vars->iso = 1;
	vars->flat = 1;
	vars->rotate_x = 0;
	vars->rotate_y = 0;
	vars->rotate_z = 0;
}

int	init_vars(t_vars *vars)
{
	vars->map = map;
	vars->img = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!vars)
		return (1);
	reset_vars(vars);
	return (0);
}

void	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->img->img = mlx_new_image(vars->mx, WIN_W, WIN_H);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bpp, &vars->img->sz_l, &vars->img->endian);
	vars->win = mlx_new_window(vars->mlx, WIN_W, WIN_H, "Fils de fer");
}
