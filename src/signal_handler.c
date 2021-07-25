#include "header.h"

// rl_replace_line only exists in the linux version of readline lib
void	sigint_handler(int signal_code)
{
	(void)signal_code;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

// the ^D is erased from the display and the signal is ignored.
// and execd binary will have the standard behavior to sigquit (not ignored)
void	sigquit_handler(int signal_code)
{
	write(1, "\b\b  \b\b", 6);
	(void)signal_code;
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
