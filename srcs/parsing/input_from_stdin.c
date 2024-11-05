#include "../../includes/minishell.h"

static int	read_from_stdin(t_all *all, t_cmd *cmd);
static char	*read_keyword(t_all *all, t_cmd *cmd);

int	input_from_stdin(t_all *all, t_cmd *cmd)
{
	char	*temp;

	all->line++;
	temp = read_keyword(all, cmd);
	if (cmd->redir->fd_infile >= 0)
	{
		if (cmd->redir->fd_infile)
			close(cmd->redir->fd_infile);
		if (cmd->redir->in_txt)
			free(cmd->redir->in_txt);
		cmd->redir->in_txt = NULL;
	}
	all->temp_for_free = ft_strjoin(temp, "\n");
	free(temp);
	if (!all->temp_for_free)
		return (error("input_from_stdin: Malloc error\n", all), 1);
	read_from_stdin(all, cmd);
	free(all->temp_for_free);
	all->temp_for_free = NULL;
	cmd->redir->in_type = 's';
	return (0);
}

static int	read_from_stdin(t_all *all, t_cmd *cmd)
{
	char	*gnl;
	char	*temp;
	size_t	len_key;

	temp = NULL;
	cmd->redir->tfile = 0;
	len_key = ft_strlen(all->temp_for_free);
	ft_printf("> ");
	gnl = get_next_line(0);
	if (!gnl)
	{
		if (g_sig)
			return (1);
		else
			return (error("read_from_stdin: Malloc error\n", all), 1);
	}
	while (ft_strncmp(all->temp_for_free, gnl, len_key + 1) && !g_sig)
	{
		temp = cmd->redir->in_txt;
		cmd->redir->in_txt = ft_strjoin(temp, gnl);
		free(temp);
		free(gnl);
		if (!cmd->redir->in_txt)
			return (error("read_from_stdin: Malloc error\n", all), 1);
		ft_printf("> ");
		gnl = get_next_line(0);
	}
	free(gnl);
    if (cmd->redir->in_txt)
	{
		cmd->redir->tfile = open(".eof", O_WRONLY | O_TRUNC | O_CREAT, 0666);
		ft_putstr_fd(cmd->redir->in_txt, cmd->redir->tfile);
		close(cmd->redir->tfile);
	}
	return (0);
}

static char	*read_keyword(t_all *all, t_cmd *cmd)
{
	char	*temp;
	char	*ret;

	all->temp_for_free = NULL;
	ret = NULL;
	while (!is_white_space(*(all->line)) && *(all->line))
		all->line++;
	if (!is_redir(*(all->line)))
		return (NULL);
	while (is_white_space(*(all->line)) && *(all->line))
	{
		if (!is_quote(*(all->line)))
			all->temp_for_free = handle_quotes(all, cmd, 1);
		else
			all->temp_for_free = handle_word(all, 1);
		temp = ret;
		ret = ft_strjoin(temp, all->temp_for_free);
		if (!ret)
			return (error("read_addr: Malloc error\n", all), NULL);
		free(temp);
		free(all->temp_for_free);
		all->temp_for_free = NULL;
	}
	all->temp_for_free = NULL;
	return (ret);
}