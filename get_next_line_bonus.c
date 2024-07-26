/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakotom <arakotom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:46:16 by arakotom          #+#    #+#             */
/*   Updated: 2024/07/26 20:47:32 by arakotom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	get_br_index(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

static char	*free_all(char *buff, char *all_line)
{
	free(buff);
	free(all_line);
	return (NULL);
}

static char	*get_line(char *all_line)
{
	char	*line;
	size_t	line_len;
	size_t	i;

	if (!all_line || *all_line == '\0')
		return (NULL);
	line_len = get_br_index(all_line);
	line = (char *)malloc((line_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (all_line[i] && all_line[i] != '\n')
	{
		line[i] = all_line[i];
		i++;
	}
	if (all_line[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*get_line_left(char *all_line)
{
	char	*new_all_line;
	size_t	all_line_len;
	size_t	br_index;
	size_t	i;

	if (!all_line)
		return (NULL);
	if (all_line[0] == '\0')
	{
		free(all_line);
		return (NULL);
	}
	br_index = get_br_index(all_line);
	all_line_len = gnl_strlen(all_line);
	new_all_line = (char *)malloc((all_line_len - br_index + 1) * sizeof(char));
	if (!new_all_line)
		return (NULL);
	i = 0;
	while (all_line[br_index])
		new_all_line[i++] = all_line[br_index++];
	new_all_line[i] = '\0';
	free(all_line);
	return (new_all_line);
}

char	*get_next_line(int fd)
{
	static char	*all_line[MAX_FD];
	char		*buff;
	int			byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	byte_read = 1;
	while (byte_read != 0 && !gnl_strchr(all_line[fd], '\n'))
	{
		byte_read = read(fd, buff, BUFFER_SIZE);
		if (byte_read == -1)
			return (free_all(buff, all_line[fd]));
		if (byte_read == 0)
			break ;
		*(buff + byte_read) = '\0';
		all_line[fd] = gnl_strjoin(all_line[fd], buff);
	}
	free(buff);
	buff = get_line(all_line[fd]);
	all_line[fd] = get_line_left(all_line[fd]);
	return (buff);
}
