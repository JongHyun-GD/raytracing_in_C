/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 20:58:52 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/15 12:55:25 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef struct		s_vec3
{
	double	x;
	double	y;
	double	z;
}					t_vec3;

t_vec3				vec3_init(double x, double y, double z);
double				vec3_mag(t_vec3 v);
t_vec3				vec3_normalize(t_vec3 v);
t_vec3				vec3_plus(t_vec3 a, t_vec3 b);
t_vec3				vec3_minus(t_vec3 a, t_vec3 b);
t_vec3				vec3_multi(double t, t_vec3 a);
double				vec3_dot(t_vec3 a, t_vec3 b);
t_vec3				vec3_cross(t_vec3 a, t_vec3 b);

#endif
