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
		
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	[ ]=  CHANGER LA variable $_ en fonction de la derniere ligne de commande tapee
		PBLM with $_ variable
	printf("%s\n", env_var("_=/usr/bin/env")); // does work the right way \\ var in it isnt good


BUILTINS

	[✅]=  echo with option -n
			// echo -nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn TEST
			// echo -nnnnno TEST
			// echo -n -n -n -n -n -n TEST

	[]=  pwd with no options + updating pwd after using cd
		// PWD Set by the shell to be an absolute pathname of the current working directory. If an application sets
		// 	or unsets the value of PWD , the behaviors of the cd and pwd utilities are unspecified.

	[✅]=  env with no options or arguments

	[✅]=  export with no options
			// echo "$ $ $ $ $SHELL----------$LOL.......$123TEST"
			// export 1 \\A

	[✅]=  unset with no options
			// handles "_" not being able to be unset

	[ ]=  cd with only a relative or absolute path

	[ ]=  exit with no options
		// when exiting our ./minishell, exit value should have the value of the last exit value if its not 0

	
