/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:32:58 by vtavitia          #+#    #+#             */
/*   Updated: 2023/06/14 13:14:39 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	read_line(char **buffer)
{
	char	*tmp;
	int		i;
	int		bytes;
	char	c;

	i = 0;
	bytes = 0;
	tmp = (char *)malloc(sizeof(char) * 9999);
	if (!tmp)
		return (1);
	bytes = read(0, &c, 1);
	while (bytes > 0 && c != '\n' && c != '\0')
	{
		if (c != '\n' || c != '\0')
			tmp[i] = c;
		i++;
		bytes = read(0, &c, 1);
	}
	if (bytes > 0)
		tmp[i] = '\n';
	tmp[++i] = '\0';
	*buffer = tmp;
	return (bytes);
}

static void	here_doc_child(char **buff, char *lim, int *hdpipe)
{
	char	*buffer;

	buffer = *buff;
	close(hdpipe[0]);
	while (read_line(&buffer))
	{
		if (ft_strncmp(buffer, lim, ft_strlen(lim)) == 0)
		{
			free(buffer);
			exit(0);
		}
		write(hdpipe[1], buffer, ft_strlen(buffer));
		free(buffer);
	}
	close(hdpipe[1]);
	exit(0);
}

void	do_here_doc(char *lim, int argc)
{
	int		hdpipe[2];
	int		pid;
	char	*buffer;

	if (pipe(hdpipe) == -1)
		error_msg("Error\nPipe Creation Failed\n");
	pid = fork();
	if (pid == 0)
		here_doc_child(&buffer, lim, hdpipe);
	else
	{
		close(hdpipe[1]);
		dup2(hdpipe[0], STDIN_FILENO);
		close(hdpipe[0]);
		wait(NULL);
	}
}
