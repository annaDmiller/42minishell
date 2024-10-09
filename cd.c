#include "include/minishell.h"

void    cd(t_msh *msh, char *path)
{
	// char	*tmp;
	DIR	*test;

	// tmp = msh->pwd;
	(void)msh;
	test = opendir(path);
	if (test)
		if (chdir(path))
			return ; // handle error
	// if (path == "..")
		// msh->pwd = handle going backward, crop everything after the last '/'
	// if (path == ".")
		// "." mean current directory so no need to handle this ?
	// env->OLD_PWD = tmp; // set OLD_PWD to the current pwd if chdir succeed
}

void    cd_backward(struct msh *msh)
{
	char	*nvx_pwd;
	int	i;
	int	d;

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
}