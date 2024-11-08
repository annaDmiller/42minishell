#!/bin/sh

while [ true ]
do
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell l 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell ls 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell pwd 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell "mkdir a" 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell "rm -rf a" 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell l 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell ls 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell pwd 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell "mkdir a" 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell "rm -rf a" 2>&1 | grep "FILE DESCRIPTORS"
	valgrind --track-fds=yes --suppressions=suppress.supp ./minishell 2>&1 | grep "FILE DESCRIPTORS"
done

si fd ouvert herite d`un parent utiliser fdmonitor.sh pour le tracker
# ./fdmonitor.sh gnome-terminal -m

# int	main(int argc, char **argv, char **envp)
# {
# 	t_all	*all;
# 	char	*line;
# 	t_msh	msh;

# 	g_sig = 0;
# 	all = NULL;
# 	if (argc < 2)
# 		return (0);
# 	everyinit(&msh, envp);
# 	init_signals(all);
# 	// while (!msh.have_to_exit)
# 	// {
# 		all = init_all_struct(all, &msh);
# 		// line = readline(PROMPT);
# 		line = tstrdup(argv[1]);
# 		// if (!line)
# 		// 	return (0);
# 		all->line = line;
# 		if (is_empty_line(all->line))
# 			process_line(all, &msh);
# 		g_sig = 0;
# 		rl_on_new_line();
# 	// }
# 	rl_clear_history();
# 	(void)argc;
# 	// (void)argv;
# 	printf("exit\n");
# 	free_exit(all, &msh, 0);
# 	return (msh.exit);
# }

