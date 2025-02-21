

#include "cellular.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>



char	*table_dup(t_view *v)
{
	int		i;
	char	*table;

	i = 0;
	table = malloc((sizeof(char)) * v->len + 1);
	if (!table)
		return (NULL);
	i = -1;
	while (++i < v->len)
		table[i] = v->table[i];
	table[i] = '\0';
	return (table);
}

char *table_create(t_view v)
{
    int i;
    char *table;

    table = (char *)malloc(sizeof(char) * (v.len + 1));
    for (i = 0; i < v.len; i++)
       table[i] = false;  // Corrected string to wide character
	table[i] = '\0';  // Null-terminate the row

    return table;
}

void print_table(t_view *v)
{
    int i = 0;

	if (v->table[i] == 1)
		printf("1 ");
	else
		printf("  ");
	i++;
    while (i < v->len)
    {
        if (i % v->width == 0)
			printf("\n");
		if (v->table[i] == 1)
			printf("1 ");
		else
			printf("  ");
		i++;
    }
	printf("\n");
	printf("\n");
}

char	get_cell(t_view *v, int x, int y)
{
	int index = y * v->width + x;

	if (index < 0 || v->len <= index)
		return false;
	return v->table[index];
}

void	set_cell(t_view *v, int x, int y, char c)
{
	int index = y * v->width + x;
	v->new_table[index] = c;
}


int	count_side(t_view *v, int x, int y)
{
	int count = 0;

	count += get_cell(v, x - 1, y + 1) == true;
	count += get_cell(v, x - 1, y) == true;
	count += get_cell(v, x - 1, y - 1) == true;
	count += get_cell(v, x, y - 1) == true;
	count += get_cell(v, x + 1, y - 1) == true;
	count += get_cell(v, x + 1, y) == true;
	count += get_cell(v, x + 1, y + 1) == true;
	count += get_cell(v, x, y + 1) == true;

	return (count);
}

void algo_one(t_view *v, int x, int y)
{
	int c;
	c = count_side(v, x, y);

	if (c == 2)
	{
		return;
	}
	if (c == 3)
	{
		set_cell(v, x, y, true);
		return ;
	}
	set_cell(v, x, y, false);
}


void	update_frame(t_view *v)
{
	int i = 0;
	int x = 0;
	int y = 0;

	v->new_table = table_dup(v);
	while (i < v->len)
	{
		algo_one(v, x, y);
		x++;
		if (x == v->width)
		{
			x = 0;
			y++;
		}
		i++;
	}
	free(v->table);
	v->table = v->new_table;
}

t_view	gen_cells(t_view v)
{
	int	i = v.len / 2 + v.width / 2;
	// int j = v.len / 2 + v.width / 4;

	v.table[i] = true;
	v.table[i + v.width] = true;
	v.table[i - v.width] = true;
	// v.table[i + v.width + 2] = true;
	// v.table[i + (v.width * 2)] = true;
	// v.table[i + v.width - 3] = true;

	// v.table[j] = true;
	// v.table[j - v.width ] = true;
	// v.table[j - v.width - 1] = true;
	// v.table[j + v.width + 1] = true;
	return v;
}

t_view	gen_cells_2(t_view v)
{
	int i = v.len / 4;

	while (i < v.len / 2)
	{
		v.table[i] = true;
		i+= 3;
	}
	return (v);
}

t_view	gen_cells_3(t_view v)
{
	int	i = v.len / 2 + v.width / 2;

	while (i < v.len / 2 + v.len / 4)
	{
		v.table[i] = true;
		if ( i % 2 == 0)
			i+= 3;
		else
			i += 5;
	}
	return (v);
}

t_view	gen_cells_4(t_view v)
{
	int	i = v.len / 2 + v.width / 2;

	v.table[i] = true;
	v.table[i + 1] = true;
	v.table[i - v.width] = true;
	v.table[i - v.width - 1] = true;
	v.table[i + v.width] = true;
	return (v);
}

t_view 	init_game_of_life(int argc, char **argv)
{
	t_view v;
	int	i;

	v.width  = atoi(argv[1]);
	v.height = atoi(argv[2]);
	v.len = v.width * v.height;
	v.rect_size = TABLE_S / v.width;
	printf("%d, %d, %d\n", v.width, v.height, v.len);
	printf("%d\n", TABLE_S);
	v.table = table_create(v);
	gen_cells_4(v);
	// print_table(&v);
	usleep(1000 * 1000);

    return (v);
}

