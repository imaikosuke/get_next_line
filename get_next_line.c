/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koimai <koimai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:15:16 by koimai            #+#    #+#             */
/*   Updated: 2023/10/10 19:50:55 by koimai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*duplicate;

	len = 0;
	while (str[len] != '\0')
		len++;
	duplicate = (char *)malloc((len + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		duplicate[i] = str[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		buffer[BUFFER_SIZE + 1];
	char		*newline_pos;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder[fd])
		remainder[fd] = ft_strdup("");
	while (!(newline_pos = ft_strchr(remainder[fd], '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break;
		buffer[bytes_read] = '\0';
		char *temp = remainder[fd];
		remainder[fd] = ft_strjoin(remainder[fd], buffer);
		free(temp);
		if (!remainder[fd])
			return (NULL);
	}
	if (bytes_read <= 0 && !*remainder[fd])
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	char *line = ft_strdup_chr(remainder[fd], '\n');
	newline_pos = ft_strchr(remainder[fd], '\n');
	if (newline_pos)
	{
		char *temp = remainder[fd];
		remainder[fd] = ft_strdup(newline_pos + 1);
		free(temp);
	}
	else
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
	}
	return (line);
}


#include <stdio.h>
int main(void)
{
	int fd;
	char *result;
	int i;

	fd = open("test.txt", O_RDWR);
	i = 0;
	result = get_next_line(fd);
	while (result != NULL)
	{
		i++;
		printf("%d->%s\n", i, result);
		result = get_next_line(fd);
	}
	printf("finish");
	return (0);
}
