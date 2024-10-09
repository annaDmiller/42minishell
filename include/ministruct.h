/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ministruct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:05:16 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/09 00:06:57 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISTRUCT_H
# define MINISTRUCT_H

typedef struct env
{
	struct env	*next;
	char		*var;
	char		*name;
	int			id;
	int			index;
}		t_env;

typedef struct msh
{
	t_env		*env;
	char		*pwd;
	char		**argv;
	int			argc;
}		t_msh;

#endif
