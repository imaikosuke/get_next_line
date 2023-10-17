/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koimai <koimai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:15:19 by koimai            #+#    #+#             */
/*   Updated: 2023/10/17 11:15:53 by koimai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 3

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>

size_t	ft_strlen(char *str);
int		ft_strchr(char *s);
char	*ft_strjoin_clear(char *s1, char *s2);
char	*reset_line(char *line);
char	*modified_line(char *line);
char	*get_next_line(int fd);

#endif