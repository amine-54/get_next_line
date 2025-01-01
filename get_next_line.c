/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:15:05 by mmanyani          #+#    #+#             */
/*   Updated: 2024/12/22 18:19:39 by mmanyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUFFER_SIZE 3

char	*get_next_line(int fd)
{
	char buffer[BUFFER_SIZE + 1];
	ssize_t bytes_read;
	int i = 0;
	char *line;
	int found_new_line = 0;

	bytes_read = 1;
	while (found_new_line == 0 && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		i = 0;
		while (buffer[i])
		{
			if (buffer[i] == '\n')
			{
				found_new_line = 1;
				break;
			}
			i++;
		}
		int line_len = ft_strlen(line);
		char *temp = malloc(bytes_read + line_len + 1);
		if (temp == NULL)
		{
			if (line)
				free(line);
			return (NULL);
		}
		int j = 0;
		if (line)
		{
			while (j < line_len)
			{
				temp[j] = line[j];
				j++;
			}
			free(line);
		}
		i = 0;
		while (buffer[i])
		{
			temp[j] = buffer[i];
			j++;
			i++;
		}
		temp[j] = '\0';
		line = temp;
	}

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	char *next_line = malloc(i + 2);
	if (next_line == NULL)
		return (NULL);
	while (line[i] && line[i] != '\n')
	{
		next_line


}




int main()
{
	int fd = open("file.txt", O_RDWR);
	printf("%s\n", get_next_line(fd));
}
