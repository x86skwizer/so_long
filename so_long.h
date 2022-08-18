/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 00:44:55 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/18 03:34:33 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libftprintf.h"

typedef struct s_data
{
	void	*ptr;
	void	*win;
	void	*img;
	int		win_width;
	int		win_height;
	int		img_width;
	int		img_height;
	int		x;
	int		y;
}	t_data;

typedef struct s_space
{
	char **map;
	char *saved_lines;
	char *line;
	int fd;
	int len;
	int p_status;
	int ret;
	int counter;
}	t_space;

typedef struct s_counter
{
	int	i;
	int	j;
}	t_counter;


int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif