/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:19:28 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/10 15:25:36 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	zoom(int keycode, t_vars *vars)
{
	if (keycode == K_DOWN)
	{
		if (vars->zoom > 0)
			vars->zoom -= ZOOM_SHIFT;
	}
	if (keycode == K_UP)
	{
		if (vars->zoom < INT_MAX)
			vars->zoom += ZOOM_SHIFT;
	}
}

void	move(int keycode, t_vars *vars)
{
	if (keycode == K_W)
		vars->shift_y += SHIFT;
	if (keycode == K_S)
		vars->shift_y -= SHIFT;
	if (keycode == K_A)
		vars->shift_x += SHIFT;
	if (keycode == K_D)
		vars->shift_x -= SHIFT;
}

void	flattening(int keycode, t_vars *vars)
{
	if (keycode == K_PLUS)
	{
		if (vars->flat < 10)
			vars->flat += 0.1;
	}
	if (keycode == K_MENU)
	{
		if (vars->flat > 0)
			vars->flat -= 0.1;
	}
}

void	rotation(int keycode, t_vars *vars)
{
	if (keycode == K_U)
		vars->rot_x += ROT_SHIFT;
	if (keycode == K_J)
		vars->rot_x -= ROT_SHIFT;
	if (keycode == K_I)
		vars->rot_y += ROT_SHIFT;
	if (keycode == K_K)
		vars->rot_y -= ROT_SHIFT;
	if (keycode == K_O)
		vars->rot_z += ROT_SHIFT;
	if (keycode == K_L)
		vars->rot_z -= ROT_SHIFT;
}
