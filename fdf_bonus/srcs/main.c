/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:30:36 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/22 08:34:38 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

int	quit(t_data *data)
{
	int	i;

	i = 0;
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	while (data->tab && data->tab[i])
	{
		free(data->tab[i]);
		i++;
	}
	free(data->tab);
	exit(0);
	return (0);
}

//verifie que la touche pressee fait partie de cette fonction
//puis permet de changer les variables de translation sur y,
//du zoom et de la vue parrallele
int	keys_bis(int k, t_data *data)
{
	if (k == 65451)
		data->zoom = data->zoom + 0.01;
	if (k == 65453)
		data->zoom = data->zoom - 0.01;
	if (k == 119)
		data->translatey = data->translatey - 40;
	if (k == 115)
		data->translatey = data->translatey + 40;
	if (k == 102)
	{
		if (data->parralel == 0)
			data->parralel = 1;
		else
			data->parralel = 0;
	}
	if (k == 65451 || k == 65453 || k == 119 || k == 115 || k == 102)
		return (1);
	else
		return (0);
}

//permet de changer les variables de translation sur x, de rotation
//et appelle la sous fonction
int	keys(int keycode, t_data *data)
{
	if (keys_bis(keycode, data) == 1)
		return (0);
	if (keycode == 97)
		data->translatex = data->translatex - 40;
	if (keycode == 100)
		data->translatex = data->translatex + 40;
	if (keycode == 113)
	{
		data->rotate_x = data->rotate_x - 1;
		if (data->rotate_x < 0)
			data->rotate_x = 359;
	}
	if (keycode == 101)
	{
		data->rotate_x = data->rotate_x + 1;
		if (data->rotate_x > 359)
			data->rotate_x = 0;
	}
	if (keycode == 65307)
		quit(data);
	return (0);
}

int	mlx_start(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (write(1, "mlx_init failed\n", 16), 0);
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fdf");
	if (data->mlx_win == NULL)
		return (free(data->mlx), write(1, "mlx_new_window failed\n", 22), 0);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img.img == NULL)
	{
		free(data->mlx);
		free(data->mlx_win);
		return (write(1, "mlx_new_image failed\n", 21), 0);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		return (write(1, "invalid amount of parameters\n", 29), 0);
	ft_bzero((void *)&data, sizeof(t_data));
	data.translatex = 0;
	data.translatey = 0;
	data.zoom = 1;
	data.rotate_x = 45;
	data.draw.lowest = 0;
	data.draw.tallest = 0;
	data.parralel = 0;
	if (parsing (argv[1], &data, &data.tab) == false)
		return (1);
	if (mlx_start(&data) == 0)
	{
		error_management(&data);
		return (1);
	}
	mlx_loop_hook(data.mlx, &drawing, &data);
	mlx_hook(data.mlx_win, 17, 0, &quit, &data);
	mlx_hook(data.mlx_win, 2, 1L << 0, &keys, &data);
	mlx_loop(data.mlx);
	return (0);
}
