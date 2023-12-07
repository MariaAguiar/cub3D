/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:15:22 by margarida         #+#    #+#             */
/*   Updated: 2023/12/07 18:38:16 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	sprite_loop(t_cub3d *cub, t_vector *vec, double step)
{
	int		x;
	int		y;
	double	texture_pos;
	int		texture_y;

	x = 0;
	while (x < vec->xf && x * step <= cub->txtrs[SP]->width[cub->level \
	% (cub->txtrs[SP]->levels)])
	{
		y = vec->yi;
		texture_pos = 0;
		while (y < vec->yf && texture_pos <= cub->txtrs[SP]->height[cub->level \
	% (cub->txtrs[SP]->levels)])
		{
			texture_y = (int)texture_pos;
			if (y >= vec->yi && y < WHEI && \
			get_color(cub, SP, x * step, texture_y) != 0)
				my_mlx_pixel_put(cub, vec->xi + x, y, \
				get_color(cub, SP, x * step, texture_y));
			texture_pos += step;
			y++;
		}
		x++;
	}
}

void	draw_sprite(t_cub3d *cub)
{
	double		step;
	t_vector	vec;

	vec.xi = cub->start + WWID / 2;
	vec.yi = WHEI / 2;
	vec.xf = WWID;
	vec.yf = WHEI;
	step = 1.0 * cub->txtrs[SP]->height[cub->level \
		% (cub->txtrs[SP]->levels)] / (vec.yf - vec.yi);
	sprite_loop(cub, &vec, step);
	if (cub->start > 20)
		cub->incr = -1;
	else if (cub->start <= 0)
		cub->incr = 1;
	cub->start += cub->incr;
}

int	move_with_mouse(t_cub3d *cub)
{
	if (cub->mouse_x > WWID / 4 && cub->mouse_x < WWID / 4 * 3 &&
	cub->mouse_y > WHEI / 4 && cub->mouse_y < WHEI / 4 * 3)
	{
		if (cub->mouse_x < WWID / 5 * 2)
			add_player_rot(cub, ARROW_LEFT);
		else if (cub->mouse_x > WWID / 5 * 3)
			add_player_rot(cub, ARROW_RIGHT);
	}
	else
		return (0);
	return (1);
}

int	mouse_position(int x, int y, t_cub3d *cub)
{
	if (cub->mouse_x != x || cub->mouse_y != y)
	{
		remove_player_rot(cub, ARROW_LEFT);
		remove_player_rot(cub, ARROW_RIGHT);
	}
	cub->mouse_x = x;
	cub->mouse_y = y;
	return (1);
}

void	display_in_canvas(t_cub3d *cub)
{
	int	type;

	type = 1;
	while ((cub->elems >> type & 1))
		type++;
	if (type < 6)
		print_err_cub("not enough textures", cub);
	cub->mlx = mlx_init();
	cub->img = mlx_new_image(cub->mlx, WWID, WHEI);
	type = 0;
	while (++type <= cub->tot_txtrs)
		if ((cub->elems >> type & 1))
			if (!fill_txtrs(cub, type - 1, cub->txtrs[type - 1]->levels))
				quits(cub);
	cub->mlx_win = mlx_new_window(cub->mlx, WWID, WHEI, "cub3D");
	cub->addr = mlx_get_data_addr(cub->img, &cub->bpp, \
	&cub->line_length, &cub->endian);
	raycasting(cub);
	redraw_minimap(cub);
	if ((cub->elems >> (SP + 1) & 1))
		draw_sprite(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img, 0, 0);
	mlx_hook(cub->mlx_win, 2, (1L << 0), read_keys, cub);
	mlx_hook(cub->mlx_win, 3, (1L << 1), key_release, cub);
	mlx_hook(cub->mlx_win, 6, (1L << 6), mouse_position, cub);
	mlx_hook(cub->mlx_win, 17, (1L << 1), quits, cub);
	mlx_do_key_autorepeatoff(cub->mlx);
	mlx_loop_hook(cub->mlx, in_key, cub);
	mlx_loop(cub->mlx);
}
