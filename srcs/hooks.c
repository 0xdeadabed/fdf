/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:24:36 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/10 17:36:27 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../incs/fdf.h"

int	close_win(t_vars *vars)
{
	free_all(vars);
	exit (EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == K_ESC)
		close_win(vars);
	if (keycode == K_R)
		reset_vars(vars);
	if (keycode == K_W || keycode == K_S
		|| keycode == K_A || keycode == K_D)
		move(keycode, vars);
	if (keycode == K_UP || keycode == K_DOWN)
		zoom(keycode, vars);
	if (keycode == K_U || keycode == K_J || keycode == K_I
		|| keycode == K_K || keycode == K_O || keycode == K_L)
		rotation(keycode, vars);
	if (keycode == K_MINUS || keycode == K_PLUS)
		flattening(keycode, vars);
	if (keycode == K_P)
	{
		if (vars->iso)
			vars->iso = 0;
		else
			vars->iso = 1;
	}
	draw(vars);
	return (0);
}
