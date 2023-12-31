/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_closed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:35:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/07 17:15:59 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_border(char **map, int i)
{
	int	j;

	j = -1;
	while (map[i][++j])
		if (map[i][j] == ZERO || map[i][j] == NORTH \
		|| map[i][j] == SOUTH || map[i][j] == EAST \
		|| map[i][j] == WEST || map[i][j] == DOOR)
			return (1);
	return (0);
}

static int	check_line_obj(char c, int obj)
{
	if (obj == 1 && c != WALL)
		return (1);
	if (c != ZERO && c != NORTH && c != SOUTH && c != EAST \
	&& c != WEST && c != WALL && c != DOOR)
		return (1);
	return (0);
}

int	check_line_lim(char **map, int i, int j)
{
	if (j == 1 && (check_line_obj(map[i][0], 1) || \
		check_line_obj(map[i][2], 0) || check_line_obj(map[i + 1][1], 0) || \
		check_line_obj(map[i - 1][1], 0)))
		return (1);
	else if (j == ft_strlen(map[i]) - 2)
		if (check_line_obj(map[i][j - 1], 0) \
	|| check_line_obj(map[i][j + 1], 1) || check_line_obj(map[i + 1][j], 0) \
	|| check_line_obj(map[i - 1][j], 0))
			return (1);
	return (0);
}

int	check_line_mid(char **map, int i, int j)
{
	if (j <= 1 || j >= ft_strlen(map[i]) - 2)
		return (0);
	if (check_line_obj(map[i][j - 1], 0) || check_line_obj(map[i][j + 1], 0 ||
		check_line_obj(map[i - 1][j], 0) || check_line_obj(map[i + 1][j], 0)))
		return (1);
	return (0);
}

int	check_door(char **map, int i, int j, int cols)
{
	if ((j > 0 && map[i][j - 1] == SPACE) \
	|| (j < cols && map[i][j + 1] == SPACE) \
	|| (i > 0 && map[i - 1][j] == SPACE) \
	|| (i < cols && map[i + 1][j] == SPACE))
		return (1);
	return (0);
}
