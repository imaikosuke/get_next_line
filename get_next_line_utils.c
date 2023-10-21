/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koimai <koimai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:38:45 by koimai            #+#    #+#             */
/*   Updated: 2023/10/21 17:54:02 by koimai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_initialize_target(char *target)
{
	target = (char *)malloc(1 * sizeof(char));
	if (!target)
		return (NULL);
	target[0] = '\0';
	return (target);
}

size_t	ft_len(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_len(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *target, char *buf)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!target)
		target = ft_initialize_target(target);
	if (!target)
		return (NULL);
	str = (char *)malloc(((ft_len(target) + ft_len(buf)) + 1) * sizeof(char));
	if (!str)
	{
		free(target);
		return (NULL);
	}
	i = -1;
	if (target)
		while (target[++i] != '\0')
			str[i] = target[i];
	j = 0;
	while (buf[j] != '\0')
		str[i++] = buf[j++];
	str[ft_len(target) + ft_len(buf)] = '\0';
	free(target);
	return (str);
}

char	*ft_save_after_linebreak(char *line)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = (char *)malloc((ft_len(line) - i + 1) * sizeof(char));
	if (!str)
	{
		free(line);
		return (NULL);
	}
	i++;
	j = 0;
	while (line[i] != '\0')
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}
