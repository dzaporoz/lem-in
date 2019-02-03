#ifndef LEM_IN_PROJECT_H
#define LEM_IN_PROJECT_H

#include "libft/libft.h"
#include "ftprintf/ft.h"
#include <limits.h>

# define START_ROOM 0
# define END_ROOM 1
# define REG_ROOM 2


typedef struct      s_room
{
    char            *name;
    short             x;
    short             y;
    t_list          *links;
    unsigned int    ant;
    int             level;
    t_list          *back_link;
}                   t_room;

typedef struct      s_data
{
    int             ants;
    t_list          *rooms;
    t_list          *start;
    t_list          *end;
    t_list          *routes;
    char        vizualize;
}                   t_data;

void    read_data(t_data *data);
void    check_map(t_data *data);
void    depth_first_traversal(t_data *data);
void    error(char *string, t_data *data);
void    del_unmalloced_list(void *p, size_t size);
t_list  *add_link(void *p);
void    breadth_first_traversal(t_data *data);
void    free_data(t_data *data);
void    print_moves(t_data *data);
void    routes_optimization(t_data *data);
void    print_routes(t_data *data);
void    cut_dead_ends(t_data *data);

//move to ft_lib
void    ft_splitdel(char **chrarr);
int     ft_atoi_check(char *string, int integer);



#endif //LEM_IN_PROJECT_H
