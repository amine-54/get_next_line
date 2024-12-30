#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 5

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);



static char	*read_to_buffer(int fd, char *stash)
{
    char	*buffer;
    int		bytes_read;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    bytes_read = 1;
    while (!ft_strchr(stash, '\n') && bytes_read != 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        stash = ft_strjoin(stash, buffer);
    }
    free(buffer);
    return (stash);
}

static char	*extract_line(char *stash)
{
    int		i;
    char	*line;

    i = 0;
    if (!stash[i])
        return (NULL);
    while (stash[i] && stash[i] != '\n')
        i++;
    line = malloc(sizeof(char) * (i + 2));
    if (!line)
        return (NULL);
    i = 0;
    while (stash[i] && stash[i] != '\n')
    {
        line[i] = stash[i];
        i++;
    }
    if (stash[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return (line);
}

static char	*update_stash(char *stash)
{
    int		i;
    int		j;
    char	*new_stash;

    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (!stash[i])
    {
        free(stash);
        return (NULL);
    }
    new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
    if (!new_stash)
        return (NULL);
    i++;
    j = 0;
    while (stash[i])
        new_stash[j++] = stash[i++];
    new_stash[j] = '\0';
    free(stash);
    return (new_stash);
}

char	*get_next_line(int fd)
{
    char		*line;
    static char	*stash;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stash = read_to_buffer(fd, stash);
    if (!stash)
        return (NULL);
    line = extract_line(stash);
    stash = update_stash(stash);
    return (line);
}


char	*ft_strchr(const char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if ((char)c == '\0')
        return ((char *)s);
    return (NULL);
}

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

size_t	ft_strlen(const char *s)
{
    size_t	i;

    i = 0;
    while (s[i])
        i++;
    return (i);
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
