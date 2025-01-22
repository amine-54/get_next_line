#include "get_next_line.h"


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


