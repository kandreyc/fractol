/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 10:32:27 by kandreyc          #+#    #+#             */
/*   Updated: 2017/04/19 17:53:24 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void				in_cube(float *a, float *b, float *c, float *d)
{
	float	tmp;

	tmp = (*a) * ((*a) * (*a) - 3 * (*b) * (*b));
	(*d) = (*b) * (3 * (*a) * (*a) - (*b) * (*b));
	(*c) = tmp;
}

void				in_square(float *a, float *b)
{
	float	tmp;

	tmp = (((*a) * (*a) - (*b) * (*b)));
	(*b) = ((2 * (*a) * (*b)));
	(*a) = tmp;
}

void				key_define(int button, t_session *session)
{
	if (button == 69 || button == 78)
		KEY = (button == 69) ? 69 : 78;
	else if ((button == 116 || button == 121))
		maxiterations(session, button, 5);
	else if (button == 76)
	{
		if (LIVE_XY == 1 || LIVE_XY == 0)
			LIVE_XY = (LIVE_XY == 0) ? 1 : 2;
		else if (LIVE_XY == 2)
			LIVE_XY = 1;
	}
	else if (button == 126 || button == 125)
		KEY = ((button == 126) ? 126 : 125);
	else if (button == 124 || button == 123)
		KEY = ((button == 124) ? 124 : 123);
	else if (button == 82)
		LIVE_XY = 0;
	else if (button == 53)
		exit(0);
	else if (button == 269)
		KEY = 269;
}

static	void		argv_check(char **av, t_session **ses, int i)
{
	int		threads;
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 800, "Fractol");
	threads = 12;
	if (ft_strcmp(av[i], "1") == 0 || ft_strcmp(av[i], "mandelbrot") == 0)
		*ses = new_fractol(threads, &mandelbrot, 0);
	else if (ft_strcmp(av[i], "2") == 0 || ft_strcmp(av[i], "julia") == 0)
		*ses = new_fractol(threads, &julia, 0);
	else if (ft_strcmp(av[i], "3") == 0 || ft_strcmp(av[i], "sunflower") == 0)
		*ses = new_fractol(threads, &sunflower, 0);
	else if (ft_strcmp(av[i], "4") == 0 || ft_strcmp(av[i], "mandelCube") == 0)
		*ses = new_fractol(threads, &cube_mandelbrot, 0);
	else if (ft_strcmp(av[i], "5") == 0 || ft_strcmp(av[i], "tree") == 0)
		*ses = new_fractol(threads, NULL, 1);
	else
		error(NULL, 1);
	(*ses)->mlx = mlx;
	(*ses)->win = win;
}

int					main(int ac, char **av)
{
	pid_t		pid;
	t_session	*ses;
	int			i;

	i = 0;
	pid = 0;
	ses = NULL;
	if (ac < 2)
		error(NULL, 1);
	else
		while (++i < (ac - 1))
			if ((pid = fork()) == 0)
				break ;
	argv_check(av, &ses, i);
	(ses->tree_flag == 0) ? control(-42, ses) : tree_control(-42, ses);
	return (0);
}
