#include "../includes/minishell.h"

volatile int    g_sig;

int main(int argc, char **argv, char **env)
{
    char    *prompt;
    char    *cmd_line;
    char    **args; 

//    init_signal;
    while (1)
    {
        prompt = print_prompt();
        cmd_line = readline(prompt);
        //args = parse_line(cmd_line);
        free (cmd_line);
        free(prompt);
    }
    return (0);
}
