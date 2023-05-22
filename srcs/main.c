/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:30:36 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/22 08:38:24 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

//fonction qui ferme la fenetre, et free tout ce qui a
//ete alloue puis quitte le programme
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

//fonction qui fait certaines actions en fonction
//des touches pressees
int	keys(int keycode, t_data *data)
{
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

//main, appelle toutes les sous fonctions / a la boucle pour la mlx
int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		return (write(1, "invalid amount of parameters\n", 29), 0);
	ft_bzero((void *)&data, sizeof(t_data));
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
