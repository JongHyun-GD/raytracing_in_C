/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 12:17:17 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/06 12:03:16 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_init(double x, double y, double z)
{
	t_vec3		v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

double	vec3_mag(t_vec3 v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	mag;

	mag = vec3_mag(v);
	v.x /= mag;
	v.y /= mag;
	v.z /= mag;
	return (v);
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_multi(double t, t_vec3 a)
{
	a.x *= t;
	a.y *= t;
	a.z *= t;
	return (a);
}
