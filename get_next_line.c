/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:08:26 by vminomiy          #+#    #+#             */
/*   Updated: 2020/03/10 18:49:26 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_calloc(int size)
{
	char	*s;
	int		i;

	i = 0;
	s = (char *)malloc(sizeof(char) * size);
	while (i < size)
	{
		s[i] = '\0';
		i++;
	}
	return (s);
}

int		ft_findstr(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

char	*ft_substr(char *s, int start, int end)
{
	int		size;
	char	*str;
	int		i;

	i = 0;
	size = end - start;
	str = ft_calloc(size +1);
	while (i < size)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	int		j;
	char	*str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = ft_calloc(len1 + len2 + 1);
	i = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		str[i + j] = s2[j];
		j++;
	}
	if (s1)
		free(s1);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	static char *str;
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	char		ret;
	int			pos;

	if (!line)
		return (-1);
	if (!(str) && !(str = ft_calloc(1)))
		return (-1);
	while (ft_findstr(str, '\n') < 0 && (ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		str = ft_strjoin(str, buffer);
	}
	pos = ft_findstr(str, '\n');
	if (pos >= 0)
	{
		*line = ft_substr(str, 0, pos);
		tmp = str;
		str = ft_substr(str, pos + 1, ft_findstr(str, '\0'));
		free(tmp);
		return (1);
	}
	else
	{
		*line = ft_substr(str, 0, ft_findstr(str, '\0'));
		free(str);
		return (0);
	}
}
