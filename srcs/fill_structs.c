/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/07 17:13:03 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**solo_matrix(int rows, int cols)
{
	int		i;
	char	**mat;

	mat = malloc((sizeof(char *) + 1) * rows);
	if (!mat)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		mat[i] = malloc((sizeof(char) + 1) * cols);
		if (!mat[i])
		{
			i = -1;
			while (mat[++i])
				free(mat[i]);
			free(mat);
			return (NULL);
		}
		i++;
	}
	mat[i] = NULL;
	return (mat);
}

void	insert_map_tail(t_list *list, int *data, int len)
{
	t_node	*new_node;

	new_node = init_node();
	if (!new_node)
		return ;
	new_node->symbol = data;
	new_node->tot_cols = len;
	if (list->tail)
	{
		new_node->prev = list->tail;
		list->tail->next = new_node;
	}
	else
		list->head = new_node;
	list->tail = new_node;
	list->tot_rows++;
}

void	list_to_map(t_list *list, t_cub3d *cub)
{
	t_node	*cur;
	int		i;
	int		f;

	init_matrix(cub, list->tot_rows, cub->map_cols);
	cur = list->head;
	i = 0;
	while (i < cub->map->tot_rows)
	{
		f = -1;
		while (++f < cur->tot_cols)
			cub->map->map[i][f] = cur->symbol[f];
		while (f < cub->map_cols)
			cub->map->map[i][f++] = SPACE;
		cub->map->map[i][f] = '\0';
		free(cur->symbol);
		cur->symbol = NULL;
		cur = cur->next;
		i++;
	}
	destroy_list(list);
}

int	fill_txtrs(t_cub3d *cub, int type, int i)
{
	if (type == F || type == C || type == TOT)
		return (1);
	cub->txtrs[type]->imgs = malloc(sizeof(void *) * i);
	if (!cub->txtrs[type]->imgs)
		return (0);
	cub->txtrs[type]->bpp = malloc(sizeof(int) * i);
	if (!cub->txtrs[type]->bpp)
	{
		free(cub->txtrs[type]->imgs);
		return (0);
	}
	cub->txtrs[type]->line_length = malloc(sizeof(int) * i);
	if (!cub->txtrs[type]->line_length)
	{
		free(cub->txtrs[type]->imgs);
		free(cub->txtrs[type]->bpp);
		return (0);
	}
	if (!fill_txtrs_utils1(cub, type, i) || !fill_txtrs_utils2(cub, type, i))
		return (0);
	return (1);
}

void	insert_txtrs(t_cub3d *cub, char *line, int txtr_type)
{
	char		**split;
	int			i;

	i = 0;
	if (txtr_type > TOT - 1)
		return ;
	else if ((cub->elems >> (txtr_type + 1) & 1))
		print_err_cub("duplicated textures", cub);
	i += ft_strlen(conv_to_txtr_text(txtr_type));
	split = ft_split_spaces(&line[i]);
	if (!split)
		print_err_cub("invalid texture formatting", cub);
	i = mtx_len(split);
	if (!cub->txtrs)
	{
		cub->txtrs = malloc(TOT * sizeof(t_txtrs *));
		if (!cub->txtrs)
			return ;
	}
	cub->txtrs[txtr_type] = init_txtrs(i);
	cub->txtrs[txtr_type]->path = split;
	cub->txtrs[txtr_type]->type = txtr_type;
	cub->txtrs[txtr_type]->levels = i;
	insert_txtrs_utils(cub, txtr_type, line, i);
}
