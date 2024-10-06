#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct s_cmd
{
    char *name;
    char **argv;
    struct s_cmd    *next;
    struct s_cmd    *prev;
}               t_cmd;
#endif