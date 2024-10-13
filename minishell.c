/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:51:07 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/11 00:53:24 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"
#include "include/structures.h"

/// @brief parse argv given after ./minishell and parse it into a linked list to test for the final parsing
/// @param msh 
/// @param argv 
static void	parse_cmd_line(t_msh *msh, char **argv)
{
	t_args	*tmp;
	int		i;

	i = 0;
	msh->l_args = NULL;
	while (argv[++i])
	{
		if (msh->l_args == NULL)
		{
			msh->l_args = (t_args *)malloc(sizeof(t_args));
			if (msh->l_args == NULL)
				return ; // error malloc
			tmp = msh->l_args;
		}
		else
		{
			tmp->next = (t_args *)malloc(sizeof(t_args));
			if (tmp->next == NULL)
				return ; // error malloc
			tmp = tmp->next;
		}
		tmp->arg = argv[i];
		tmp->next = NULL;
	}
}

void	minishell(t_msh *msh, int argc, char **argv, char **envp)
{
	everyinit(msh, argc, argv, envp);
	parse_cmd_line(msh, argv);
	export_def(msh, msh->l_args);
	env(msh->env);
	(void)argc;
	(void)argv;
	(void)envp;
}

void	freestr(char *str)
{
	free(str);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	minishell(&msh, argc, argv, envp);
	freenv(msh.env);
	free(msh.pwd);
	return (0);
}
