#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

char	*extract_line(char *leftover)
{
	char	*line;
	int	i;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (leftover[i] && leftover[i] != '\n')
	{
		line[i] = leftover[i];
		i++;
	}
	if (leftover[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';

	return (line);
}

char	*update_leftover(char *leftover)
{
	char	*new_leftover;
	int	i;
	int	j;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	new_leftover = malloc(sizeof(char) * (ft_strlen(leftover) - i + 1));
	if (new_leftover == NULL)
		return (NULL);
	i++;
	j = 0;
	while (leftover[i])
	{
		new_leftover[j] = leftover[i];
		i++;
		j++;
	}
	free(leftover);
	new_leftover[j] = '\0';
	return (new_leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char	*buffer;
	ssize_t	bytes_read;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);

	bytes_read = 1;
	while (bytes_read != 0 !! ft_strchr(leftover, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read = -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
	}
	free(buffer);

	if (leftover == NULL)
		return (NULL);
	line = extract_line(leftover);
	leftover = update_leftover(leftover);

	return (line);
}
