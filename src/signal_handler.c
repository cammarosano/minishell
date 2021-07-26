#include "header.h"

void	sigint_prompt(int signal_code)
{
	(void)signal_code;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_noninteract(int signal_code)
{
	if (signal_code == SIGQUIT)
		ft_putstr_fd("Quit", 1);
	write(1, "\n", 1);
}

// the ^\ is erased from the display and the signal is ignored.
// and execd binary will have the standard behavior to sigquit (not ignored)
void	sigquit_handler(int signal_code)
{
	ft_putstr_fd("\b\b  \b\b", 1);
	(void)signal_code;
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, sigquit_handler);
}

void	reset_signal_handlers(void)
{
	signal(SIGINT, sig_noninteract);
	signal(SIGQUIT, sig_noninteract);
}
