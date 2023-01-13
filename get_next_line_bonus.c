/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaddouc <hhaddouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:50:03 by hhaddouc          #+#    #+#             */
/*   Updated: 2021/11/29 07:01:14 by hhaddouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*left_fun(int fd, char *left)
{
	char	*buff;
	int		bytes;

	buff = malloc (BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(left, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		left = ft_strjoin(left, buff);
	}
	free(buff);
	return (left);
}

char	*new_left(char *left)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (left[i] && left[i] != '\n')
		i++;
	if (!left)
		return (NULL);
	str = (char *)malloc(ft_strlen(left) - i + 1);
	if (!str)
		return (NULL);
	if (left[i] == '\n')
		i++;
	j = 0;
	while (left[i])
		str[j++] = left[i++];
	str[j] = '\0';
	free(left);
	return (str);
}

char	*get_line(char *left)
{
	int		i;
	char	*str;

	i = 0;
	if (!left[i])
		return (NULL);
	while (left[i] && left[i] != '\n')
		i++;
	str = (char *)malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (left[i] && left[i] != '\n')
	{
		str[i] = left[i];
		i++;
	}
	if (left[i] == '\n')
	{
		str[i] = left[i];
		i++;
	}	
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*left[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left[fd] = left_fun(fd, left[fd]);
	if (!left[fd])
		return (NULL);
	line = get_line(left[fd]);
	left[fd] = new_left(left[fd]);
	if (!left[fd][0])
	{
		free(left[fd]);
		left[fd] = NULL;
	}
	return (line);
}
