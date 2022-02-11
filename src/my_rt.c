/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_rt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 12:48:58 by jongpark          #+#    #+#             */
/*   Updated: 2021/05/07 12:11:52 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_hitinfo	hit_sphere(t_vec3 ro, t_vec3 rd, const t_sp *sp)
{
	t_vec3	oc;
	t_hitinfo	hitinfo;
	double	a;
	double	b;
	double	c;
	double	t;
	
	oc = vec3_minus(ro, sp->pos);
	a = vec3_dot(rd, rd);
	b = 2.0 * vec3_dot(rd, oc);
	c = vec3_dot(oc, oc) - (sp->dm / 2.0) * (sp->dm / 2.0);
	t = b * b - 4 * a * c;
	t = t > 0 ? ((-b - sqrt(t)) / (2.0 * a)) : -1.0;
	hitinfo.t = t;
	hitinfo.kd = sp->kd;
	hitinfo.pos = vec3_plus(ro, vec3_multi(t, rd));
	hitinfo.normal = vec3_normalize(vec3_minus(hitinfo.pos, sp->pos));
	hitinfo.hit_obj = (void *)sp;
	return (hitinfo);
}

t_hitinfo	hit_plane(t_vec3 ro, t_vec3 rd, const t_pl *pl)
{
	t_hitinfo	hi;
	
	if (vec3_dot(pl->normal, rd) != 0)
		hi.t = vec3_dot(pl->normal, vec3_minus(pl->pos, ro)) / vec3_dot(pl->normal, rd);
	else
		hi.t = -1.0;
	hi.pos = vec3_plus(ro, vec3_multi(hi.t, rd));
	hi.kd = pl->kd;
	hi.normal = pl->normal;
	hi.hit_obj = (void *)pl;
	return (hi);
}

t_hitinfo	hit_square(t_vec3 ro, t_vec3 rd, const t_sq *sq)
{
	t_hitinfo	hi;
	t_vec3		pivot[3];
	t_vec3		hv;
	t_vec3		vv;

	pivot[0] = vec3_init(-sq->size/2, -sq->size/2, 0);
	pivot[1] = vec3_init(sq->size/2, -sq->size/2, 0);
	pivot[2] = vec3_init(-sq->size/2, sq->size/2, 0);
	pivot[0] = axis_angle_rot(vec3_init(0, 0, 1), sq->normal, pivot[0]);
	pivot[1] = axis_angle_rot(vec3_init(0, 0, 1), sq->normal, pivot[1]);
	pivot[2] = axis_angle_rot(vec3_init(0, 0, 1), sq->normal, pivot[2]);
	hv = vec3_minus(pivot[1], pivot[0]);
	vv = vec3_minus(pivot[2], pivot[0]);
	if (vec3_dot(sq->normal, rd) != 0)
		hi.t = vec3_dot(sq->normal, vec3_minus(sq->pos, ro)) / vec3_dot(sq->normal, rd);
	else
		hi.t = -1.0;
	hi.pos = vec3_plus(ro, vec3_multi(hi.t, rd));	
	double proj1 = vec3_dot(vec3_minus(hi.pos, sq->pos), vec3_normalize(hv));
	double proj2 = vec3_dot(vec3_minus(hi.pos, sq->pos), vec3_normalize(vv));
	if (proj1 < vec3_mag(hv) && proj1 > 0 && proj2 < vec3_mag(vv) && proj2 > 0)
		hi.t = hi.t;
	else
		hi.t = -1.0;
	hi.kd = sq->kd;
	hi.normal = sq->normal;
	hi.hit_obj = (void *)sq;
	return (hi);
}

t_hitinfo	hit_cylinder(t_vec3 O, t_vec3 D, const t_cy *cy)
{
	t_hitinfo	hi;
	double		disc[4];
	t_vec3		A;
	t_vec3		B;

	//printf("cy %f, %f, %f\n",cy->pos.x,cy->pos.y, cy->pos.z); 
	A = vec3_minus(D, vec3_multi(vec3_dot(D, cy->dir), cy->dir));
	B = vec3_plus(vec3_minus(O, vec3_multi(vec3_dot(O, cy->dir), cy->dir)),
	vec3_multi(vec3_dot(cy->pos, cy->dir), cy->dir));
	disc[0] = vec3_dot(A, A);
	disc[1] = 2.0 * vec3_dot(A, B);
	disc[2] = vec3_dot(B, B) - pow(cy->dm / 2.0, 2);
	disc[3] = pow(disc[1], 2) - (4.0 * disc[0] * disc[2]);
	if (disc[3] < 0)
		hi.t = -1.0;
	else
		hi.t = (-disc[1] - sqrt(disc[3])) / (2.0 * disc[0]); 
	hi.pos = vec3_plus(O, vec3_multi(hi.t, D));
	if (vec3_dot(vec3_minus(hi.pos, cy->pos), cy->dir) < 0 ||
	vec3_dot(vec3_minus(hi.pos, cy->pos), cy->dir) > cy->h)
		hi.t = -1.0;
	hi.kd = cy->kd;
	hi.hit_obj = (void *)cy;
	hi.normal = vec3_minus(hi.pos, 
	vec3_multi(vec3_dot(vec3_minus(hi.pos, cy->pos), cy->dir), cy->dir));
	return (hi);
}

t_hitinfo	hit_circle(t_vec3 O, t_vec3 D, const t_cy *cy)
{
	t_hitinfo	hi;
	//t_vec3		cpos;
	
	if (vec3_dot(cy->dir, D) != 0)
		hi.t = vec3_dot(cy->dir, vec3_minus(cy->pos, O)) / vec3_dot(cy->dir, D);
	else
		hi.t = -1.0;
	hi.pos = vec3_plus(O, vec3_multi(hi.t, D));
	vec3_mag(vec3_minus(hi.pos, O));
	hi.kd = cy->kd;
	hi.normal = cy->dir;
	hi.hit_obj = (void *)cy;
	return (hi);	
}

t_hitinfo	parsing_hittables(t_vec3 *ro, t_vec3 *rd, t_hittable *hittable)
{
	t_hitinfo	hitinfo;

	hitinfo.t = -1.0;
	if (hittable->type == sphere)
		hitinfo = hit_sphere(*ro, *rd, (t_sp *)hittable->obj);
	else if (hittable->type == plane)
		hitinfo = hit_plane(*ro, *rd, (t_pl *)hittable->obj);
	else if (hittable->type == square)
		hitinfo = hit_square(*ro, *rd, (t_sq *)hittable->obj);
	else if (hittable->type == cylinder)
		hitinfo = hit_cylinder(*ro, *rd, (t_cy *)hittable->obj);
	return (hitinfo);
}

t_hitinfo	raycast(t_vec3 *ro, t_vec3 *rd)
{
	int			it;
	t_hitinfo	hitinfo;
	t_hitinfo	closest_hit;

	it = 0;
	closest_hit.t = -1.0;
	while (it < g_obj_cnt)
	{
		hitinfo = parsing_hittables(ro, rd, &g_obj_lst[it]);
		if (hitinfo.t > 0.0 &&
			(hitinfo.t < closest_hit.t || closest_hit.t == -1.0))
		{
			closest_hit.t = hitinfo.t;
			closest_hit.kd = hitinfo.kd;
			closest_hit.pos = hitinfo.pos;
			closest_hit.normal = hitinfo.normal;
			closest_hit.hit_obj = hitinfo.hit_obj;
		}
		it++;
	}
	return (closest_hit);
}

// int		in_shadow(t_hitinfo *hitinfo)
// {
// 	t_vec3	l;
// 	int		it;
// 	int		it_li;
// 	int		is_block;

// 	is_block = 1;
// 	it_li = 0;
// 	while (it_li < g_li_cnt)
// 	{
// 		it = 0;
// 		l = vec3_minus(g_li_lst[it_li].pos, hitinfo->pos);
// 		l = vec3_normalize(l);
// 		while (it < g_obj_cnt)
// 		{
// 			if (g_obj_lst[it].obj != hitinfo->hit_obj &&
// 			parsing_hittables(&hitinfo->pos, &l, &g_obj_lst[it]).t >= 0.0)
// 				break ;
// 			it++;
// 		}
// 		if (it == g_obj_cnt)
// 			is_block = 0;
// 		it_li++;
// 	}
// 	return (is_block);
// }

t_color	calc_ks(t_vec3 *ro, t_vec3 *n, t_vec3 *pos)
{
	int			it;
	t_vec3		v;
	t_vec3		l;
	t_vec3		h;
	t_color		ret;
	t_color		tmp;
	t_color		ks;

	it = 0;
	ret = 0;
	ks = 0x00ffffff;
	tmp = 0;
	v = vec3_minus(*ro, *pos);
	v = vec3_normalize(v);
	while (it < g_li_cnt)
	{
		l = vec3_minus(g_li_lst[it].pos, *pos);
		l = vec3_normalize(l);
		h = vec3_multi(1.0 / vec3_mag(vec3_plus(v, l)), vec3_plus(v, l));
		h = vec3_normalize(h);
		tmp = color_multi(fmax(0.0, pow(vec3_dot(*n, h), 100)), ks);
		ret = color_plus(ret, tmp);
		it++;
	}
	return (ret);
}

int		check_obs(t_vec3 li_pos, t_vec3 l, t_hitinfo hitinfo)
{
	int		it;
	double	light_t;
	double	t;

	it = -1;
	light_t = vec3_dot(vec3_minus(li_pos, hitinfo.pos), l);
	while (++it < g_obj_cnt)
	{
		if (hitinfo.hit_obj == g_obj_lst[it].obj)
			continue;
		t = parsing_hittables(&hitinfo.pos, &l, &g_obj_lst[it]).t; 
		if ( t >= 0.0 && t < light_t)
			return (1);
	}
	return (0);
}

t_color	calc_kd(t_hitinfo hitinfo)
{
	int			it;
	t_color		tmp;
	t_color		ret;
	t_vec3 		l;
	t_li		*li;

	it = 0;
	li = NULL;
	ret = 0;
	while (it < g_li_cnt)
	{
		tmp = 0;
		li = &g_li_lst[it];
		l = vec3_minus(li->pos, hitinfo.pos);
		l = vec3_normalize(l);
		if (!check_obs(li->pos, l, hitinfo))
			color_set(&tmp,
					color_get('r', hitinfo.kd) * color_get('r', li->color) 
					* li->brightness * fmax(0, vec3_dot(hitinfo.normal, l)),
					color_get('g', hitinfo.kd) * color_get('g', li->color) 
					* li->brightness * fmax(0, vec3_dot(hitinfo.normal, l)),
					color_get('b', hitinfo.kd) * color_get('b', li->color)
					* li->brightness * fmax(0, vec3_dot(hitinfo.normal, l)));
		ret = color_plus(ret, tmp);
		it++;
	}
	return (ret);
}

t_color	ray_color(t_vec3 ro, t_vec3 rd)
{
	t_color		ret;
	t_hitinfo	hitinfo;
	double		ty;

	hitinfo = raycast(&ro, &rd);
	if (hitinfo.t > 0.0)
	{
		ret = color_blend(color_multi(g_ka_ratio, g_ka),
			calc_kd(hitinfo),
			calc_ks(&ro, &hitinfo.normal, &hitinfo.pos));
	}
	else
	{
		ty = rd.y + 1;
		color_set(&ret, (1.0 - ty) * 1.0 + ty * 0.5,
					(1.0 - ty) * 1.0 + ty * 0.7,
					(1.0 - ty) * 1.0 + ty * 1.0);
	}
	return (ret);
}

t_vec3	axis_angle_rot(t_vec3 v1, t_vec3 v2, t_vec3 src)
{
	t_vec3	axis;
	double	theta;
	
	axis = vec3_cross(v1, v2);
	theta = acos(vec3_dot(v1, v2) / (vec3_mag(v1) * vec3_mag(v2)));
	return (vec3_plus(vec3_plus(
		vec3_multi(cos(theta), src),
		vec3_multi(sin(theta), vec3_cross(axis, src))),
		vec3_multi((1 - cos(theta)) * vec3_dot(axis, src), axis)));	
}

void	my_rt(t_data *img)
{
	int		pixel_pos[2];
	t_vec3	screen_pos;
	t_vec3  rd;
	t_cam	*cam;
	double	focal;
	t_vec3	pivot[3];
	
	cam = &g_cam_lst[0];
	focal = g_aspect / tan(cam->fov / (57.3 * 2.0));
	pivot[0] = vec3_init(-g_aspect, -1, focal);
	pivot[1] = vec3_init(g_aspect, -1, focal);
	pivot[2] = vec3_init(-g_aspect, 1, focal);
	t_vec3 hv = vec3_minus(pivot[1], pivot[0]);
	t_vec3 vv = vec3_minus(pivot[2], pivot[0]);
	pixel_pos[1] = 0;
	while (pixel_pos[1] < g_height)
	{
		pixel_pos[0] = 0;
		while (pixel_pos[0] < g_width)
		{
			double	u = (double)pixel_pos[0] / (double)(g_width - 1);
			double	v = (double)pixel_pos[1] / (double)(g_height - 1);
			screen_pos = vec3_plus(vec3_plus(pivot[0], vec3_multi(u, hv)), vec3_multi(v, vv));
			rd = axis_angle_rot(vec3_init(0, 0, 1), cam->dir, screen_pos);
			// rd = vec3_normalize();
			setpixel(img, pixel_pos[0], g_height - pixel_pos[1] - 1, ray_color(cam->pos, rd));
			pixel_pos[0]++;
		}
		pixel_pos[1]++;
	}
}
