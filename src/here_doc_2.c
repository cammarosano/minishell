#include "header.h"

static void	display_warning_heredoc(char *word)
{
	ft_putstr_fd("Minishell: Warning: here-document delimited by end-of-\
file (wanted `", 1);
	ft_putstr_fd(word, 1);
	ft_putendl_fd("')", 1);
}

static char	*generate_filename(t_list **hd_files)
{
	char	*name;
	int		size;
	char	*seq_n;

	size = ft_strlen(HEREDOC_FILE) + 3;
	name = malloc(size);
	if (!name)
		return (NULL);
	ft_strlcpy(name, HEREDOC_FILE, size);
	seq_n = ft_itoa(ft_lstsize(*hd_files));
	if (!seq_n)
	{
		free(name);
		return (NULL);
	}
	ft_strlcat(name, seq_n, size);
	free(seq_n);
	return (name);
}

// generate filename, open it and, add to list
static int	create_file(t_list **hd_files, char **file_name)
{
	char	*name;
	int		fd;
	t_list	*node;

	name = generate_filename(hd_files);
	if (!name)
		return (-1);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		ft_perror("open");
		free(name);
		return (-1);
	}
	node = ft_lstnew(name);
	if (!node)
	{
		close(fd);
		free(name);
		return (-1);
	}
	ft_lstadd_back(hd_files, node);
	*file_name = name;
	return (fd);
}

// creates a file with content from user input
// includes the filename in hd_files list
// returns the file name
char	*create_heredoc(char *word, t_list **hd_files)
{
	int		fd_file;
	char	*line;
	char	*file_name;

	fd_file = create_file(hd_files, &file_name);
	if (fd_file == -1)
		return (NULL);
	line = readline("> ");
	while (line && ft_strcmp(line, word) != 0)
	{
		write(fd_file, line, ft_strlen(line));
		write(fd_file, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (!line)
		display_warning_heredoc(word);
	free(line);
	close(fd_file);
	return (file_name);
}
