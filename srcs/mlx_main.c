/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:33:55 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/10 15:18:21 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf"

int	mlx_main(t_map *map)
{
	t_vars	*vars;

	vars = (t_vars *)ft_calloc(1, sizeof(t_vars));
	if (!vars)
		malloc_error();
	if (init_vars(vars, map))
	{
		free_all(vars);
		malloc_error();
	}
	init_mlx(vars);
	mlx_hook(vars->win, w, 1L << 0, key_hook, vars);
	mlx_hook(vars->win, 17, 1L << 17, close_win, vars);
	draw(vars);
	mlx_loop(vars->mlx);
	free_all(vars);
	return (EXIT_SUCCESS);
}
