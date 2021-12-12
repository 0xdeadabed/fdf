/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:31:09 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/12 18:50:02 by 1mthe0wl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

/*
 * ft_atoi_base: takes a string and a base, it simply changes the string
 * to number according to the given base.
 */

static int	parse_color(t_map *map, char *s)
{
	while (*s && (ft_isdigit(*s) || *s == '-' || *s == '+' || *s == '.'))
		s++;
	if (*s && *s == 'x')
	{
		map->iscolor = 1;
		while (++s)
		{
			ft_tolower(*s);
		}
		return (ft_atoi_base(s + 1, LHEX));
	}
	else
		return (WHITE);
	return (0);
}

/*
 * From the map file, take the X, Y, Z and put them on the matrix.
 */

static void	fill_matrix(t_map *map, int fd)
{
	int		x;
	int		y;
	char	*line;
	char	**split;

	y = -1;
	while (++y < map->h)
	{
		line = get_next_line(fd);
		split = ft_split(line, ' ');
		if (!split)
		{
			free_map(map);
			malloc_error();
		}
		x = -1;
		while (++x < map->w)
		{
			map->z_matrix[y][x] = ft_atoi(split[x]);
			map->colors[y][x] = parse_color(map, split[x]);
		}
		free_split(split);
		free(line);
	}
}

/*
 * We want to have the min and max Z in advance so we after can
 * reuse them to nicely coloring by altitude.
 */

void	get_z(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->h)
	{
		x = -1;
		while (++x < map->w)
		{
			if (map->z_matrix[y][x] < map->min_z)
				map->min_z = map->z_matrix[y][x];
			else if (map->z_matrix[y][x] > map->max_z)
				map->max_z = map->z_matrix[y][x];
		}
	}
}

/*
 * Checks the number of arguments, if everything is fine,
 * then initializes the map according to the given argument (The path of the map),
 * We basically looking for the size of X and Y.
 * Allocate memory for the map's size.
 * fill the matrix.
 */

void	handle_args(t_map **map, int argc, char **argv)
{
	char	*file;
	int		fd;

	if (argc != 2)
		print_error("Invalid argument number.");
	file = argv[1];
	*map = init_map(file);
	alloc_map(*map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free_map(*map);
		print_error("Error while opening the map :(");
	}
	fill_matrix(*map, fd);
	close(fd);
	get_z(*map);
}
