/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:21:58 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/16 03:31:03 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	check_map_name(char *av)
{
	char	*ext;
	int		status;

	ext = ft_substr(av, ft_strlen(av) - 4, 4);
	status = ft_strncmp(ext, ".ber", ft_strlen(ext));
	if (status != 0)
	{
		ft_printf("ERROR : Map name incorrect !\n");
		exit (-1);
	}
}

char	**map_valid_dimension(char *av)
{
	char	**map;
	int		fd;
	int		len;
	int		len_check;
	int		index;
	char	*map_tmp;
	char	*tmp1;
	char	*tmp2;
	int		p_status;

	fd = open(av, O_RDONLY);
	tmp1 = get_next_line(fd);
	len = ft_strlen(tmp1);
	index = 0;
	while (tmp1[index])
	{
		if (tmp1[index] != '1')
		{
			ft_printf("ERROR : First wall structure incorrect !\n");
			exit (-1);
		}
		index++;
	}
	map_tmp = ft_strdup(tmp1);
	free (tmp1);
	index = 1;
	len_check = 0;
	p_status = 0;
	while (tmp1 = get_next_line(fd))
	{
		len_check = ft_strlen(tmp1);
		if (len_check != len)
		{
			ft_printf("ERROR : Line lenght incorrect !\n");
			exit (-1);
		}
		if (tmp1[0] != '1' || tmp1[len_check - 2] != '1')
		{
			ft_printf("ERROR : Wall structure incorrect !\n");
			exit (-1);
		}
		while (tmp1[index] && index < len_check - 2)
		{
			if (tmp1[index] != '0' || tmp1[index] != '1' || tmp1[index] != 'C' || tmp1[index] != 'E' || tmp1[index] != 'P')
			{
				ft_printf("ERROR : Map structure incorrect !\n");
				exit (-1);
			}
			if (tmp1[index] == 'P')
			{
				if (p_status != 0)
					p_status += 1;
				else
				{
					ft_printf("ERROR : You only need 1 player !\n");
					exit (-1);
				}
			}
			index++;
		}
		tmp2 = ft_strdup(map_tmp);
		free(map_tmp);
		map_tmp = ft_strjoin(tmp2, tmp1);
		free(tmp1);
		free(tmp2);
	}
}

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

int	main(void)
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