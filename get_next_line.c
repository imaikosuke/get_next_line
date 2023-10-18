/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koimai <koimai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:28:11 by koimai            #+#    #+#             */
/*   Updated: 2023/10/18 00:27:26 by koimai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ft_read_to_line(fd, line);
	if (!line)
		return (NULL);
	result = ft_modify_line(line);
	line = ft_save_after_linebreak(line);
	return (result);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*result;
// 	int		i;

// 	fd = open("test.txt", O_RDONLY);
// 	i = 0;
// 	result = "(null)";
// 	result = get_next_line(fd);
// 	while (result != NULL)
// 	{
// 		i++;
// 		printf("%d->%s", i, result);
// 		result = get_next_line(fd);
// 	}
// 	// printf("finish\n");
// 	free(result);
// 	return (0);
// }