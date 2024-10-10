				Lire le manuel de bash --posix

gerer tous les cas de redirections + tt apprendre sur les here documents

	[ ]=  < should redirect input.
	[ ]=  > should redirect output.

	[ ]=  << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesnt have to update the history!
	[ ]=  >> should redirect output in append mode.

gerer les pipes | 

	[ ]=  appeler une fonction lorsque un pipe est signalé qui permet de prendre en input la partie gauche
		du pipe au côté droit pipe



gerer les variables env

	[✅]=  $variable est censé etre remplace par le contenu de la variable si elle existe // env+var
		
		PBLM with $_ variable
	printf("%s\n", env_var("_=/usr/bin/env")); // does work the right way \\ strange that env_find_var return the good node but var in it isnt good


	

BUILTINS

	[✅]=  echo with option -n

	[✅]=  pwd with no options
		PWD Set by the shell to be an absolute pathname of the current working directory. If an application sets
			or unsets the value of PWD , the behaviors of the cd and pwd utilities are unspecified.

	[✅]=  env with no options or arguments

	[ ]=  cd with only a relative or absolute path

	[ ]=  export with no options

	[ ]=  unset with no options

	[ ]=  exit with no options
		when exiting our ./minishell, exit value should have the value of the last exit value if its not 0

	
