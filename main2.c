#include "get_next_line.h"


int main()
{
	char	*line;
	int fd = open("get_next_line.h", O_RDWR);
/*
	line = get_next_line(fd);

	printf("%s", line);
	close(fd);
*/
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	

}


