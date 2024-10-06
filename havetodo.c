                                Lire le manuel de bash --posix

gerer tous les cas de redirections + tt apprendre sur les here documents

        [ ]=  < should redirect input.
        [ ]=  > should redirect output.
//	

        [ ]=  << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesnt have to update the history!
        [ ]=  >> should redirect output in append mode.

gerer les pipes | 

        [ ]=  appeler une fonction lorsque un pipe est signalé qui permet de prendre en input la partie gauche
                du pipe au côté droit pipe
        
gerer les variables env

        [ ]=  echo $variable est censé retrouvé la variable d env si elle existe et printf son contenu
                sur le terminal /// dans tous les cas rtval == 0

        [ ]=  rebuilt la fonction export qui permet d/add une variable a env

