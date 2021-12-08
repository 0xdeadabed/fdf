/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:53:12 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/08 12:43:45 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libft/incs/libft.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_map
{
	int	w;
	int	h;
	int	**z_mt;
	int	**clrs;
}	t_map;

// Map utils
t_map	*init_map(char *file);
void	alloc_map(t_map *map);

// Error
void	perror_exit(const char *str);
void	print_error(char *str);
void	malloc_error(void);
#endif
