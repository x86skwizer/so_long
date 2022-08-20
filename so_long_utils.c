/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 08:29:41 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/20 03:12:06 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	collect_search(t_data *mlx, char c)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (y < mlx->j)
	{
		x = 0;
		while (x < mlx->i)
		{
			if (mlx->map[y][x] == c)
				i++;
			x++;
		}
		y++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while (str1[i] == str2[i] && (str1[i] != '\0' || str2[i] != '\0')
		&& (i + 1) < n)
		i++;
	return (str1[i] - str2[i]);
}

void	ft_exit(char *message)
{
	ft_printf("%s\n", message);
	exit(-1);
}

int	count_line(char *s)
{
	int	index;

	index = 0;
	while (s[index])
		index++;
	if (s[index - 1] == '\n')
		index--;
	return (index);
}

void	save_line(char **dist, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(*dist, line);
	free(*dist);
	*dist = tmp;
}
