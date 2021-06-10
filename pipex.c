/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:03:35 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/10 12:03:47 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/pipex.h"

void	fill_tokens_args(char ***tokens_args, int ac, char *av[])
{
	char	**tmp_tokens_args;
	int		i;

	i = 0;
	tmp_tokens_args = (char **)malloc(sizeof(char *) * ac - 2);
	while (i < ac - 3)
	{
		tmp_tokens_args[i] = ft_strdup(av[i + 2]);
		i++;
	}
	tmp_tokens_args[i] = NULL;
	i = 0;
	while (tmp_tokens_args[i])
	{
		tokens_args[i] = ft_split(tmp_tokens_args[i], ' ');
		free(tmp_tokens_args[i]);
		i++;
	}
	tokens_args[i] = NULL;
	free(tmp_tokens_args);
}

t_data	*init(int ac, char *av[], char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->tokens_args = (char ***)malloc(sizeof(char **) * ac - 2);
	data->input_file = ft_strdup(av[1]);
	data->output_file = ft_strdup(av[ac - 1]);
	data->env = get_envs(envp);
	fill_tokens_args(data->tokens_args, ac, av);
	return (data);
}

int     main(int ac, char *av[], char **envp)
{
	t_data	*data;

	if (ac == 5)
	{
		data = init(ac, av, envp);
		fork_pipes(data, envp);
	}
	else
	{
		ft_putstr_fd("error argument\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
    return (EXIT_SUCCESS);
}