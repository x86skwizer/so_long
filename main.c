/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:21:58 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/15 22:32:23 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

// int	check_map_name(char *av)
// {
// 	char	*ext;
// 	int		status;

// 	ext = ft_substr(av, ft_strlen(av) - 4, 4);
// 	status = ft_strncmp(ext, ".ber", ft_strlen(ext));
// 	if (status != 0)
// 		return (-1);
// 	return (0);
// }

// char	**map_valid_dimension(char *av)
// {
// 	char	**map;
// 	int		fd;
// 	int		line;
// 	int		len;
// 	int		len_check;
// 	int		index;

// 	fd = open(av, O_RDONLY);
// 	line = 0;
// 	map[line] = get_next_line(fd);
// 	len = ft_strlen(map[line]);
// 	index = 0;
// 	while (map[line][index])
// 	{
// 		if (map[line][index] != "1")
// 		{
// 			ft_printf("ERROR: Wall structure incorrect !");
// 			return (-1);
// 		}
// 		index++;
// 	}
// 	len_check = 0;
// 	while (map[line])
// 	{
// 		line++;
// 		map[line] = get_next_line(fd);
// 		if (ft_strlen(map[line]) != len)
// 		{
// 			ft_printf("ERROR: Line's lenght incorrect !");
// 			return (-1);
// 		}
// 	}
// }

// int	get_map(char *av)
// {
// 	if (check_map_name(av) != 0)
// 	{
// 		ft_printf("ERROR: Map's name incorrect !");
// 		return (-1);
// 	}
	
// }

int key_hook(int key, t_data *mlx)
{
	printf("key : %d\n", key);
	mlx->x += 100;
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./ralph.xpm", &mlx->img_width, &mlx->img_height);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, mlx->x, mlx->y);
	return 0;
}

int	main(int ac, char **av)
{
	t_data	mlx;
	char	*relative_path;

	mlx.x = 100;
	mlx.y = 100;
	mlx.win_width = 600;
	mlx.win_height = 600;

	mlx.ptr = mlx_init();
	relative_path = "./ralph.xpm";
	mlx.win = mlx_new_window(mlx.ptr, mlx.win_width, mlx.win_height, "so_long");
	mlx.img = mlx_xpm_file_to_image(mlx.ptr, relative_path, &mlx.img_width, &mlx.img_height);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 100, 100);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.ptr);

}