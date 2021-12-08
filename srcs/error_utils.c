/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:36:24 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/08 12:41:34 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	malloc_error(void)
{
	ft_printf("Memory allocation failed.");
	exit(EXIT_FAILURE);
}

void	print_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

void	perror_exit(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
