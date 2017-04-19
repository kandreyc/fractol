/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:13:52 by kandreyc          #+#    #+#             */
/*   Updated: 2017/03/03 18:46:09 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int		mouse_hook(int x, int y, t_session *session)
{
	if (x <= WIDTH && y <= HEIGHT && x > 0 && y > 0)
	{
		MOUSE_X = x;
		MOUSE_Y = abs(y - HEIGHT);
	}
	return (0);
}

static	int		around(t_session *session)
{
	if (LIVE_XY == 1)
	{
		session->tree->phi = (MOUSE_X > WIDTH / 2) ?
		(MOUSE_X - (WIDTH / 2)) * 0.1 : (MOUSE_X - (WIDTH / 2)) * 0.1;
		session->tree->len = (MOUSE_Y) * 0.3;
	}
	reimage(session, 1);
	return (0);
}

static	int		mouse_control(int button, int x, int y, t_session *session)
{
	x *= 1;
	y *= 1;
	tree_control(button, session);
	return (0);
}

void			line_it(t_tree tree, float phi, int i)
{
	tree.max_x = floor(tree.min_x + (tree.len * cos(phi * 0.0174533)));
	tree.max_y = floor(tree.min_y + (-(tree.len) * sin(phi * 0.0174533)));
	straight(&tree);
	tree.min_x = tree.max_x;
	tree.min_y = tree.max_y;
	if (tree.len > tree.max_len)
	{
		tree.len *= 0.7;
		line_it(tree, phi + tree.phi, i + 1);
		line_it(tree, phi - tree.phi, i + 1);
	}
}

int				tree_control(int button, t_session *session)
{
	if (button == 5 || button == 4)
		session->tree->max_len *= (button == 4) ? 1.1 : 0.9;
	else if (button == 76)
	{
		if (LIVE_XY == 1 || LIVE_XY == 0)
			LIVE_XY = (LIVE_XY == 0) ? 1 : 2;
		else if (LIVE_XY == 2)
			LIVE_XY = 1;
	}
	else if (button == 53)
		exit(0);
	(button == 76 || button == 5 || button == 4)
	? mlx_loop_hook(MLX, around, session) : reimage(session, 1);
	reimage(session, 1);
	mlx_key_hook(WIN, tree_control, session);
	mlx_hook(WIN, 6, 0, mouse_hook, session);
	mlx_mouse_hook(WIN, mouse_control, session);
	mlx_loop(MLX);
	return (0);
}
