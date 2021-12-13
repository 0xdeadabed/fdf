/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:52:46 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/13 09:54:17 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"
#include <stdlib.h>

/*
 * The entry of the program, we first handle the arguments,
 * once everything is initialized perfectly we begin with mlx.
 */

int	main(int argc, char **argv)
{
	t_map	*map;

	map = NULL;
	handle_args(&map, argc, argv);
	mlx_main(map);
	return (0);
}
