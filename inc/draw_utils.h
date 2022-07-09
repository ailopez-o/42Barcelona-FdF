#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

int		draw_line(t_meta *meta, t_point start, t_point end);
void	draw_dot(t_meta *meta, t_point point, int radius);
int		gradient(int startcolor, int endcolor, int len, int pix);
#endif