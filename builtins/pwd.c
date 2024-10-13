#include "../include/minishell.h"


void    up_pwd(t_msh *msh, char *dir)
{
	char	*nvx_pwd;

	nvx_pwd = tjoin(tjoin(tstrdup(msh->pwd), "/"), dir);
	free(msh->pwd);
	msh->pwd = nvx_pwd;
	// env->OLD_PWD = tmp; // set OLD_PWD to the current pwd if chdir succeed
}

void    down_pwd(t_msh *msh)
{
	char	*nvx_pwd;
	// char	*tmp;
	int	i;
	int	d;

	// tmp = msh->pwd;
	i = tstrlen(msh->pwd);
	while (msh->pwd[--i])
		if (msh->pwd[i] == '/')
			break ;
	nvx_pwd = malloc(sizeof(char) * i + 1);
	if (!nvx_pwd)
		return ; // handle error
	d = -1;
	while (++d < i)
		nvx_pwd[d] = msh->pwd[d];
	nvx_pwd[d] = '\0';
	free(msh->pwd);
	msh->pwd = nvx_pwd;
	// env->OLD_PWD = tmp; // set OLD_PWD to the current pwd if chdir succeed
}