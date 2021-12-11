/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:52:46 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/11 18:35:09 by 1mthe0wl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"
#include <stdlib.h>

/*
 * The entry of the program, we first handle the arguments,
 * then once everything is initialized perfectly we begin with mlx.
 */

int	main(int argc, char **argv)
{
	t_map	*map;

	map = NULL;
	handle_args(&map, argc, argv);
	mlx_main(map);
	return (0);
}
