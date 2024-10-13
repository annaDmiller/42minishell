SAUVEGGGGGGARDE

void	export_no_opt(t_msh *msh)
{
	t_env	*tmp;
	int		*order;
	char		**names;
	int		length;
	int		i;
	int		d;
	int		r;

	length = -1;
	tmp = msh->env;
	while (tmp)
	{
		++length;
		tmp = tmp->next;
	}
	names = malloc(sizeof(char *) * (length + 1));
	order = malloc(sizeof(int) * (length + 1));
	order[length] = 0;
	i = -1;
	tmp = msh->env;
	while (++i >= 0 && tmp)
	{
		names[i] = tstrdup(tmp->name);
		tmp = tmp->next;
	}
	i = -1;
	tmp = msh->env;
	while (++i <= length)
	{
		r = -1;
		d = 0;
		while (++r <= length)
			if (tstrcmp(tmp->name, names[r]) > 0)
				d++;
		order[d] = tmp->id;
		tmp = tmp->next;
	}
	i = -1;
	while (++i < length)
	{
		tmp = msh->env;
		while (tmp && tmp->id != order[i] + 1)
			tmp = tmp->next;
		printf("export %s=\"%s\"\n", tmp->name, tmp->var);
	}
	i = -1;
	while (++i <= length)
		free(names[i]);
	free(names);
	free(order);
}