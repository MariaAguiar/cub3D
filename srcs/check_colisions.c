/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colisions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:22:31 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/06 13:18:04 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	player_colision_x(t_cub3d *cub, double dist, int type)
{
	int	y;
	int	y2;
	int	x;

	y = 0;
	x = 0;
	while (x < cub->map->tot_cols - 1 && dist > x + 1)
		x++;
	while (y < cub->map->tot_rows - 1 && y + 1 < cub->player_y - 0.25)
		y++;
	y2 = y;
	while (y2 < cub->map->tot_rows - 1 && y2 + 1 < cub->player_y + 0.25)
		y2++;
	if (y < cub->map->tot_rows && x < cub->map->tot_cols \
	&& cub->map->map[y][x] == type)
		return (reload_player_pos(cub, y, x));
	if (y2 != y && y2 < cub->map->tot_rows && x < \
	cub->map->tot_cols && cub->map->map[y2][x] == type)
		return (reload_player_pos(cub, y2, x));
	return (0);
}

int	player_colision_y(t_cub3d *cub, double dist, int type)
{
	int	y;
	int	x;
	int	x2;

	y = 0;
	x = 0;
	while (y < cub->map->tot_rows - 1 && dist > y + 1)
		y++;
	while (x < cub->map->tot_cols - 1 && x + 1 < cub->player_x - 0.25)
		x++;
	x2 = x;
	while (x2 < cub->map->tot_cols - 1 && x2 + 1 < cub->player_x + 0.25)
		x2++;
	if (y < cub->map->tot_rows && x < cub->map->tot_cols \
	&& cub->map->map[y][x] == type)
		return (reload_player_pos(cub, y, x));
	if (x2 != x && y < cub->map->tot_rows && x2 < \
	cub->map->tot_cols && cub->map->map[y][x2] == type)
		return (reload_player_pos(cub, y, x2));
	return (0);
}

int	check_door_colision(t_cub3d *cub, double distx, double disty)
{
	if (player_colision_x(cub, cub->player_x + 0.25 + distx, DOOR) == 2 \
	|| player_colision_x(cub, cub->player_x - 0.25 + distx, DOOR) == 2 \
	|| player_colision_y(cub, cub->player_y + 0.25 + disty, DOOR) == 2 \
	|| player_colision_y(cub, cub->player_y - 0.25 + disty, DOOR) == 2)
		return (1);
	return (0);
}
