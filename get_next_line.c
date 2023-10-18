/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koimai <koimai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:28:11 by koimai            #+#    #+#             */
/*   Updated: 2023/10/18 15:38:10 by koimai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
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
// 		printf("%s", result);
// 		result = get_next_line(fd);
// 	}
// 	// printf("finish\n");
// 	free(result);
// 	return (0);
// }