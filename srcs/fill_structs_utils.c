/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:19 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/14 17:57:50 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fill_txtrs_utils1(t_cub3d *cub, int type, int i)
{
	(void)i;
	cub->txtrs[type]->bpp = malloc(sizeof(int) * i);
	if (!cub->txtrs[type]->bpp)
		return (0);
	cub->txtrs[type]->line_length = malloc(sizeof(int) * i);
	if (!cub->txtrs[type]->line_length)
	{
		free(cub->txtrs[type]->bpp);
		return (0);
	}
	cub->txtrs[type]->endian = malloc(sizeof(int) * i);
	if (!cub->txtrs[type]->endian)
	{
		free(cub->txtrs[type]->bpp);
		free(cub->txtrs[type]->line_length);
		return (0);
	}
	cub->txtrs[type]->addrs = malloc(sizeof(char *) * (i + 1));
	if (!cub->txtrs[type]->addrs)
	{
		free(cub->txtrs[type]->bpp);
		free(cub->txtrs[type]->line_length);
		free(cub->txtrs[type]->endian);
		return (0);
	}
	return (1);
}

int	fill_txtrs_utils2(t_cub3d *cub, int type, int i)
{
	int	counter;

	counter = -1;
	while (++counter < i)
	{
		cub->txtrs[type]->imgs[counter] = mlx_xpm_file_to_image(cub->mlx, \
		cub->txtrs[type]->path[counter], \
		&cub->txtrs[type]->width[counter], \
		&cub->txtrs[type]->height[counter]);
		if (!cub->txtrs[type]->imgs[counter])
		{
			while (--counter >= 0)
				mlx_destroy_image(cub->mlx, cub->txtrs[type]->imgs[counter]);
			return (print_err_ret("one or more invalid textures"));
		}
	}
	counter = -1;
	while (++counter < i)
		cub->txtrs[type]->addrs[counter] = \
	mlx_get_data_addr(cub->txtrs[type]->imgs[counter], \
	&cub->txtrs[type]->bpp[counter], &cub->txtrs[type]->line_length[counter], \
	&cub->txtrs[type]->endian[counter]);
	cub->txtrs[type]->addrs[counter] = NULL;
	return (1);
}

int	check_door_txtrs(t_cub3d *cub)
{
	int	i;
	int	j;
	int	doors;

	i = -1;
	doors = 0;
	while (cub->map->map[i++])
	{
		j = -1;
		while (cub->map->map[i][++j])
			if (cub->map->map[i][j] == DOOR)
				doors++;
	}
	if (doors && !cub->txtrs[DO])
		return (print_err_ret("no door textures found"));
	return (1);
}

int	insert_txtrs_utils(t_cub3d *cub, int txtr_type, char *line, int i)
{
	if (i > cub->max_level)
		cub->max_level = i;
	cub->tot_txtrs++;
	register_elem(cub, txtr_type);
	if (txtr_type == F || txtr_type == C)
	{
		if (!parse_colors(cub, line, txtr_type))
			return (0);
	}
	return (1);
}
