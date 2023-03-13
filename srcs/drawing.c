/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 05:30:23 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/09 20:02:48 by tlivroze         ###   ########.fr       */
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
	int			offset_x;
	int			offset_y;

	x = 0;
	y = 0;
	offset_x = WIDTH / data->width;
	offset_y = offset_x / 2;
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
	while (x < data->width - 1)
	{
		while (y < data->height - 1)
		{
			data->draw.x0 = calculate_x(offset_x, data->tab[x][y], *data);
			data->draw.x1 = calculate_x(offset_x, data->tab[x + 1][y], *data);
			data->draw.y0 = calculate_y(offset_y, data->tab[x][y], *data);
			data->draw.y1 = calculate_y(offset_y, data->tab[x + 1][y], *data);
			putline(data->draw, data->img, color_point(data->tab[x][y].z, data));
			data->draw.x1 = calculate_x(offset_x, data->tab[x][y + 1], *data);
			data->draw.y1 = calculate_y(offset_y, data->tab[x][y + 1], *data);
			putline(data->draw, data->img, color_point(data->tab[x][y].z, data));
			y++;
		}
		data->draw.x0 = calculate_x(offset_x, data->tab[x][y], *data);
		data->draw.y0 = calculate_y(offset_y, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(offset_x, data->tab[x + 1][y], *data);
		data->draw.y1 = calculate_y(offset_y, data->tab[x + 1][y], *data);
		putline(data->draw, data->img, color_point(data->tab[x][y].z, data));
		y = 0;
		x++;
	}
	while (y < data->height - 1)
	{
		data->draw.x0 = calculate_x(offset_x, data->tab[x][y], *data);
		data->draw.y0 = calculate_y(offset_y, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(offset_x, data->tab[x][y + 1], *data);
		data->draw.y1 = calculate_y(offset_y, data->tab[x][y + 1], *data);
		putline(data->draw, data->img, color_point(data->tab[x][y].z, data));
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	return (0);
}
