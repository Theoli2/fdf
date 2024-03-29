/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:24:06 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/05 00:53:45 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# define WIDTH 1920
# define HEIGHT 1024
# define HEXA	"0123456789ABCDEF"
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "../libft/libft.h"

//structure qui contient les valeurs rgb
//des pixels
typedef struct s_color
{
	int	d_r;
	int	d_g;
	int	d_b;
	int	r;
	int	g;
	int	b;
}				t_color;

//contient les variables avec les valeurs les 
//plus basses et hautes en hauteur sur la map
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

//contient la couleur apres gradient de chaque point
typedef struct s_vertex {
	int		x;
	int		y;
	int		z;
	int		color;
	int		file_color;
}				t_vertex;

//contient les variables pour les translations, le zoom
//la rotation et la vue parrallele en plus
typedef struct s_data {
	float		width;
	float		height;
	void		*mlx;
	void		*mlx_win;
	int			translatex;
	int			translatey;
	float		zoom;
	float		offset_x;
	float		offset_y;
	int			rotate_x;
	int			parralel;
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
int			drawing_reverse(t_data *data);
int			ft_atoi_base(char *str, char *base);
int			get_perfect_gradient(t_data *data, int alt);
int			line_gradient(t_drawing draw, t_vertex start, t_vertex end);
int			sign(int n);
float		center_x(t_data data);
float		center_y(t_data data);
void		drawing_bis(t_data *data);
void		drawing_parralel(t_data *data);
void		initialize(t_data *data);
void		error_management(t_data *data);
void		get_distance(t_drawing *draw);
void		lowest_tallest(t_data *data);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		putline(t_drawing draw, t_img img, t_vertex start, t_vertex end);
void		reset(t_data *data);
bool		parsing(char *file, t_data *data, t_vertex ***tab);

#endif
