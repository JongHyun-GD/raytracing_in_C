/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:19:06 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/19 15:05:11 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "read_file.h"

static int		handle_error(char *message, char *buf)
{
	ft_putstr_fd(message, 2);
	free(buf);
	return (-1);
}

double			ft_atod(char *str)
{
	double	f;
	int		s;
	int		s_len;
	size_t	i;
	int		sign;

	i = 0;
	s_len = 0;
	f = ft_atoi(str);
	sign = str[0] == '-' ? -1 : 1;
	while (str[i] && (str[i] != '.' && str[i] != ','))
		i++;
	if (!str[i] || str[i] == ',')
		s = 0;
	else
		s = ft_atoi(&(str[++i]));
	while (str[i] != ',' && str[i++])
		s_len++;
	if (s_len == 0)
		return (f);
	else
		return (f + sign * (double)s / pow(10, s_len));
}

t_color			read_color(char *str)
{
	int		r;
	int		g;
	int		b;
	int		i;
	t_color	ret;
	
	i = 0;
	r = ft_atoi(str);
	while (str[i] && str[i] != ',')
		i++;
	if (!str[i])
		g = 0;
	else
		g = ft_atoi(&(str[++i]));
	while (str[i] && str[i] != ',')
		i++;
	if (!str[i])
		b = 0;
	else
		b = ft_atoi(&(str[++i]));
	color_set(&ret, (double)r / 255.0, (double)g / 255.0, (double)b / 255.0);	
	return (ret);
}

t_vec3			read_vec3(char *str)
{
	t_vec3		ret;
	
	ret.x = ft_atod(str);	
	while (*str && *str != ',')
		str++;
	ret.y = !*str ? 0.0 : ft_atod(++str); 
	while (*str && *str != ',')
		str++;
	ret.z = !*str ? 0.0 : ft_atod(++str);
	return (ret);	
}

int				apply_resolution(char **line)
{
	size_t	size;

	size = 0;
	while (line[size])
		size++;
	if (size != 3)
		return (-1);
	g_width = ft_atoi(line[1]);
	g_height = ft_atoi(line[2]);
	if (g_width <= 0 || g_height <= 0)
		return (-1);
	ft_putstr_fd("reading resolution...\n", 1);
	return (0);
}

int				apply_ambient(char **line)
{
	size_t	size;
	double	ratio;
	t_color	_ka;

	size = 0;
	while (line[size])
		size++;
	if (size != 3)
		return (-1);
	ratio = ft_atod(line[1]);
	_ka = read_color(line[2]);
	ratio = clamp(ratio, 0.0, 1.0);
	g_ka_ratio = ratio;
	g_ka = _ka;
	ft_putstr_fd("reading ambient lighting...\n", 1);
	return (0);
}

int				apply_sphere(char **line)
{
	t_sp		*sp;
	size_t		size;

	size = 0;
	while (line[size])
		size++;
	if (size != 4)
		return (-1);
	if (!(sp = (t_sp *)ft_calloc(1, sizeof(t_sp))))
		return (-1);
	g_obj_lst[g_obj_cnt].type = sphere;
	g_obj_lst[g_obj_cnt++].obj = sp;
	sp->pos = read_vec3(line[1]);
	sp->dm = ft_atod(line[2]);
	sp->kd = read_color(line[3]);
	ft_putstr_fd("reading sphere...\n", 1);
	// debug
	printf("sp->pos\t:\t%f, %f, %f\n", sp->pos.x, sp->pos.y, sp->pos.z);
	printf("sp->dm\t:\t%f\n", sp->dm);
	printf("sp->kd\t:\t%#08X\n", sp->kd);
	return (0);
}

int				apply_light(char **line)
{
	t_li		li;	
	
	li.pos = read_vec3(line[1]);
	li.brightness = ft_atod(line[2]);
	li.color = read_color(line[3]);
	g_li_lst[g_li_cnt++] = li;
	ft_putstr_fd("reading lighting...\n", 1);
	// debug
	printf("li->pos\t:\t%f, %f, %f\n", li.pos.x, li.pos.y, li.pos.z);
	printf("li->kd\t:\t%#010X\n", li.color);
	printf("li->br\t:\t%f\n", li.brightness);
	return (0);	
}

int				apply_cam(char **line)
{
	int			size;
	t_cam		cam;	

	size = 0;
	while (line[size])
		size++;
	if (size != 4)
		return (-1);
	cam.pos = read_vec3(line[1]);
	cam.dir = read_vec3(line[2]);
	cam.fov = ft_atoi(line[3]);	
	if (cam.fov < 0 || cam.fov > 180)
		return (-1);
	cam.dir = vec3_normalize(cam.dir);	
	g_cam_lst[0] = cam;

	return (0);	
}

void			free_split(char **line)
{
	size_t		it;

	it = 0;
	while (line[it])
	{
		free(line[it]);
		it++;
	}
	free(line);
}

int				apply_plane(char **line)
{
	t_pl		*pl;
	size_t		size;
	
	if (!(pl = ft_calloc(1, sizeof(t_pl) + 1)))
		return (-1);
	size = 0;
	while (line[size])
		size++;
	if (size != 4)
		return (-1);
	printf("reading plane...\n");
	pl->pos = read_vec3(line[1]);
	pl->normal = read_vec3(line[2]);
	pl->normal = vec3_normalize(pl->normal);
	pl->kd = read_color(line[3]);
	g_obj_lst[g_obj_cnt].obj = pl;
	g_obj_lst[g_obj_cnt++].type = plane;
	printf("pl->pos\t:\t%f,%f,%f\n", pl->pos.x, pl->pos.y, pl->pos.z);
	printf("pl->normal\t:\t%f,%f,%f\n", pl->normal.x, pl->normal.y, pl->normal.z);
	printf("pl->kd\t:\t%X\n", pl->kd);
	return (0);
}

