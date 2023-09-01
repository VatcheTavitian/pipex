/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:49:47 by vtavitia          #+#    #+#             */
/*   Updated: 2023/06/14 13:12:12 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;

	index = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[index] && index < dstsize - 1)
	{
		dst[index] = src[index];
		index++;
	}
	if (index < dstsize)
		dst[index] = '\0';
	return ((size_t)ft_strlen(src));
}

void	path_to_array(char ***paths, char **envp)
{
	int		i;
	int		size;
	char	*path;

	i = 0;
	size = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	while (envp[i][size])
		size++;
	size -= 5;
	path = (char *)malloc(sizeof(char) * size + 1);
	if (!path)
		error_msg("Malloc failed");
	ft_strlcpy(path, &envp[i][5], size + 1);
	*paths = ft_split(path, ':');
	free(path);
}

char	*cut_argv(char *argv)
{
	int		i;
	int		size;
	char	*cut;

	i = 0;
	while (argv[i] && argv[i] != ' ')
		i++;
	size = i;
	cut = (char *)malloc(sizeof(char) * (i + 1));
	if (!cut)
		error_msg("Error\nMallocing failed");
	i = 0;
	while (i < size)
	{
		cut[i] = argv[i];
		i++;
	}
	cut[i] = '\0';
	return (cut);
}

int	join_commands(char **paths, char *argv, int argc)
{
	int		i;
	int		j;
	char	*comm;	
	char	*tmp;
	int		check;

	i = 2;
	j = 0;
	check = 0;
	argv = cut_argv(argv);
	while (paths[j] != NULL)
	{
		comm = ft_strjoin("/", argv);
		tmp = comm;
		comm = ft_strjoin(paths[j], tmp);
		if (access(comm, R_OK) == 0)
			check++;
		j++;
		free(comm);
		free(tmp);
	}
	free(argv);
	return (check);
}

int	check_command(char *argv, char **envp, int argc)
{
	int		i;
	char	**paths;
	int		check;

	path_to_array(&paths, envp);
	i = 2;
	check = 0;
	check = join_commands(paths, argv, argc);
	free_all(paths);
	return (check);
}
