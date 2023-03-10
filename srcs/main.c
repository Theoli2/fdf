/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:49:35 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/13 14:23:37 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

int	keys(int keycode, t_data *data)
{
	printf("%i\n", keycode);
	if (keycode == 65451)
		data->zoom = data->zoom + 0.01;
	if (keycode == 65453)
		data->zoom = data->zoom - 0.01;
	if (keycode == 119)
		data->translatey = data->translatey - 40;
	if (keycode == 115)
		data->translatey = data->translatey + 40;
	if (keycode == 97)
		data->translatex = data->translatex - 40;
	if (keycode == 100)
		data->translatex = data->translatex + 40;
	if (keycode == 65307)
		quit(data);
	return (0);
}

// void	check_matrix(t_data data, t_vertex **tab)
// {
// 	int	a;
// 	int	b;

// 	a = 0;
// 	while (a < data.width)
// 	{
// 		b = 0;
// 		while (b < data.height)
// 		{
// 			printf("%d  ", tab[a][b].z);
// 			b++;
// 		}
// 		printf("\n");
// 		a++;
// 	}
// 	return ;
// }

int	main(int argc, char **argv)
{
	t_data		data;

	(void) argc;
	(void) argv;
	if (argc != 2)
		return (write(1, "invalid amount of parameters\n", 29), 0);
	data.translatex = 0;
	data.translatey = 0;
	data.zoom = 1;
	data.draw.lowest = 0;
	data.draw.tallest = 0;
	parsing (argv[1], &data, &data.tab);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "fdf");
	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
			&data.img.line_length, &data.img.endian);
	mlx_loop_hook(data.mlx, &drawing, &data);
	mlx_hook(data.mlx_win, 17, 0, &quit, &data);
	mlx_hook(data.mlx_win, 2, 1L << 0, &keys, &data);
	mlx_loop(data.mlx);
	return (0);
}

// int main()
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	void	*img;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1000, 1000, "test colors");
// 	img = mlx_new_image(mlx, 1000, 1000);
// 	mlx_put_image_to_window(mlx, mlx_win, img, 0, 0);
// 	for (int i=200; i<600; i++)
// 	{
// 		for (int j=200; j<600; j++)
// 			mlx_pixel_put(mlx, mlx_win, i, j, 0xFFFFFF);
// 	}
// 	mlx_loop(mlx);
// }