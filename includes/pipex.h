/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:03:57 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/10 12:04:18 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../dlist/dlists.h"

# define READ 0
# define WRITE 1

typedef struct s_env
{
	char		*key;
	char		*value;
	char		sep;
	int			has_value;
}				t_env;

typedef struct s_data
{
	char	***tokens_args;
	char	*input_file;
	char	*output_file;
    int     i;
    t_dlist env;
    char    *bin;
}				t_data;

/*
** Env main functions
*/
t_dlist	get_envs(char **env);
t_env	*env_create(char *key, char *value);
/*
** Env utils and destructor
*/
char	*get_key(char *line);
char	*get_value(char *line);
void	env_destroy(void *env_);

void	fork_pipes(t_data *data, char **envp);


#endif
