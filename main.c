#include "get_next_line_bonus.h"

/*
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
*/
int main()
{
	char	*line;
	int fd = open("get_next_line.h", O_RDWR);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}
