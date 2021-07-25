/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:19:01 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 13:31:08 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** load_buffer reads data from fd to buffer, and places a '\0' after the
** last byte, or -1 (at index 0) in case of EOF.
** Returns 0 in case of error, 1 otherwise.
*/

int	load_buffer(int fd, char *buffer)
{
	ssize_t	ret;

	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret == -1)
		return (0);
	if (ret == 0)
		buffer[0] = -1;
	else
		buffer[ret] = '\0';
	return (1);
}

/*
** buffer_to_line allocates memory and transfers data from buffer to line.
** Returns 1 if '\n' has been reached, 0 if EOF has been reached, -1 in case
** of error, 2 otherwise (end of the buffer has been reached and must be
** reloaded). Data read from the buffer is removed form it and the remaining
** data is shifted to its initial portion.
*/

int	buffer_to_line(char *buffer, char **line)
{
	size_t	len;
	size_t	i;
	char	stop;

	len = line_len(buffer);
	*line = malloc(sizeof(char) * (len + 1));
	if (!*line)
		return (-1);
	i = 0;
	while (i < len)
	{
		(*line)[i] = buffer[i];
		i++;
	}
	(*line)[i] = '\0';
	stop = buffer[i];
	mem_shift(buffer, i);
	if (stop == '\n')
		return (1);
	if (stop == -1)
		return (0);
	return (2);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			ret;
	char		*temp;

	if (!line || BUFFER_SIZE < 1)
		return (-1);
	*line = NULL;
	if (!*buffer && !load_buffer(fd, buffer))
		return (-1);
	ret = buffer_to_line(buffer, line);
	while (ret > 1)
	{
		if (!load_buffer(fd, buffer))
			return (free_set_null(line));
		temp = *line;
		ret = buffer_to_line(buffer, line);
		if (ret == -1)
			return (free_set_null(&temp));
		*line = join(temp, *line);
		if (!*line)
			return (-1);
	}
	return (ret);
}
