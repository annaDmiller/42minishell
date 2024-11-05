/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:55:01 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:55:03 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

//function returns 0 if the line is empty; 
//1 if there is at least any other char besides white spaces 
int	is_empty_line(char *cmd_line)
{
	int	ind;

	ind = 0;
	while (cmd_line[ind])
	{
		if (is_white_space(cmd_line[ind]))
			return (1);
		ind++;
	}
	return (0);
}

//function returns 0 if car is white space or end of string
int	is_white_space(char car)
{
	if (car == ' ' || car == '\v' || car == '\t' || car == '\r'
		|| car == '\f' || car == '\0')
		return (0);
	return (1);
}

//function returns 0 if car is a quote symbol
int	is_quote(char car)
{
	if (car == '\'' || car == '"')
		return (0);
	return (1);
}

//function returns 0 if car is a redirection symbol
int	is_redir(char car)
{
	if (car == '>' || car == '<' || car == '|')
		return (0);
	return (1);
}
