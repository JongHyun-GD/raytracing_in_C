#ifndef HITTABLE_H
# define HITTABLE_H

typedef enum	e_obj_type
{
	sphere,
	plane,
	square,
	cylinder,
	triangle
}				t_obj_type;

typedef struct	s_hittable
{
	t_obj_type	type;
	void		*obj;
}				t_hittable;

typedef struct	s_hitinfo
{
	double		t;
	t_vec3		pos;
	t_vec3		normal;
	t_color		kd;
	void		*hit_obj;
}				t_hitinfo;

typedef struct	s_sp
{
	t_vec3		pos;
	double		dm;
	t_color		kd;
}				t_sp;

typedef struct	s_pl
{
	t_vec3		pos;
	t_vec3		normal;
	t_color		kd;
}				t_pl;

typedef struct	s_sq
{
	t_vec3		pos;
	t_vec3		normal;
	double		size;
	t_color		kd;
}				t_sq;

typedef struct	s_cy
{
	t_vec3		pos;
	t_vec3		dir;
	double		dm;
	double		h;
	t_color		kd;
}				t_cy;

typedef struct	s_li
{
	t_vec3		pos;
	double		brightness;
	t_color		color;
}				t_li;

typedef struct	s_cam
{
	t_vec3		pos;
	t_vec3		dir;
	int			fov;
}				t_cam;

#endif