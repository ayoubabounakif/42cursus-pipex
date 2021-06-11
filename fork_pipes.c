/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:41:19 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/10 15:41:30 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/pipex.h"

char *bin_path(char *cmd, t_dlist envl)
{
	t_env	*_420sh_env;
	int		bin_fd;
	char	*path;
	char	*bin_path;
	char	**split_path;
	int		i;

	i = 0;
	bin_path = NULL;
	dlist_move_cursor_to_head(envl);
	while (envl->cursor_n != envl->sentinel)
	{
		_420sh_env = envl->cursor_n->value;
		if (strcmp(_420sh_env->key, "PATH") == 0)
			path = _420sh_env->value;
		dlist_move_cursor_to_next(envl);
	}
	split_path = ft_split(path, ':');
	if (split_path == NULL)
	{
		ft_putstr_fd("_420sh: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (NULL);
	}
	while (split_path[i])
	{
		bin_path = ft_strjoin(split_path[i], "/");
		bin_path = ft_strjoin(bin_path, cmd);
		bin_fd = open(bin_path, O_RDONLY);
		if (bin_fd > 0)
		{
			close(bin_fd);
			return (bin_path);
		}
		i++;
	}
	ft_putstr_fd("_420sh: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	i = 0;
	free(bin_path);
	while (split_path[i])
	{
		free(split_path[i]);
		i++;
	}
	free(split_path);
	return (NULL);
}

void	redir_in_out(int in, int out)
{
	if (in != STDIN_FILENO)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != STDOUT_FILENO)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

void	fork_pipes(t_data *data, char **envp)
{
	pid_t	pid;
	int		in;
	char	*bin;
	int		fds[2];
	int		file;

	in = STDIN_FILENO;
	data->i = 0;
	// Main loop
	while (data->tokens_args[data->i + 1] != NULL)
	{
		if (data->i == 0)
			in = open((const char *)data->input_file, O_RDONLY);
		if (in == -1)
		{
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
			exit(errno);
		}

		pipe(fds);

		bin = bin_path(data->tokens_args[data->i][0], data->env);
		if (bin == NULL)
			exit(EXIT_FAILURE);

		// SPAWN PROC
		pid = fork();
		if (pid == 0)
		{
			redir_in_out(in, fds[1]);
			execve(bin, data->tokens_args[data->i], envp);
		}

		close(fds[WRITE]);
		if (in != STDIN_FILENO)
			close(in);
		in = fds[READ];
		data->i++;
	}

	bin = bin_path(data->tokens_args[data->i][0], data->env);
	if (bin == NULL)
		exit(EXIT_FAILURE);

	// Execution of last command
	pid = fork();
	if (pid == 0)
	{
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		file = open((const char *)data->output_file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (file == -1)
		{
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
			exit(errno);
		}
		dup2(file, STDOUT_FILENO);
		close(file);
		execve(bin, data->tokens_args[data->i], envp);
	}
	if (in != STDIN_FILENO)
		close(in);
	while (waitpid(-1, NULL, 0) > 0)
		;
}