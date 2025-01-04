/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:15:05 by mmanyani          #+#    #+#             */
/*   Updated: 2025/01/04 16:47:33 by mmanyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*actual_line(char *holder)
{
	char	*line;
	int		i;

	i = 0;
	if (holder[i] == '\0')
		return (NULL);
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

	if (holder == NULL || holder[0] == '\0')
	{
		free(holder);
		return (NULL);
	}
	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	
	if (holder[i] == '\0')
	{
		free(holder);
		return (NULL);
	}
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
/*
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
		buffer[bytes_returned] = '\0';
		holding = ft_strjoin(holding , buffer);
	}
	free(buffer);
	return (holding);
}*/
/*
char	*get_next_line(int fd)
{
	static char	*holder = NULL; // Initialize holder to NULL
	char		*buffer;
	char		*line;
	ssize_t		bytes_returned;

	if (fd < 0 || BUFFER_SIZE <= 0)
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
		buffer[bytes_returned] = '\0';
		holder = ft_strjoin(holder, buffer);
	}

	free(buffer); // Free buffer after use

	if (holder == NULL || holder[0] == '\0') // Check if holder is NULL or empty
	{
		free(holder); // Free holder if it's not NULL
		holder = NULL; // Reset holder to NULL
		return (NULL);
	}

	line = actual_line(holder); // Allocate memory for line
	holder = update_holder(holder); // update_holder will reset holder to NULL if needed

	return (line); // Return the allocated line
}
*/


char	*get_next_line(int fd)
{
	static char	*holder;
	char		*buffer;
	char		*line;
	ssize_t		bytes_returned;

	if (fd < 0 || BUFFER_SIZE <= 0)
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
		buffer[bytes_returned] = '\0';
		holder = ft_strjoin(holder, buffer);
	}
	free(buffer);
	//holder = read_and_hold(fd, holder);
	/*if (holder[0] == '\0')
	{
		free(holder);
		return (NULL);
	}*/
	line = actual_line(holder);
	holder = update_holder(holder);
	//if (holder == NULL)
	//	return (NULL);
	return (line);
}

/*
int main()
{
	int fd;

	fd = open("file.txt", O_RDWR);

	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	if (get_next_line(fd) == NULL)
		printf("debugng line");
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}
*/


int main()
{
    char *line;
	int num = 1;
    int fd = open("file.txt", O_RDWR);

    while ((line = get_next_line(fd)))
    {
		if (!line)
		{
			printf("{!} line was not allocated. exiting...\n");
			return (1);
		}
        printf("{+} line %d: %s", num, line);
        free(line);
		num++;
    }

    close(fd);
    return (0);
}

