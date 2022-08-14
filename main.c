/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:21:58 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/14 07:52:53 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// int	check_map(av) {get_next_line | check_line_nbrs | check_wall}
// int check_map_name(av)

int	main(int ac, char **av)
{
	t_data	mlx;
	t_img	ralph;
	char	*relative_path;

	mlx.ptr = mlx_init();
	mlx.x_size = 600;
	mlx.y_size = 600;
	relative_path = "./ralph.xpm";
	mlx.win = mlx_new_window(mlx.ptr, mlx.x_size, mlx.y_size, "so_long");
	mlx.img = mlx_new_image(mlx.ptr, mlx.x_size, mlx.y_size);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	ralph.img = mlx_xpm_file_to_image(mlx.ptr, relative_path, &ralph.img_width, &ralph.img_height);
	ralph.addr = mlx_get_data_addr(ralph.img, &ralph.bits_per_pixel, &ralph.line_length, &ralph.endian);
	mlx_put_image_to_window(mlx.ptr, mlx.win, ralph.img, 100, 100);
	mlx_loop(mlx.ptr);
}