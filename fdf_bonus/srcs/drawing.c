/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 05:30:23 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/05 02:10:05 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

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

//appelle line_gradient en plus quand la fonction pose un pixel
//pour connaitre la couleur de chaque pixel
void	putline_bis(t_drawing draw, t_img img, t_vertex start, t_vertex end)
{
	while (1)
	{
		my_mlx_pixel_put(&img, draw.x0, draw.y0, \
		line_gradient(draw, start, end));
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


void	putline(t_drawing draw, t_img img, t_vertex start, t_vertex end)
{
	draw.dx = absolute(draw.x1 - draw.x0);
	draw.sx = sign (draw.x1 - draw.x0);
	draw.dy = -absolute(draw.y1 - draw.y0);
	draw.sy = sign (draw.y1 - draw.y0);
	draw.error = draw.dx + draw.dy;
	get_distance(&draw);
	putline_bis(draw, img, start, end);
}

//appelle reset, initialize, drawing_reverse et drawing_parallel en plus
int	drawing(t_data *data)
{
	reset(data);
	initialize(data);
	if (data->parralel == 0)
	{
		if (data->rotate_x < 180)
		{
			drawing_bis(data);
		}
		else
			drawing_reverse(data);
	}
	else
		drawing_parralel(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	return (0);
}
