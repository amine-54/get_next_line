#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 5



char	*get_next_line(int fd)
{
	char	*line;
	char	*buffer;
	static char *leftover;
	ssize_t bytes_read;

	buffer = malloc(sizeof(ssize_t) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);

	bytes_read = 1;
	while (bytes_read != 0 && ft_strchr(buffer, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
	}
	free(buffer);

	int i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;          // strlen ??
	line = malloc(sizeof(char) * (i + 2));

	i = 0;
	while(leftover[i] && leftover[i] != '\n')
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

	i = 0;
	int j = 0;
	char	*new_leftover;

	while (leftover[i] && leftover[i] != '\n')
		i++;
	new_leftover = malloc(ft_strlen(leftover) - i + 1);
	if (new_leftover == NULL)
		return (NULL);

	i++;
	while (leftover[i])
	{
		new_leftover[j] = leftover[i];
		j++;
		i++
	}
	new_leftover[j] = '\0';

	free(leftover);
	leftover = new_leftover;

	return (line);
}
