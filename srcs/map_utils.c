/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:14:16 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/08 12:36:00 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->z_mt)
	{
		i = -1;
		while (++i < map->h)
		{
			if (map->z_mt[i])
				free(map->z_mt[i]);
		}
		free(map->z_mt);
	}
	if (map->clrs)
	{
		i = -1;
		while (++i < map->h)
		{
			if (map->clrs[i])
				free(map->clrs[i]);
		}
		free(map->clrs);
	}
	free(map);
}

void	alloc_map(t_map *map)
{
	int	i;

	map->z_mt = (int **)malloc(sizeof(int *) * map->h);
	map->clrs = (int **)malloc(sizeof(int *) * map->h);
	if (!map->z_mt || !map->clrs)
	{
		free_map(map);
		ft_printf("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < map->h)
	{
		map->z_mt[i] = (int *)malloc(sizeof(int) * map->w);
		map->clrs[i] = (int *)malloc(sizeof(int) * map->w);
		if (!map->z_mt[i] || !map->clrs[i])
		{
			free_map(map);
			ft_printf("Memory allocation failed!");
			exit(EXIT_FAILURE);
		}
	}
}

static int	count_nbr(t_map *map, char *line, char *file)
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
	map->w = count_nbr(map, line, file);
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
