/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_gradient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:57:54 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/17 23:36:30 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	line_gradient(t_drawing draw, t_vertex start, t_vertex end)
{
	int	cur_dist;
	int	d_r;
	int	d_g;
	int	d_b;
	int	r;
	int	g;
	int	b;

	if (draw.is_x)
		cur_dist = absolute(draw.x0 - draw.pos_start);
	else
		cur_dist = -absolute(draw.y0 - draw.pos_start);
	d_r = ((end.color & (255 << 16)) - (start.color & (255 << 16))) >> 16;
	d_g = ((end.color & (255 << 8)) - (start.color & (255 << 8))) >> 8;
	d_b = (end.color & 255) - (start.color & 255);
	if (draw.dist != 0)
	{
		r = ((start.color & (255 << 16)) >> 16) + (d_r * cur_dist / draw.dist);
		g = ((start.color & (255 << 8)) >> 8) + (d_g * cur_dist / draw.dist);
		b = (start.color & 255) + (d_b * cur_dist / draw.dist);
	}
	else
		return (start.color);
	return (b + (g << 8) + (r << 16));
}
