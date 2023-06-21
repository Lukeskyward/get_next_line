/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasda- <lucasda-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:17:21 by lucasda-          #+#    #+#             */
/*   Updated: 2023/06/21 15:19:32 by lucasda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_str(int fd, char *str)
{
	char		*tab;
	char		*tmp;
	int			read_bytes;

	tab = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!tab)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !(ft_strchr(tab, '\n')))
	{
		read_bytes = read(fd, tab, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			if (str)
				free(str);
			free(tab);
			return (NULL);
		}
		tab[read_bytes] = '\0';
		tmp = ft_strjoin(str, tab);
		free(str);
		str = tmp;
	}
	free(tab);
	return (str);
}

char	*get_theline(char *str)
{
	char	*result;
	int		i;

	i = 0;
	if (!(str[i]))
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	result = ft_calloc(sizeof(char), (i + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{	
		result[i] = str[i];
		i++;
	}
	else
		result[i] = '\0';
	return (result);
}

char	*get_new_str(char *str)
{
	char	*new_str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (!(str[i] == '\n'))
	{
		free(str);
		return (NULL);
	}
	new_str = ft_calloc(sizeof(char), (ft_strlen(str) - i));
	if (!new_str)
		return (NULL);
	i++;
	while (str[i] != '\0')
	{
		new_str[count] = str[i];
		count++;
		i++;
	}
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char		*str[FOPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	str[fd] = get_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = get_theline(str[fd]);
	str[fd] = get_new_str(str[fd]);
	return (line);
}
