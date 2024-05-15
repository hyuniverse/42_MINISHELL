/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:22:08 by siychoi           #+#    #+#             */
/*   Updated: 2023/11/15 14:22:08 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 10496
# endif

char	*get_buffer(int fd, char *buffer);
char	*cut_one_line(const char *buffer);
char	*cut_buffer_line(char *buffer);
char	*get_next_line(int fd);
int		get_buffer_idx(char *buffer);

int		gnl_strchr(char *str, char c);
char	*gnl_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);

#endif