/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:03:26 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/10 14:03:29 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

// bash-5.1$ env -i unset PATH
// env: ‘unset’: No such file or directory
// bash-5.1$

char	*setup_name(char *str)
{
	char    *name;
	int		i;
	int		r;

	i = 0;
	r = 0;
	while (str[i] && str[i] != '=')
		i++;
	printf("\n\n");
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	printf("name taille ==  %d \ton malloc cette taille // %d\n", i, i + 1);
	name[i] = '\0';
	while (--i >= 0)
	{
		name[i] = str[i];
		printf("\tname[%d] == %c\n", i, name[i]);
	}
	return (name);
}

void    unset(struct msh *msh, char *str)
{
	// ideally doubly linked list ill go previous but dk how to implement it
	t_env   *node;
	t_env   *tmp;
	char	*name;
	// int             i;

	name = setup_name(str);
	if (!name)
		return ;
	node = env_retrieve_var(msh->env, name); // pcque le nom de la variable est export nomdelavariable
	if (!node)
		return (freestr(name));
	tmp = msh->env;	
	while (tmp && tmp->next->id != node->id) // je parcours ma liste avec tmp, lorsque le prochaine correspond a la var que je veux enlever je m'arrete
		tmp = tmp->next;
	if (!node->next) // if the var i want to unset is the last one in the list
	{
		free(node); // i just free it
		tmp->next = NULL; // and set ->next of the one before him to NULL
		return (freestr(name));
	}
	tmp->next = node->next;
	freestr(name);
	free(node->name);
	free(node->var);
	free(node);
}
