/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:44:55 by tespandj          #+#    #+#             */
/*   Updated: 2024/09/03 13:08:23 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/pipex.h"

static	int	hw_much_words(struct spt x)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (x.str[i] != '\0')
	{
		while (x.str[i] && x.str[i] == x.c)
			i++;
		if (x.str[i] && x.str[i] != x.c)
		{
			d++;
			while (x.str[i] != '\0' && x.str[i] != x.c)
				i++;
		}
	}
	return (d);
}

static struct	spt	len_word(struct spt x, int op)
{
	int	i;
	int	d;

	i = 0;
	while (op >= 0)
	{
		d = 0;
		if (op == 0)
		{
			while (x.str[i] != '\0' && x.str[i] != x.c)
			{
				i++;
				d++;
			}
			x.i = i;
			x.len = d;
			return (x);
		}
		while (x.str[i] != '\0' && x.str[i] != x.c)
			i++;
		while (x.str[i] != '\0' && x.str[i] == x.c)
			i++;
		op--;
	}
	return (x);
}

static struct	spt	space_alloc(struct spt x)
{
	x.indic = 0;
	x = len_word(x, x.op);
	x.split[x.op] = (char *)malloc(sizeof(char) * x.len + 1);
	if (!x.split[x.op])
		x.indic = 42;
	else
		x.split[x.op][x.len] = '\0';
	return (x);
}

static struct	spt	fill_split(struct spt x)
{
	int	tzy;
	int	tmp;

	x.op = 0;
	tzy = 0;
	x.nb_words = hw_much_words(x);
	while (x.op < x.nb_words)
	{
		x = space_alloc(x);
		if (x.indic == 42)
			return (x);
		tzy = x.i;
		tmp = x.len;
		while (--tmp >= 0)
		{
			--tzy;
			x.split[x.op][tmp] = x.str[tzy];
		}
		x.op++;
	}
	x.split[x.op] = NULL;
	return (x);
}

char	**split(char const *str, char c)
{
	struct spt	x;

	x.c = c;
	x.str = str;
	x.i = 0;
	x.indic = 0;
	if (!x.str || !x.c)
		return (NULL);
	x.split = (char **)malloc(sizeof(char *) * (hw_much_words(x) + 1));
	if (!x.split)
		return (NULL);
	x = fill_split(x);
	if (x.indic == 42)
	{
		wegotasplituation(x);
		return (NULL);
	}
	return (x.split);
}
