#ifndef INFO_H
# define INFO_H

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct  s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

#endif