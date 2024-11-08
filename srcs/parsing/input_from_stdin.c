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
		if (cmd->redir->stdin_delim)
			free(cmd->redir->stdin_delim);
		cmd->redir->stdin_delim = NULL;
	}
	cmd->redir->stdin_delim = ft_strjoin(temp, "\n");
	free(temp);
	if (!cmd->redir->stdin_delim)
		return (error("input_from_stdin: Malloc error", all, SIGTERM), 1);
	//if (read_from_stdin(all, cmd) == 1)
	//	if (!g_sig)
	//		error("read_from_stdin: Malloc error", all, SIGTERM);
	//free(all->temp_for_free);
	cmd->redir->in_type = 's';
	cmd->redir->fd_infile = '0';
	return (0);
}

static int	read_from_stdin(t_all *all, t_cmd *cmd)
{
	char	*gnl;
	char	*temp;
	size_t	len_key;

	temp = NULL;
	len_key = ft_strlen(all->temp_for_free);
	ft_printf("> ");
	gnl = get_next_line(0);
	if (!gnl)
		return (1);
	while (ft_strncmp(all->temp_for_free, gnl, len_key + 1) && !g_sig)
	{
		temp = cmd->redir->stdin_delim;
		cmd->redir->stdin_delim = ft_strjoin(temp, gnl);
		free(temp);
		free(gnl);
		if (!cmd->redir->stdin_delim)
			return (error("read_from_stdin: Malloc error", all, SIGTERM), 1);
		ft_printf("> ");
		gnl = get_next_line(0);
	}
	free(gnl);
	// temp_input(all, cmd);
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
	while (is_white_space(*(all->line)) && *(all->line) && is_redir(*all->line))
	{
		if (!is_quote(*(all->line)))
			all->temp_for_free = handle_quotes(all, cmd, 1);
		else
			all->temp_for_free = handle_word(all, 1);
		temp = ret;
		ret = ft_strjoin(temp, all->temp_for_free);
		if (!ret)
			return (error("read_addr: Malloc error", all, SIGTERM), NULL);
		free(temp);
		free(all->temp_for_free);
		all->temp_for_free = NULL;
	}
	all->temp_for_free = NULL;
	return (ret);
}

int	hdc_writing(t_all *all, t_cmd *cmd)
{
	if (cmd && cmd->redir && cmd->redir->stdin_delim)
	{
		if (cmd->redir->fd_infile > 0)
			close(cmd->redir->fd_infile);
		cmd->redir->fd_infile = open(".eof", O_WRONLY
				| O_TRUNC | O_CREAT, 0666);
		if (cmd->redir->fd_infile == -1)
			return (error("hdc_writing: open error\n", all, SIGTERM), 1);
		ft_putstr_fd(cmd->redir->stdin_delim, cmd->redir->fd_infile);
		close(cmd->redir->fd_infile);
		all->hdc_situation = 1;
	}
	return (0);
}
