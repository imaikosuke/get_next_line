/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koimai <koimai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:15:16 by koimai            #+#    #+#             */
/*   Updated: 2023/10/17 19:59:55 by koimai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	ft_strchr(char *s)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (i == len && s[0] != '\0')
		return (1);
	else
		return (0);
}

char	*ft_strjoin_clear(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	result = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s1 != NULL && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 != NULL && s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}


char	*reset_line(char *line)
{
	size_t	len;
	size_t	len_to_newline;
	size_t	i;
	char	*str;

	len = ft_strlen(line);
	if (len == 0)
	{
		free(line);
		return (NULL);
	}
	len_to_newline = 0;
	while (line[len_to_newline] != '\n' && line[len_to_newline] != '\0')
		len_to_newline++;
	if (len - len_to_newline != 1 || line[BUFFER_SIZE - 1] == '\n')
		len_to_newline++;
	str = (char *)malloc((len - len_to_newline + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (line[len_to_newline] != '\0')
	{
		str[i] = line[len_to_newline];
		len_to_newline++;
		i++;
	}
	str[i] = '\0';
	free(line);
	return (str);
}

char	*modified_line(char *line)
{
	char	*str;
	size_t	i;
	size_t	len;

	if (!ft_strlen(line))
		return (NULL);
	len = 0;
	while (line[len] != '\n' && line[len] == '\0')
		len++;
	if (line[len] == '\n')
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while ((line[i] != '\0' && line[i] != '\n'))
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*line;
	char		*result;
	long long	byte_num;

	result = NULL;
	if (tmp != NULL)
		result = ft_strjoin_clear(result, tmp);
	line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	byte_num = read(fd, line, BUFFER_SIZE);
	if (byte_num == -1)
		return (NULL);
	line[byte_num] = '\0';
	while (ft_strchr(line))
	{
		result = ft_strjoin_clear(result, line);
		byte_num = read(fd, line, BUFFER_SIZE);
		if (byte_num == -1)
		{
			free(line);
			return (NULL);
		}
		line[byte_num] = '\0';
	}
	result = ft_strjoin_clear(result, modified_line(line));
	tmp = reset_line(line);
	return (result);
}

#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*result;
	int		i;

	fd = open("test.txt", O_RDONLY);
	i = 0;
	result = "(null)";
	result = get_next_line(fd);
	while (result != NULL)
	{
		i++;
		printf("%s", result);
		result = get_next_line(fd);
	}
	// printf("finish\n");
	free(result);
	return (0);
}