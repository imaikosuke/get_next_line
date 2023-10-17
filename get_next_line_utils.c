/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koimai <koimai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:42:47 by koimai            #+#    #+#             */
/*   Updated: 2023/10/16 14:29:44 by koimai           ###   ########.fr       */
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
