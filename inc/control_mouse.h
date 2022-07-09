#ifndef CONTROL_MOUSE_H
# define CONTROL_MOUSE_H

int		mouse_move(int X, int Y, void *param);
int		mouse_release(int button, int X, int Y, void *param);
int		mouse_press(int button, int X, int Y, void *param);
#endif