int				apply_square(char **line)
{
	t_sq		*sq;
	size_t		size;
	
	if (!(sq = ft_calloc(1, sizeof(t_sq) + 1)))
		return (-1);
	size = 0;
	while (line[size])
		size++;
	if (size != 5)
		return (-1);
	printf("reading square...\n");
	sq->pos = read_vec3(line[1]);
	sq->normal = read_vec3(line[2]);
	sq->normal = vec3_normalize(sq->normal);
	sq->size = ft_atod(line[3]);
	sq->kd = read_color(line[4]);
	g_obj_lst[g_obj_cnt].obj = sq;
	g_obj_lst[g_obj_cnt++].type = square;
	printf("sq->pos\t:\t(%f,%f,%f)\n", sq->pos.x, sq->pos.y, sq->pos.z);
	printf("sq->norm\t:\t(%f,%f,%f)\n", sq->normal.x, sq->normal.y, sq->normal.z);
	printf("sq->size\t:\t%f\n", sq->size);	
	printf("sq->kd\t:\t%X\n", sq->kd);
	return (0);
}

int				apply_cylinder(char **line)
{
	t_cy		*cy;
	size_t		size;
	
	size = 0;
	while (line[size])
		size++;
	if (size != 6)
		return (-1);
	if (!(cy = ft_calloc(1, sizeof(t_cy) + 1)))
		return (-1);
	printf("reading cylinder...\n");
	cy->pos = read_vec3(line[1]);
	cy->dir = read_vec3(line[2]);
	cy->dir = vec3_normalize(cy->dir);
	cy->dm = ft_atod(line[3]);
	cy->h = ft_atod(line[4]);
	cy->kd = read_color(line[5]);
	g_obj_lst[g_obj_cnt].obj = cy;
	g_obj_lst[g_obj_cnt++].type = cylinder;
	printf("cy->pos\t:\t(%f,%f,%f)\n", cy->pos.x, cy->pos.y, cy->pos.z);
	printf("cy->n\t:\t(%f,%f,%f)\n", cy->dir.x, cy->dir.y, cy->dir.z);
	printf("cy->dm\t:\t%f\n", cy->dm);
	printf("cy->h\t:\t%f\n", cy->h);	
	printf("cy->kd\t:\t%X\n", cy->kd);
	return (0);
}

static int		handle_line(char **line)
{
	int		ret;

	if (ft_strncmp(line[0], "R", 2) == 0)
		ret = apply_resolution(line);
	else if (ft_strncmp(line[0], "A", 2) == 0)
		ret = apply_ambient(line);
	else if (ft_strncmp(line[0], "sp", 3) == 0)
		ret = apply_sphere(line);
	else if (ft_strncmp(line[0], "li", 3) == 0)
		ret = apply_light(line);
	else if (ft_strncmp(line[0], "c", 2) == 0)
		ret = apply_cam(line);
	else if (ft_strncmp(line[0], "pl", 3) == 0)
		ret = apply_plane(line);
	else if (ft_strncmp(line[0], "sq", 3) == 0)
		ret = apply_square(line);
	else if (ft_strncmp(line[0], "cy", 3) == 0)
		ret = apply_cylinder(line);
	else
		ret = -1;
	free_split(line);
	return (ret);
}

void			count_obj(char *filename)
{
	int		fd;
	int		cnt;
	char	c;

	cnt = 0;
	fd = open(filename, O_RDONLY);
	while (read(fd, &c, 1) == 1)
		if (c == '\n')
			cnt++;
	close(fd);
	if (!(g_obj_lst = (t_hittable *)ft_calloc(cnt + 1, sizeof(t_hittable))))
		return ;
	if (!(g_li_lst = (t_li *)ft_calloc(cnt + 1, sizeof(t_li))))
	{
		free(g_obj_lst);
		return ;
	}
	if (!(g_cam_lst = (t_cam *)ft_calloc(cnt + 1, sizeof(t_cam))))
	{
		free(g_obj_lst);
		free(g_li_lst);
		return ; 
	}
}

int				read_rt(char *filename)
{
	int		fd;
	int		i;
	int		flag;
	char	*buf;
	char	**sp_buf;

	count_obj(filename);
	fd = open(filename, O_RDONLY);
	if (!(buf = (char *)ft_calloc(1024, 1)))
		return (-1);
	while (1)
	{
		i = 0;
		while ((flag = read(fd, &buf[i], 1)) > 0 && i < 1023 && buf[i] != '\n')
			i++;
		buf[i] = '\0';
		if (flag == -1)
			return (handle_error("Error\n[\'rt\' [Can't open file.]", buf));
		if (i == 0 && flag == 0)
			break ;
		if (i == 0)
			continue ;
		sp_buf = ft_split(buf, ' ');
		if (handle_line(sp_buf) == -1)
			return (handle_error("Error\n[\'rt\' file format is wrong.]\n", buf));
	}
	free(buf);
	return (0);
}