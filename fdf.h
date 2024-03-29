/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:24:06 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/09 22:15:01 by tlivroze         ###   ########.fr       */
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

//struct contenant les variables pour l'affichage
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
	int	dist;
	int	is_x;
	int	pos_start;
}				t_drawing;

//struct contenant les variables pour le parsing
typedef struct s_parse {
	int	k;
	int	l;
}				t_parse;

//struct contenant les variables de l'image
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

//struct contenant les variables de chaque points
typedef struct s_vertex {
	int		x;
	int		y;
	int		z;
	int		file_color;
}				t_vertex;

//struct contenant toute les variables du projet
//et les autres structures
typedef struct s_data {
	float		width;
	float		height;
	void		*mlx;
	void		*mlx_win;
	float		offset_x;
	float		offset_y;
	float		center_map_x;
	float		center_map_y;
	t_vertex	**tab;
	t_drawing	draw;
	t_img		img;
}					t_data;

int			absolute(int i);
int			calculate_x(float offset, t_vertex tab, t_data data);
int			calculate_y(float offset, t_vertex tab, t_data data);
int			drawing(t_data *data);
int			drawing_bis(t_data *data, int x, int y);
int			ft_atoi_base(char *str, char *base);
int			sign(int n);
float		center_x(t_data data);
float		center_y(t_data data);
void		get_distance(t_drawing *draw);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		putline(t_drawing draw, t_img img, t_vertex start);
void		reset(t_data *data);
void		error_management(t_data	*data);
bool		parsing(char *file, t_data *data, t_vertex ***tab);

#endif
