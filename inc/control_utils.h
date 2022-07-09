#ifndef CONTROL_UTILS_H
# define CONTROL_UTILS_H

void	angle_control(int key, t_meta *meta);
void	angle(float *ang, float value);
void	colorscheme(int bck, int men, int bot, int top, int gnd, t_map *map);
void	colorize(t_map *map);
#endif