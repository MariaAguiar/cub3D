/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_gaze.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:15:01 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/02 14:30:29 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_initial_gaze(t_cub3d *cub, int dist)
{
	cub->gaze_x = cub->player->xi + \
	(cub->player->xf - cub->player->xi) * 0.5;
	cub->gaze_y = cub->player->yi + \
	(cub->player->yf - cub->player->yi) * 0.5;
	if (cub->direction == NNORTH)
		cub->gaze_y -= dist;
	else if (cub->direction == NSOUTH)
		cub->gaze_y += dist;
	else if (cub->direction == NEAST)
		cub->gaze_x += dist;
	else if (cub->direction == NWEST)
		cub->gaze_x -= dist;
}
