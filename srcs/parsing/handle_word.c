/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:28:56 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/19 13:28:56 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

char	*handle_word(t_all *all, int in_dollar)
{
	int		ind;
	char	*str;

	ind = 0;
	while (all->line[ind] && is_white_space(all->line[ind]))
	{
		if (!in_dollar && all->line[ind] == '$'
			&& is_white_space(all->line[ind + 1]))
			break ;
		if (!is_quote(all->line[ind]) || !is_redir(all->line[ind]))
			break ;
		ind++;
	}
	str = (char *) malloc(sizeof(char) * (ind + 1));
	if (!str)
		error("handle_word: Malloc error", all, SIGTERM);
	ft_strlcpy(str, all->line, ind + 1);
	all->line += ind;
	return (str);
}
