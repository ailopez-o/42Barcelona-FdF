#include "../inc/map.h"
#include "../inc/keycodes.h"
#include "../inc/map.h"

void	angle(float *ang, float value)
{
	*ang += value;
	if (*ang < 0)
			*ang = 360 + *ang;
	if (*ang >= 360)
			*ang = *ang - 360;
}

void	angle_control(int key, t_meta *meta)
{
	int	ang;

	ang = 1;
	if (meta->keys.b_keyctrl)
		ang = 90;
	if (key == KEY_DOWN)
		angle(&meta->map.ang[x], ang);
	if (key == KEY_UP)
		angle(&meta->map.ang[x], -ang);
	if (key == KEY_LEFT)
		angle(&meta->map.ang[y], ang);
	if (key == KEY_RIGHT)
		angle(&meta->map.ang[y], -ang);
	if (key == KEY_Q)
		angle(&meta->map.ang[z], ang);
	if (key == KEY_W)
		angle(&meta->map.ang[z], -ang);
}

void	colorscheme(int bck, int men, int bot, int top, int gnd, t_map *map)
{
	map->colors.backcolor = bck;
	map->colors.bottomcolor = bot;
	map->colors.groundcolor = gnd;
	map->colors.menucolor = men;
	map->colors.topcolor = top;
	colorize(map);
}
