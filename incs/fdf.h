/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:53:12 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/11 18:40:51 by 1mthe0wl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libft/incs/libft.h"
# include "../libs/libft/incs/libft.h"
# include "../libs/minilibx_macos/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>

# ifndef WIN_H
#  define WIN_H 1080
# endif

# ifndef WIN_W
#  define WIN_W 1080
# endif

# ifndef SHIFT
#  define  SHIFT 10
# endif

# ifndef ROT_SHIFT
#  define ROT_SHIFT 0.5
# endif

# ifndef ZOOM_SHIFT
#  define ZOOM_SHIFT 0.5
# endif

# define LHEX "0123456789abcdef"

# define WHITE 0xFFFFFF

# ifndef COLOR_1
#  define COLOR_1 0x581845
# endif
# ifndef COLOR_2
#  define COLOR_2 0x900C3F
# endif
# ifndef COLOR_3
#  define COLOR_3 0xC70039
# endif
# ifndef COLOR_4
#  define COLOR_4 0xFF5733
# endif
# ifndef COLOR_5
#  define COLOR_5 0xFFC30F
# endif

# ifdef OSX
#  define K_ESC 53
#  define K_UP 126
#  define K_DOWN 125
#  define K_LEFT 123
#  define K_RIGHT 124
#  define K_W 13
#  define K_S 1
#  define K_A 0
#  define K_D 2
#  define K_P 35
#  define K_MINUS 27
#  define K_PLUS 24
#  define K_R 15
#  define K_U 32
#  define K_J 38
#  define K_I 34
#  define K_K 40
#  define K_O 31
#  define K_L 37
# elif LINUX
#  define K_ESC 65307
#  define K_UP 65362
#  define K_DOWN 65364
#  define K_LEFT 65361
#  define K_RIGHT 65363
#  define K_W 119
#  define K_S 115
#  define K_A 97
#  define K_D 100
#  define K_P 112
#  define K_MINUS 45
#  define K_PLUS 61
#  define K_R 114
#  define K_U 117
#  define K_J 106
#  define K_I 105
#  define K_K 107
#  define K_O 111
#  define K_L 108
# else
#  define LINUX
#  define K_ESC 65307
#  define K_UP 65362
#  define K_DOWN 65364
#  define K_LEFT 65361
#  define K_RIGHT 65363
#  define K_W 119
#  define K_S 115
#  define K_A 97
#  define K_D 100
#  define K_P 112
#  define K_MINUS 45
#  define K_PLUS 61
#  define K_R 114
#  define K_U 117
#  define K_J 106
#  define K_I 105
#  define K_K 107
#  define K_O 111
#  define K_L 108
# endif

typedef struct s_point t_point;
typedef struct s_img t_img;
typedef struct s_vars t_vars;
typedef struct s_map t_map;

typedef struct	s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		sz_l;
	int		endian;
}	t_img;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	*img;
	int		shift_x;
	int		shift_y;
	int		iso;
	float	zoom;
	float	flat;
	float	rotate_x;
	float	rotate_y;
	float	rotate_z;
}	t_vars;

/*
 * w = X-axis
 * h = Y-axis
 * z_matrix = Z-axis
 */

typedef struct	s_map
{
	int	w;
	int	h;
	int	**z_matrix;
	int	**colors;
	int	iscolor;
	int	min_z;
	int	max_z;
}	t_map;

// HANDLER
void	handle_args(t_map **map, int argc, char **argv);

// Map utils
t_map	*init_map(char *file);
void	alloc_map(t_map *map);
void	get_z(t_map *map);

// Error
void	perror_exit(const char *str);
void	print_error(char *str);
void	malloc_error(void);

// Free
void	free_map(t_map *map);
void	free_all(t_vars *vars);

// MLX
int	mlx_main(t_map *map);

// MLX_UTILS
void	reset_vars(t_vars *vars);
int		init_vars(t_vars *vars, t_map *map);
void	init_mlx(t_vars *vars);

// COLORS
int	get_color(t_point current, t_point start, t_point end, t_point delta);
int	get_z_color(t_vars *vars, int current_z);

// FREE
void	free_split(char **split);

// DRAW
void	draw(t_vars *vars);

// DRAW_UTILS
void	img_pixel_put(t_vars *vars, int x, int y, int color);
t_point get_coordinations(t_vars *vars, t_point point);
t_point	new_point(int x, int y, t_vars *vars);

// CONTROLS
void	zoom(int keycode, t_vars *vars);
void	move(int keycode, t_vars *vars);
void	flattening(int keycode, t_vars *vars);
void	rotation(int keycode, t_vars *vars);

// HOOKS
int	key_hook(int keycode, t_vars *vars);
int	close_win(t_vars *vars);

#endif
