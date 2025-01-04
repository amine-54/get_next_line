/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:15:05 by mmanyani          #+#    #+#             */
/*   Updated: 2025/01/04 14:27:05 by mmanyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*actual_line(char *holder)
{
	char	*line;
	int		i;

	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (holder[i] && holder[i] != '\n')
	{
		line[i] = holder[i];
		i++;
	}
	if (holder[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_holder(char *holder)
{
	char	*new_holder;
	int		i;
	int		j;

	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	new_holder = malloc(sizeof(char) * (ft_strlen(holder) - i + 1));
	if (new_holder == NULL)
		return (NULL);
	i++;
	j = 0;
	while (holder[i])
	{
		new_holder[j] = holder[i];
		j++;
		i++;
	}
	new_holder[j] = '\0';
	free(holder);
	return (new_holder);
}

char	*read_and_hold(int fd, char *holding)
{
	char	*buffer;
	ssize_t	bytes_returned;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	bytes_returned = 1;
	while (ft_strchr(holding, '\n') == NULL && bytes_returned != 0)
	{
		bytes_returned = read(fd, buffer, BUFFER_SIZE);
		if (bytes_returned == -1)
		{
			free(buffer);
			return (NULL);
		}
		holding = ft_strjoin(holding , buffer);
	}
	return (holding);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*buffer;
	char		*line;
	ssize_t		bytes_returned;

	/*if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	bytes_returned = 1;
	while (ft_strchr(holder, '\n') == NULL && bytes_returned != 0)
	{
		bytes_returned = read(fd, buffer, BUFFER_SIZE);
		if (bytes_returned == -1)
		{
			free(buffer);
			return (NULL);
		}
		holder = ft_strjoin(holder, buffer);
	}
	if (holder[0] == '\0')
		return (NULL);
	*/
	holder = read_and_hold(fd, holder);
	if (holder == NULL)
		return (NULL);
	line = actual_line(holder);
	holder = update_holder(holder);
	return (line);
}

int main()
{
	int fd;
	char	*line;

	fd = open("file.txt", O_RDWR);

	printf("%s", line = get_next_line(fd));
	printf("%s", line = get_next_line(fd));
	line = get_next_line(fd);
	printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));

}
