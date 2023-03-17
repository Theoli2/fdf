/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:24:06 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/17 21:37:45 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1024
# define HEXA	"0123456789ABCDEF"
# include "minilibx-linux/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_drawing {
	int	error;
	int	sx;
	int	sy;
	int	dx;
	int	dy;
	int	e2;
	int	x0;
	int	y0;
	int	z0;
	int	x1;
	int	y1;
	int	z1;
	int dist;
	int	is_x;
	int pos_start;
	int	lowest;
	int	tallest;
}				t_drawing;

typedef struct s_parse {
	int	k;
	int	l;
}				t_parse;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_vertex {
	int		x;
	int		y;
	int		z;
	int		color;
	int		file_color;
}				t_vertex;

typedef struct s_data {
	int			width;
	int			height;
	void		*mlx;
	void		*mlx_win;
	int			translatex;
	int			translatey;
	float		zoom;
	int			offset_x;
	int			offset_y;
	int			last_y;
	t_vertex	**tab;
	t_drawing	draw;
	t_img		img;
}					t_data;

void		parsing(char *file, t_data *data, t_vertex ***tab);
void		check_matrix(t_data data, t_vertex **tab);
int			ft_atoi_base(char *str, char *base);
int			drawing(t_data *data);
int			calculate_x(int offset, t_vertex tab, t_data data);
int			calculate_y(int offset, t_vertex tab, t_data data);
// int			lowest(int z, t_data data);
// int			tallest(int z, t_data data);
void		lowest_tallest(t_data *data);
int			get_perfect_gradient(t_data *data, int alt);
int			drawing_bis(t_data *data, int x, int y);
int			absolute(int i);
int			line_gradient(t_drawing draw, t_vertex start, t_vertex end);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		putline(t_drawing draw, t_img img, t_vertex start, t_vertex end);
void		reset(t_data *data);

#endif
