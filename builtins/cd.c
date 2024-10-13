#include "../include/minishell.h"

/// @brief if path given argv->arg is not valid it prints pathname: No such file or directory
///	if there is more than one arg it doesnt move and prints cd: too many arguments
void    cd(t_msh *msh, t_args *argv)
{
	// char	*tmp;
	DIR	*test;
	char	*path;

	// tmp = msh->pwd;
	if (argv->next)
		return (putstrfd("cd: too many arguments\n", STDOUT_FILENO));
	path = argv->arg;
	(void)msh;
	test = opendir(path);
	if (test)
		if (!chdir(".."))
			return ; // handle error

	//if cmd is ../../sgoinfr --> make the right pwd be
	// if (path[0] == '.' && path[1] == '.')
		// down_pwd(msh);
		// msh->pwd = handle going backward, crop everything after the last '/'
	// else if (path == ".")
		// "." mean current directory so no need to handle this ?
}