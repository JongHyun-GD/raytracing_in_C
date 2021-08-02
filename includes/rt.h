/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 19:25:07 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/15 14:19:19 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# include "info.h"
# include "vec3.h"
# include "ray.h"
# include "color.h"
# include "my_rt.h"
# include "util.h"
# include "read_file.h"
# include "hittable.h"

extern int			g_width;
extern int			g_height;
extern double		g_aspect;
extern double		g_focal_length;
extern double		g_fov;
extern t_li			*g_li_lst;
extern int			g_li_cnt;
extern t_color		g_ka;
extern double		g_ka_ratio;
extern t_hittable	*g_obj_lst;
extern int			g_obj_cnt;
extern t_cam		*g_cam_lst;
extern int			g_cam_cnt;

void			setpixel(t_data *img, int y, int x, int c);
char			**ft_split(const char *s, char d);
void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
t_vec3			axis_angle_rot(t_vec3 v1, t_vec3 v2, t_vec3 src);	
#endif