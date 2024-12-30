#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 5

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

/*
char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
*/
char	*ft_strjoin(char *s1, char *s2)
{
    char	*str;
    size_t	i;
    size_t	j;

    if (!s1)
    {
        s1 = malloc(1);
        s1[0] = '\0';
    }
    str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!str)
        return (NULL);
    i = -1;
    while (s1[++i])
        str[i] = s1[i];
    j = 0;
    while (s2[j])
        str[i++] = s2[j++];
    str[i] = '\0';
    free(s1);
    return (str);
}

char	*extract_line(char *leftover)
{
	int	i;
	char	*line;

	i = 0;
	if (!leftover[i])
		return (NULL);
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

	j = 0;
	while (leftover[i])
	{
		new_leftover[j] = leftover[i];
		j++;
		i++;
	}
	new_leftover[j] = '\0';
	free(leftover);

	return (new_leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover = NULL;
	char	*buffer;
	ssize_t	bytes_read;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);

	bytes_read = 1;
	while (bytes_read != 0 && ft_strchr(leftover, '\n') == NULL)
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

	if (leftover ==  NULL)
		return (NULL);
	line = extract_line(leftover);
	leftover = update_leftover(leftover);

	return (line);
}

int main()
{
    int fd = open("file.txt", O_CREAT | O_RDWR, 0644);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    char *line;
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
