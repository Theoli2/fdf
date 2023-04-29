/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_parralel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 04:41:13 by tlivroze          #+#    #+#             */
/*   Updated: 2023/04/29 06:38:25 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	calc_para_x(float offset, t_vertex tab, t_data data)
{
	int	res ;

	res = (cos(180 * 3.14 / 180) * offset * \
	tab.x / 2 + data.translatex) * data.zoom + WIDTH / 2 - data.center_map_x;
	return (res);
}

int	calc_para_y(float offset, t_vertex tab, t_data data)
{
	int	res;

	res = -tab.z * 0.30 * offset + data.translatey \
	* data.zoom + HEIGHT / 2;
	return (res);
}

int	drawing_parralel_ter(t_data *data, int x, int y)
{	
	while (y < data->height - 1)
	{
		data->draw.x0 = calc_para_x(data->offset_x, data->tab[x][y], *data);
		data->draw.x1 = calc_para_x(data->offset_x, data->tab[x + 1][y], *data);
		data->draw.y0 = calc_para_y(data->offset_y, data->tab[x][y], *data);
		data->draw.y1 = calc_para_y(data->offset_y, data->tab[x + 1][y], *data);
		putline(data->draw, data->img, data->tab[x][y], data->tab[x + 1][y]);
		data->draw.x1 = calc_para_x(data->offset_x, data->tab[x][y + 1], *data);
		data->draw.y1 = calc_para_y(data->offset_y, data->tab[x][y + 1], *data);
		putline(data->draw, data->img, data->tab[x][y], data->tab[x][y + 1]);
		y++;
	}
	return (y);
}

int	drawing_parralel_bis(t_data *data, int x, int y)
{
	while (x < data->width - 1)
	{
		y = drawing_parralel_ter(data, x, y);
		data->draw.x0 = calc_para_x(data->offset_x, data->tab[x][y], *data);
		data->draw.y0 = calc_para_y(data->offset_y, data->tab[x][y], *data);
		data->draw.x1 = calc_para_x(data->offset_x, data->tab[x + 1][y], *data);
		data->draw.y1 = calc_para_y(data->offset_y, data->tab[x + 1][y], *data);
		putline(data->draw, data->img, data->tab[x][y], data->tab[x + 1][y]);
		y = 0;
		x++;
	}
	return (x);
}

void	drawing_parralel(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	x = drawing_parralel_bis(data, x, y);
	while (y < data->height - 1)
	{
		data->draw.x0 = calc_para_x(data->offset_x, data->tab[x][y], *data);
		data->draw.y0 = calc_para_y(data->offset_y, data->tab[x][y], *data);
		data->draw.x1 = calc_para_x(data->offset_x, data->tab[x][y + 1], *data);
		data->draw.y1 = calc_para_y(data->offset_y, data->tab[x][y + 1], *data);
		putline(data->draw, data->img, data->tab[x][y], data->tab[x][y + 1]);
		y++;
	}
}
