void	chromakopia(t_cmd *cmd)
{
	if (!cmd->redir)
		return ;
	else if (cmd->redir->pos == SOLO)
	{
		fprintf(stderr, "SOLO\n");
		if (cmd->redir->in_type != '0')
			if (cmd->redir->in_type == 'f')
				if(dup2(cmd->redir->fd_infile, STDIN_FILENO) == -1)
					wgas("!chromakopia // 23\n", 22);;// handle error
		if (cmd->redir->out_type != '0')
		{
			if (dup2(cmd->redir->fd_outfile, STDOUT_FILENO) == -1)
				wgas("!chromakopia // 26\n", 22);// handle error
			close(cmd->redir->pipe_fd[1]);
		}
	}
	else if (cmd->redir->pos == START)
	{
		fprintf(stderr, "START\n");
		if (dup2(cmd->redir->pipe_fd[1], STDOUT_FILENO) == -1)
			return ;// handle error
		if (cmd->redir->in_type != '0')
		{
			if (cmd->redir->in_type == 'f')
				if(dup2(cmd->redir->fd_infile, STDIN_FILENO) == -1)
					wgas("!chromakopia // 36\n", 22);;// handle error
		}
		if (cmd->redir->out_type != '0')
		{
			if (dup2(cmd->redir->fd_outfile, STDOUT_FILENO) == -1)
				wgas("!chromakopia // 39\n", 22);// handle error		
		}
		close(cmd->redir->pipe_fd[0]);
	}
	else if (cmd->redir->pos == MID)
	{
		fprintf(stderr, "MID\n");
		if (dup2(cmd->redir->pipe_fd[0], STDIN_FILENO) == -1)
			return ;// handle error
		if (dup2(cmd->redir->pipe_fd[1], STDOUT_FILENO) == -1)
			return ;// handle error
		close(cmd->redir->pipe_fd[1]);
		close(cmd->redir->pipe_fd[0]);
	}
	else if (cmd->redir->pos == END)
	{
		fprintf(stderr, "END\n");
		// if (cmd->redir->out_type == '0')           // NO need to do anything if output is on stdout ??
		// 	if (dup2(cmd->redir->pipe_fd[1], STDOUT_FILENO) == -1)
		// 		wgas("!chromakopia // 53\n", 22);// handle
		if (dup2(cmd->redir->pipe_fd[0], STDIN_FILENO) == -1)
			return ;// handle error
		if (cmd->redir->out_type != '0')
		{
			if (dup2(cmd->redir->fd_outfile, STDOUT_FILENO) == -1)
				wgas("!chromakopia // 26\n", 22);// handle error
			close(cmd->redir->pipe_fd[0]);
		}
		close(cmd->redir->pipe_fd[1]);
	}
}
