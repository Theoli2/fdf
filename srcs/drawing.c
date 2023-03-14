/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 05:30:23 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/14 20:08:36 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

int	absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	sign(int n)
{
	return ((n > 0) - (n < 0));
}

void	putline(t_drawing draw, t_img img, int color)
{
	(void)color;
	draw.dx = absolute(draw.x1 - draw.x0);
	draw.sx = sign (draw.x1 - draw.x0);
	draw.dy = -absolute(draw.y1 - draw.y0);
	draw.sy = sign (draw.y1 - draw.y0);
	draw.error = draw.dx + draw.dy;
	while (1)
	{
		my_mlx_pixel_put(&img, draw.x0, draw.y0, color);
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

int	drawing(t_data *data)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	data->offset_x = WIDTH / data->width;
	data->offset_y = data->offset_x / 2;
	printf("lowest = %i, tallest = %i\n", data->draw.lowest, data->draw.tallest);
	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(&data->img, x, y, 0);
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	y = 0;
	x = drawing_bis(data, x, y);
	while (y < data->height - 1)
	{
		data->draw.x0 = calculate_x(data->offset_x, data->tab[x][y], *data);
		data->draw.y0 = calculate_y(data->offset_y, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x][y + 1], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x][y + 1], *data);
		putline(data->draw, data->img, get_perfect_gradient(data, data->tab[x][y].z));
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	return (0);
}
