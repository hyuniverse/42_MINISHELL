/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:06:24 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/22 15:28:25 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredoc(t_phrase *phrase)
{
	t_token	*temp;
	
	temp = phrase->head;
	if (phrase->type == 4)
	{
		while (temp != NULL && temp->type == 4)
		{
			make_hd_file(temp);
			temp = temp->next;
		}
	}
}

int	make_hd_file(t_token *token)
{
	int		fd;
	char	*path;
	char	*buffer;
	char	*eof;

	eof = ft_substr(token->data, 2, ft_strlen(token->data) - 2);
	path = ft_substr("/Users/siychoi/temp/.heredoc1", 0, 30);
	while (1)
	{
		printf("path = %s\n", path);
		if (access(path, F_OK) == 0)
			path = ft_strjoin(path, "1");
		else
		{
			fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			break;
		}
	}
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
			exit(1);
		if (ms_strncmp(buffer, eof, ft_strlen(eof)) == 0)
			break;
		ft_putstr_fd(buffer, fd);
		free(buffer);
	}
	return (fd);
}
