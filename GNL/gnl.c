/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:09:34 by meandrad          #+#    #+#             */
/*   Updated: 2025/05/19 20:28:02 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*gnl(int fd);

#endif

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*gnl(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	pos;
	static int	red;
	char		line[70000];
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (pos >= red)
		{
			red = read(fd, buffer, BUFFER_SIZE);
			pos = 0;
			if (red <= 0)
				break ;
		}
		line[i] = buffer[pos];
		i++;
		if (buffer[pos++] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

int main (void)
{
	int fd;
	char *linha;

	fd = open("gnl.c", O_RDONLY);
	while ((linha = gnl(fd)) != NULL)
	{
		printf("%s", linha);
		free(linha);
	}
	close(fd);
	return (0);
}