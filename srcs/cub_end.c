/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/26 17:00:39 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_split(char ***split_location)
{
	int		i;
	char	**split;

	split = *split_location;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	*split_location = NULL;
}

void	destroy_list(t_list **list)
{
	t_node	*del;
	t_node	*next;

	if (!list || !(*list))
		return ;
	next = NULL;
	del = (*list)->head;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
	free(*list);
	*list = NULL;
}

void	destroy_txtrs_list(t_all_txtrs **txtrs)
{
	t_txtr	*del;
	t_txtr	*next;

	if (!txtrs || !(*txtrs))
		return ;
	next = NULL;
	del = (*txtrs)->head;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
	free(*txtrs);
	*txtrs = NULL;
}

void	destroy_cub(t_cub3d **cub)
{
	t_map	*matrix;
	int		i;

	if (cub || !(*cub))
		return ;
	if (*cub && (*cub)->map)
	{
		matrix = (*cub)->map;
		i = -1;
		while (++i < matrix->tot_rows)
			free(matrix->map[i]);
		free(matrix);
		matrix = NULL;
		free((*cub)->map);
		(*cub)->map = NULL;
	}
	destroy_txtrs_list(&(*cub)->textures);
	destroy_txtrs_list(&(*cub)->cur_txtrs);
	free((*cub));
}

void	destroy_matrix(t_map **mat)
{
	int	**matrix;
	int	i;

	matrix = (*mat)->map;
	i = -1;
	while (++i < (*mat)->tot_rows)
		free(matrix[i]);
	free(matrix);
	(*mat)->map = NULL;
	free((*mat));
	*mat = NULL;
}
