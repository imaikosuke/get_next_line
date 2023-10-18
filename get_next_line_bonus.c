/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koimai <koimai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:15:23 by koimai            #+#    #+#             */
/*   Updated: 2023/10/18 11:32:44 by koimai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_to_line(int fd, char *line)
{
	char	*buff;
	int		byte_size;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	byte_size = 1;
	while (!ft_strchr(line, '\n') && byte_size != 0)
	{
		byte_size = read(fd, buff, BUFFER_SIZE);
		if (byte_size == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byte_size] = '\0';
		line = ft_strjoin(line, buff);
	}
	free(buff);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*line[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line[fd] = ft_read_to_line(fd, line[fd]);
	if (!line[fd])
		return (NULL);
	result = ft_modify_line(line[fd]);
	line[fd] = ft_save_after_linebreak(line[fd]);
	return (result);
}
