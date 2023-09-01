/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:05:18 by vtavitia          #+#    #+#             */
/*   Updated: 2023/06/13 16:06:07 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_msg(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		k;

	join = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)));
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	k = i;
	i = 0;
	while (s2[i])
	{
		join[k] = s2[i];
		i++;
		k++;
	}
	join[k] = '\0';
	return (join);
}

int	ft_strlen(const char *str)
{
	int		i;
	char	*str1;

	if (!str)
		return (0);
	str1 = (char *)str;
	i = 0;
	while (str1[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{		
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *) s2)[i]);
		i++;
	}
	return (0);
}

int	set_infile(int *infile, char **argv, int argc, char **envp)
{
	int	result;

	result = 0;
	*infile = open(argv[1], O_RDONLY, 0644);
	if (*infile == -1)
		write(1, "No such file or directory\n", 26);
	if (check_command(argv[2], envp, argc) == 0 || *infile == -1)
	{
		*infile = open("TEMPORARYFILETODELETE", O_RDONLY | O_CREAT, 0644);
		if (*infile == -1)
			error_msg("Error\nInput file opening error/not found");
		result = 1;
	}
	return (result);
}
