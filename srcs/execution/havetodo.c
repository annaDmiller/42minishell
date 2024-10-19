BUILTINS

	[✅]=  echo with option -n

	[✅]=  pwd with no options 

	[✅]=  env with no options or arguments

	[✅]=  export with no options
		// echo "$ $ $ $ $SHELL----------$LOL.......$123TEST"
		// export 1 \\A

	[✅]=  unset with no options
			// handles "_" not being able to be unset

	[✅]=  cd with only a relative or absolute path

	[ ]=  exit with no options
		// when exiting our ./minishell, exit value should have the value of the last exit value if its not 0

ENV

	[✅]=  $variable est censé etre remplace par le contenu de la variable si elle existe // env+var
_____________________________________________


		Lire le manuel de bash --posix

EXEC	convertir l`env en char ** et les arguments en char ** aussi pour execve
		si pipe est, faire les commandes dans des fork


gere les redirections + here doc

	[ ]=  < should redirect input.
	[ ]=  > should redirect output.

	[ ]=  << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesnt have to update the history!
	[ ]=  >> should redirect output in append mode.

gerer les pipes | 

	[ ]=  appeler une fonction lorsque un pipe est signalé qui permet de prendre en input la partie gauche
		du pipe au côté droit pipe


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	[ ]=  CHANGER LA variable $_ en fonction de la derniere ligne de commande tapee
		PBLM with $_ variable
	
