/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:21:58 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/17 21:21:40 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

// check line format
int check_line(char *line, int len, int *player)
{

	int index = 0;

	// start with 1 and end with 1
	if (line[0] != '1' || line[len - 2] != '1')
		return -1;
	// check valid characters
	while (line[index])
	{
		if (line[index] != '0' && line[index] != '1' && line[index] != 'C' && line[index] != 'E' && line[index] != 'P')
			return -1;
		// player
		if (line[index] == 'P')
		{
			if (*player != 0)
				*player += 1;
			else
				return -1;
		}
	}
	return 0;
}

// check walls (first line and last line)
int check_wall(char *line)
{

	int index = 0;

	while (line[index])
	{
		if (line[index] != '1')
			return -1;
		index++;
	}
	return 0;
}

/*

-> check file and file extension

-> while (line) {
	-> check line
	if line is not valid
		-> error
	else
		-> save line
	-> go to next line
}

split all saved lines to 2D array

map = split(lines);

check first line and last line

check_wall(map[0]) && check_wall(map[n])
if not valid error

return map;

*/

int check_map_file(char *av)
{
	char *ext;
	int status;
	int fd;

	ext = ft_substr(av, ft_strlen(av) - 4, 4);
	status = ft_strncmp(ext, ".ber", ft_strlen(ext));
	// check file
	fd = open(av, O_RDONLY);
	if (status != 0 || fd == -1)
	{
		printf("ERROR : Map name incorrect !\n");
		exit(-1);
	}
	return fd;
}

void ft_exit(char *message)
{
	printf("%s\n", message);
	exit(-1);
}

int count_line(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	if (s[i - 1] == '\n')
		i--;
	return i;
}

void save_line(char *dist, char *line)
{
	char *tmp;
	tmp = ft_strjoin(dist, line);
	free(dist);
	dist = tmp;
}

char **map_valid_dimension(char *av)
{
	char **map;
	char *saved_lines;
	char *line;
	int fd;
	int len;
	int p_status;
	int ret;

	p_status = 0;
	len = 0;
	saved_lines = ft_strdup("");
	fd = check_map_file(av);

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (len == 0)
			len = count_line(line);
		else if (len != count_line(line))
			ft_exit("lines...");
		// check line
		ret = check_line(line, len, &p_status);
		if (ret == -1)
			ft_exit("invalid map structure");
		// save line
		save_line(saved_lines, line);
		free(line);
	}
	map = ft_split(saved_lines, '\n');
	return (map);
}

// int key_hook(int key, t_data *mlx)
// {
// 	printf("key : %d\n", key);
// 	mlx->x += 100;
// 	mlx_destroy_image(mlx->ptr, mlx->img);
// 	mlx_clear_window(mlx->ptr, mlx->win);
// 	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./ralph.xpm", &mlx->img_width, &mlx->img_height);
// 	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, mlx->x, mlx->y);
// 	return 0;
// }

int main(int ac, char **av)
{
	// t_data	mlx;
	// char	*relative_path;

	// mlx.x = 100;
	// mlx.y = 100;
	// mlx.win_width = 600;
	// mlx.win_height = 600;

	// mlx.ptr = mlx_init();
	// relative_path = "./ralph.xpm";
	// mlx.win = mlx_new_window(mlx.ptr, mlx.win_width, mlx.win_height, "so_long");
	// mlx.img = mlx_xpm_file_to_image(mlx.ptr, relative_path, &mlx.img_width, &mlx.img_height);
	// mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 100, 100);
	// mlx_key_hook(mlx.win, key_hook, &mlx);
	// mlx_loop(mlx.ptr);

	char **map = map_valid_dimension(av[1]);
	int index = 0;
	while (map[index])
	{
		printf("%s\n", map[index]);
		index++;
	}
	return 0;
}