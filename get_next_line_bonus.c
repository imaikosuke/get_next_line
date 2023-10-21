/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koimai <koimai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:15:23 by koimai            #+#    #+#             */
/*   Updated: 2023/10/21 16:54:52 by koimai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_modify_line(char *buffer)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = (char *)malloc((i + 1 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_read_to_line(int fd, char *line)
{
	char	*buffer;
	int		byte_size;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	byte_size = 1;
	while (!ft_strchr(line, '\n') && byte_size != 0)
	{
		byte_size = read(fd, buffer, BUFFER_SIZE);
		if (byte_size == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_size] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*line[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = ft_read_to_line(fd, line[fd]);
	if (!line[fd])
		return (NULL);
	result = ft_modify_line(line[fd]);
	line[fd] = ft_save_after_linebreak(line[fd]);
	return (result);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("file1: %s", line);
		free(line);
		line = get_next_line(fd2);
		printf("file2: %s", line);
		free(line);
		line = get_next_line(fd3);
		printf("file3: %s", line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}