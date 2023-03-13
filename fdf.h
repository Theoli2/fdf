/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:24:06 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/09 19:24:00 by tlivroze         ###   ########.fr       */
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
}				t_vertex;

typedef struct s_data {
	int			width;
	int			height;
	void		*mlx;
	void		*mlx_win;
	int			translatex;
	int			translatey;
	float		zoom;
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
int			lowest(int z, t_data data);
int			tallest(int z, t_data data);
int			color_point(int	height, t_data *data);
#endif
