#include "project.h"

void    ft_splitdel(char **chrarr)
{
    int n;

    n = 0;
    while (chrarr[n])
        free(chrarr[n++]);
    free(chrarr);
}

int     ft_atoi_check(char *string, int integer)
{
    char *test;

    test = ft_itoa(integer);
    integer = (!ft_strcmp(string, test)) ? 1 : 0;
    free(test);
    return (integer);
}

int main(int argc, char **argv)
{
    t_data  data;

    ft_bzero(&data, sizeof(t_data));
    read_data(&data);
    check_map(&data);
    cut_dead_ends(&data);
    if (!((t_room*)data.end->content)->links->next || !((t_room*)data.start->content)->links->next || data.ants == 1)
        breadth_first_traversal(&data);
    else
        depth_first_traversal(&data);
    if (!data.routes)
        error(NULL, &data);
    ((t_room*)data.start->content)->ant = data.ants;
    print_moves(&data);
    print_routes(&data);
    free_data(&data);
    return (0);
}