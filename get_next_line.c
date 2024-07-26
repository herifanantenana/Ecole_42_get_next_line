/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakotom <arakotom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:53:30 by arakotom          #+#    #+#             */
/*   Updated: 2024/07/26 20:15:05 by arakotom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_br_index(char *str)
{
	int	i;

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
	int		line_len;
	int		i;

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
	int		all_line_len;
	int		br_index;
	int		i;

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
	static char	*all_line;
	char		*buff;
	int			byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	byte_read = 1;
	while (byte_read != 0 && !gnl_strchr(all_line, '\n'))
	{
		byte_read = read(fd, buff, BUFFER_SIZE);
		if (byte_read == -1)
			return (free_all(buff, all_line));
		if (byte_read == 0)
			break ;
		*(buff + byte_read) = '\0';
		all_line = gnl_strjoin(all_line, buff);
	}
	free(buff);
	buff = get_line(all_line);
	all_line = get_line_left(all_line);
	return (buff);
}
