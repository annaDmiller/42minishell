/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:20 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:21 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

// echo -nnnnnnnnnnn talan
// should work
// echo -nd talan
// should printf -nd talan

// static	char	*setup_var(char *str, int i)
// {
// 	char	*var;
// 	int		r;

// 	r = i;
// 	while (str[i] && str[i] != ' ' && str[i] != '@')
// 		i++;
// 	var = malloc(sizeof(char) * (i - r + 1));
// 	if (!var)
// 		return (NULL); // handle error
// 	var[i - r] = '\0';
// 	while ()
	
	


// }


// void	echo(t_msh *msh, t_args *argv)
// {
// 	int	i;

// 	i = -1;
// 	while (argv)
// 	{
// 		if (argv->arg[0] == '\'')
// 		{
// 			i = 0;
// 			while (argv->arg[++i] && argv->arg[i + 1])
// 				write(1, argv->arg[i], 1);
// 		}
// 		else if (argv->arg[0] == '\"')
// 		{
// 			i = 0;
// 			while (argv->arg[++i])
// 			{
// 				if (argv->arg[i] == '$')
// 				{
// 					setup_var(argv->arg, i + 1);
// 				}
// 			}
// 		}
// 	}

// }





void	echo(t_msh *msh, t_cmd *cmd)
{
	// while ()
	// putstrfd(str, STDOUT_FILENO);
	// if (!cmd_line->next || !(tstrcmp(cmd_line->next, "-n") == 0)) // check if there is echo -n or not 
		// write(STDOUT_FILENO, "\n", 1);
	(void)msh;
	(void)cmd;
}
