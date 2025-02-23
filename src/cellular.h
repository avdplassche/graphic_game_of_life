
#ifndef CELLULAR_H
# define CELLULAR_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>
#include <wchar.h>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define GREENBG "\033[42m"
# define REDBG "\033[41m"

# define RATIO 1.2
# define WIDTH 1280*RATIO
# define HEIGHT 720*RATIO
# define TABLE_H 700*RATIO

typedef struct s_view
{
	char	*table;
	char	*new_table;
	int		col;
	int		lines;
    int     x;
    int     y;
	int		len;
    float     rect_size;
} t_view;

t_view  	init_game_of_life(int argc, char **argv);
void    	update_frame(t_view *v);

#endif
