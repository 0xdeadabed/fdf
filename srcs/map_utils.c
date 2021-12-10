/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:14:16 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/10 17:40:14 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

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

void	alloc_map(t_map *map)
{
	int	i;

	map->z_matrix = (int **)malloc(sizeof(int *) * map->h);
	map->colors = (int **)malloc(sizeof(int *) * map->h);
	if (!map->z_matrix || !map->colors)
	{
		free_map(map);
		ft_printf("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < map->h)
	{
		map->z_matrix[i] = (int *)malloc(sizeof(int) * map->w);
		map->colors[i] = (int *)malloc(sizeof(int) * map->w);
		if (!map->z_matrix[i] || !map->colors[i])
		{
			free_map(map);
			ft_printf("Memory allocation failed!");
			exit(EXIT_FAILURE);
		}
	}
}

static int	count_nbr(t_map *map, char *line)
{
	int		cnt;
	char	**split;

	if (!line)
	{
		free(map);
		ft_printf("Empty map error!");
		exit(EXIT_FAILURE);
	}
	split = ft_split(line, ' ');
	if (!split)
	{
		free_map(map);
		malloc_error();
	}
	cnt = 0;
	while (split[cnt])
		cnt++;
	free(split);
	return (cnt);
}

t_map	*init_map(char *file)
{
	int		fd;
	t_map	*map;
	char	*line;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	map->w = count_nbr(map, line);
	while (line)
	{
		map->h++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (map);
}
