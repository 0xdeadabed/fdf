/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:52:46 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/10 17:03:41 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"
#include <stdlib.h>

static void	char_tolower(char *c)
{
	*c = ft_tolower(*c);
}

static int	parse_color(t_map *map, char *s)
{
	while (*s && (ft_isdigit(*s) || *s == '-' || *s == '+' || *s == '.'))
		s++;
	if (*s && *s == 'x')
	{
		map->iscolor = 1;
		ft_striter(s + 1, char_tolower);
		return (ft_atoi_base(s + 1, LHEX));
	}
	else
		return (WHITE);
	return (0);
}

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

static void	parse(t_map *map, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free_map(map);
		print_error("Error while opening the map");
	}
	fill_matrix(map, fd);
	close(fd);
}

void	handle_args(t_map **map, int argc, char **argv)
{
	char	*file;

	if (argc != 2)
		print_error("Invalid argument number.");
	file = argv[1];
	*map = init_map(file);
	alloc_map(*map);
	parse(*map, file);
	get_z(*map);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	map = NULL;
	handle_args(&map, argc, argv);
	mlx_main(map);
	return (0);
}
