/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:21:38 by siychoi           #+#    #+#             */
/*   Updated: 2023/11/15 14:21:38 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	get_buffer_idx(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		i++;
		if (buffer[i - 1] == '\n')
			break ;
	}
	return (i);
}

char	*get_buffer(int fd, char *buffer)
{
	char	*temp;
	int		read_byte;

	read_byte = 1;
	temp = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	while (!gnl_strchr(buffer, '\n') && read_byte != 0)
	{
		read_byte = read(fd, temp, BUFFER_SIZE);
		if (read_byte == 0)
			break ;
		temp[read_byte] = '\0';
		buffer = gnl_strjoin(buffer, temp);
	}
	free(temp);
	return (buffer);
}

char	*cut_one_line(const char *buffer)
{
	char	*result;
	int		i;
	int		len;

	i = 0;
	len = get_buffer_idx((char *)buffer);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = buffer[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*cut_buffer_line(char *buffer)
{
	char	*result;
	int		i;
	int		j;

	i = get_buffer_idx(buffer);
	j = 0;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	result = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (result == NULL)
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i])
		result[j++] = buffer[i++];
	result[j] = '\0';
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*buffer[FD_MAX];

	if (BUFFER_SIZE < 1 || fd == 2 || fd < 0)
		return (NULL);
	if (read(fd, NULL, 0) == -1)
	{
		if (buffer[fd])
			free(buffer[fd]);
		buffer[fd] = 0;
		return (NULL);
	}
	buffer[fd] = get_buffer(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	result = cut_one_line(buffer[fd]);
	if (!result)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	else
		buffer[fd] = cut_buffer_line(buffer[fd]);
	return (result);
}
