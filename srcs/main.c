#include "../includes/minishell.h"

int main(void)
{
    char *prompt;

    while (1)
    {
        prompt = print_prompt();
        printf("%s\n", readline(prompt));
    }
    return (0);
}
