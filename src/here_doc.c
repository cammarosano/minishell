#include "header.h"

static int	subst_here_doc_redirections(t_list *redirs_lst, t_list **hd_files)
{
	t_redir	*redir;
	char	*file_name;

	while (redirs_lst)
	{
		redir = redirs_lst->content;
		if (redir->op == re_heredoc)
		{
			file_name = create_heredoc(redir->file, hd_files);
			if (!file_name)
				return (-1);
			redir->op = re_input;
			free(redir->file);
			redir->file = file_name;
		}
		redirs_lst = redirs_lst->next;
	}
	return (0);
}

// subtitutes >> redirections by a > from file created in the filesystem
// returns a list of thoses files (heredoc temp files)
int	get_here_docs(t_list *pipeline, t_list **hd_files)
{
	t_command	*command;

	*hd_files = NULL;
	while (pipeline)
	{
		command = pipeline->content;
		if (subst_here_doc_redirections(command->redirections, hd_files) == -1)
		{
			ft_lstclear(hd_files, delete_file);
			return (-1);
		}
		pipeline = pipeline->next;
	}
	return (0);
}
