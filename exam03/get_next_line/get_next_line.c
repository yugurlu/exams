
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strchr(char *s)
{
	int i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if(s[i] == '\n')
			return (0);
		i++;
	}
	return(1);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *join;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = 0;
	}
	if(!s2)
		return (0);
	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
		join[j++] = s1[i++];
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = 0;
	free(s1);
	return (join);
}

char *handle(char *buffer)
{
	int i = 0;
	int j = 0;
	char *new_buffer;

	while (buffer[i] && buffer[i] != '\n')
		i++;
	if(!buffer[i])
	{
		free(buffer);
		return NULL;
	}
	new_buffer = malloc((ft_strlen(buffer) - i) + 1);
	i++;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = 0;
	free(buffer);
	return(new_buffer);
}

char *clear_line(char *buffer)
{
	int i = 0;
	int j = 0;
	char *clear;

	while (buffer[i] && buffer[i] != '\n')
		i++;
	clear = malloc(i + 2);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		clear[j++] = buffer[i++];
	if (buffer[i] == '\n')
		clear[j++] = '\n';
	clear[j] = 0;
	if(!ft_strlen(clear))
	{
		free(clear);
		return NULL;
	}
	return(clear);
}

char *read_line(int fd, char *buffer)
{
	char *str;
	int byte = 1;

	str = malloc(BUFFER_SIZE + 1);
	while (ft_strchr(buffer) && byte != 0)
	{
		byte = read(fd, str, BUFFER_SIZE);
		if(byte == -1)
		{
			free(str);
			return NULL;
		}
		str[byte] = 0;
		buffer = ft_strjoin(buffer, str);
	}
	free(str);
	return(buffer);
}

char *get_next_line(int fd)
{
	char *line;
	static char *buffer;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = read_line(fd, buffer);
	line = clear_line(buffer);
	buffer = handle(buffer);
	return(line);
}
