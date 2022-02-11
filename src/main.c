/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:07:41 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/07 16:45:33 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				g_width = 800;
int				g_height = 600;
double			g_aspect = 800.0 / 600.0;
double			g_focal_length = 1.0;
double			g_fov = 100.0;
t_li			*g_li_lst = NULL;
int				g_li_cnt = 0;
t_color			g_ka = 0x00ffffff;
double			g_ka_ratio = 0.05;
t_hittable		*g_obj_lst = NULL;
int				g_obj_cnt = 0;
t_cam			*g_cam_lst = NULL;
int				g_cam_cnt = 0;

void		setpixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int			close_win(int keycode, t_vars *vars)
{
	printf("key %d is pressed.\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (1);
}

int				main(int ac, char **av)
{
	t_vars	vars;
	t_data	img;

	if (ac == 2)
		read_rt(av[1]);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, g_width, g_height, "This is miniRT");
	img.img = mlx_new_image(vars.mlx, g_width, g_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								&img.line_length, &img.endian);
	my_rt(&img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, close_win, &vars);
	mlx_loop(vars.mlx);
}