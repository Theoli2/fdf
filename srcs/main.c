/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:49:35 by tlivroze          #+#    #+#             */
/*   Updated: 2023/02/09 15:08:02 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x < 0 || x > LENGTH || y < 0 || y > WIDTH)
// 	{
// 		return ;
// 	}
// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

// int	quit(void)
// {
// 	exit(0);
// 	return (0);
// }

// int	keys(int keycode, void *param)
// {
// 	if (keycode == 65307)
// 		quit();
// 	return (0);
// }

// void	drawing(t_data img)
// {
// 	int					x;
// 	int					y;
// 	unsigned int		red;
// 	unsigned int		green;
// 	unsigned int		blue;
// 	unsigned int		color;

// 	x = 0;
// 	y = 0;
// 	red = 122;
// 	green = 255;
// 	blue = 0;
// 	color = 0;
// 	red <<= 16;
// 	green <<= 8;
// 	while (x < 200)
// 	{
// 		while (y + x < 200)
// 		{
// 			my_mlx_pixel_put(&img, x, y, green);
// 			my_mlx_pixel_put(&img, x + 300, 500 + y, red);
// 			y++;
// 		}
// 		y = 0;
// 		x++;
// 	}
// 	return ;
// }

void    check_matrix(t_vertex **tab, int x, int y)
{
    int	a;
    int	b;

    a = 0;
	while (a < y)
	{
        b = 0;
		while (b < x)
        {
            printf("%d  ", tab[a][b].z);
            // printf("%d  ", tab[a][b].color);
            b++;
        }
        printf("\n");
        a++;
    }
}

int	main(int argc, char **argv)
{
	// t_data		img;
	// void		*mlx;
	// void		*mlx_win;
	t_vertex	**tab;
	int			i;

	(void) argc;
	(void) argv;
	if (argc != 2)
		return (write(1, "not the right amount of parameters\n", 30), 0);
	parsing (argv[1], &tab);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, LENGTH, WIDTH, "fdf");
	// img.img = mlx_new_image(mlx, LENGTH, WIDTH);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	// 		&img.line_length, &img.endian);
	// drawing (img);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_hook(mlx_win, 17, 0, &quit, NULL);
	// mlx_hook(mlx_win, 2, 1L<<0, &keys, NULL);
	// mlx_loop(mlx);
}
