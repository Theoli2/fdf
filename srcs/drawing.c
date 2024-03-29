/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 05:30:23 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/05 00:11:41 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

//fonction qui met les pixels sur l'image avec la bonne couleur
//si les pixels ne sont pas dans l'image ne fait rien
void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	{
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//calcule l'endroit du prochain pixel a mettre sur l'image 
//pour une ligne entre 2 points puis passe au point d'apres
void	putline_bis(t_drawing draw, t_img img, t_vertex start)
{
	while (1)
	{
		my_mlx_pixel_put(&img, draw.x0, draw.y0, start.file_color);
		if (draw.x0 == draw.x1 && draw.y0 == draw.y1)
			break ;
		draw.e2 = 2 * draw.error;
		if (draw.e2 >= draw.dy)
		{
			if (draw.x0 == draw.x1)
				break ;
			draw.error = draw.error + draw.dy;
			draw.x0 = draw.x0 + draw.sx;
		}
		if (draw.e2 <= draw.dx)
		{
			if (draw.y0 == draw.y1)
				break ;
			draw.error = draw.error + draw.dx;
			draw.y0 = draw.y0 + draw.sy;
		}
	}
}

//fonction permettant de mettre les lignes sur l'image
void	putline(t_drawing draw, t_img img, t_vertex start)
{
	draw.dx = absolute(draw.x1 - draw.x0);
	draw.sx = sign (draw.x1 - draw.x0);
	draw.dy = -absolute(draw.y1 - draw.y0);
	draw.sy = sign (draw.y1 - draw.y0);
	draw.error = draw.dx + draw.dy;
	get_distance(&draw);
	putline_bis(draw, img, start);
}

//print le tableau de vertex sur l'image generee par la mlx
//est appellee dans la mlx loop hook
//appelle les fonctions qui calculent le centre de la map /
//les coordonnees de chaque point sur l'image/
//et appelle la fonction qui mets les lignes sur l'image
int	drawing(t_data *data)
{
	int			x;
	int			y;

	data->offset_x = WIDTH / data->width / 2.;
	data->offset_y = data->offset_x / 2.;
	data->center_map_x = center_x(*data);
	data->center_map_y = center_y(*data);
	x = 0;
	y = 0;
	x = drawing_bis(data, x, y);
	while (y < data->height - 1)
	{
		data->draw.x0 = calculate_x(data->offset_x, data->tab[x][y], *data);
		data->draw.y0 = calculate_y(data->offset_y, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x][y + 1], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x][y + 1], *data);
		putline(data->draw, data->img, data->tab[x][y]);
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	return (0);
}
