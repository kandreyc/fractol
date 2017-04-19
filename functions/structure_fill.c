/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 18:04:19 by kandreyc          #+#    #+#             */
/*   Updated: 2017/03/03 18:59:00 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static	void		make_adress(t_session *session, t_fractol *fractol)
{
	fractol->quantity_threads = &(session->threads);
	fractol->data = &(session->data);
	fractol->width = &(session->width);
	fractol->height = &(session->height);
	fractol->mouse_x = &(session->mouse_x);
	fractol->mouse_y = &(session->mouse_y);
	fractol->mouse_live = &(session->mouse_live);
	fractol->min_max_cx = &(session->min_max_cx);
	fractol->min_max_cy = &(session->min_max_cy);
	fractol->color = session->color;
	fractol->color_is = &(session->color_is);
	fractol->max_n = &(session->max_n);
	fractol->scale = &(session->scale);
	fractol->sizeline = &(session->end_bbp_sizeline[2]);
}

static	void		make_threads(t_session *session, int i, int (*f)())
{
	while (++i < session->threads)
	{
		session->fractol[i].thread = i;
		make_adress(session, &(session->fractol[i]));
		session->fractol[i].f = f;
		session->min_max_cx = (float *)malloc(sizeof(float) * 2);
		session->min_max_cy = (float *)malloc(sizeof(float) * 2);
		session->min_max_cx[0] = -2;
		session->min_max_cx[1] = 2;
		session->min_max_cy[0] = -2;
		session->min_max_cy[1] = 2;
	}
}

void				make_tree(t_session *session)
{
	session->tree = (t_tree *)malloc(sizeof(t_tree));
	session->tree->mouse_x = session->mouse_x;
	session->tree->mouse_y = session->mouse_y;
	session->tree->width = &(session->width);
	session->tree->height = &(session->height);
	session->tree->min_x = (*session->tree->width) / 2;
	session->tree->min_y = (*session->tree->height);
	session->tree->max_x = 0;
	session->tree->max_y = 0;
	session->tree->len = 200;
	session->tree->max_len = 5;
	session->tree->phi = 15;
	session->tree->brunch = 4;
	session->tree->data = &(session->data);
	session->tree->sizeline = &(session->end_bbp_sizeline[2]);
}

static	void		color_fill(t_session *session)
{
	session->color = (int *)malloc(sizeof(int) * (10));
	session->color[0] = 0;
	session->color[1] = 16777215;
	session->color[2] = 0;
	session->color[3] = 16770560;
	session->color[4] = 0;
	session->color[5] = 50431;
	session->color[6] = 0;
	session->color[7] = 65476;
	session->color[8] = 0;
	session->color[9] = 16724736;
	session->color[10] = 0;
	session->color[11] = 16742144;
}

t_session			*new_fractol(int threads, int (*f)(), int flag)
{
	t_session	*ses;

	ses = (t_session *)malloc(sizeof(t_session));
	ses->key = 0;
	ses->scale = 1;
	ses->img = NULL;
	ses->data = NULL;
	ses->max_n = 10;
	ses->width = 800;
	ses->height = 800;
	ses->mouse_x = 0;
	ses->mouse_y = 0;
	ses->mouse_live = 0;
	color_fill(ses);
	ses->color_is = 0;
	ses->tree_flag = flag;
	ses->threads = threads;
	ses->fractol = (t_fractol *)malloc(sizeof(t_fractol) * (ses->threads + 1));
	(ses->tree_flag == 0) ? make_threads(ses, -1, f) : make_tree(ses);
	return (ses);
}
