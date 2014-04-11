/*
 * Copyright 2008, 2009, 2010, 2011, 2012 David Winter
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE.
 *
 */

/* $Id$ */

#include <system.h>
#include "readpasswd.h"
#ifdef HAVE_SIGNAL_H
#include	<signal.h>
#endif /* HAVE_SIGNAL_H */
#ifdef HAVE_TERMIOS_H
#include	<termios.h>
#endif /* HAVE_TERMIOS_H */

struct termios	oattr;
sigset_t	oset;

/*
 * reset_terminal -- resets interrupts and terminal attributes to whatever
 *                   it was before calling setup_terminal
 */
void
reset_terminal()
{
	if (!isatty(STDIN_FILENO))
		return;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &oattr);
	sigprocmask(SIG_SETMASK, &oset, NULL);
}

/*
 * setup_terminal -- masks interrupts and changes terminal attributes
 */
void
setup_terminal(int flags)
{
	struct termios	attr;
	sigset_t	set;

	if (!isatty(STDIN_FILENO) || !(flags & F_NOECHO))
		return;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTSTP);
	sigprocmask(SIG_BLOCK, &set, &oset);

	tcgetattr(STDIN_FILENO, &attr);
	tcgetattr(STDIN_FILENO, &oattr);
	attr.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
	atexit(reset_terminal);
}

/*
 * readpasswd -- reads bufsize-1 chars from stdin or tty
 */
char *
readpasswd(const char *prompt, char *buffer, size_t bufsize, int flags)
{
	size_t		len;
	char		*ptr;
	char		c;
	int		has_prompt;

	has_prompt = ((prompt != NULL) && (strlen(prompt) > 0) ? 1 : 0);
	memset(buffer, 0, sizeof(buffer));

	setup_terminal(flags);


	if (has_prompt)
		fputs(prompt, stdout);

	len = 0;
	while (((c = getchar()) != EOF) && (c != '\n'))
	{
		buffer[len] = c;

		if (++len >= bufsize)
		{
			break;
		}
	}
	buffer[len] = '\0';

	if (has_prompt)
		putchar('\n');

	reset_terminal();

	if (len >= bufsize)
		errx(EXIT_OVERFLOW, "the password must not contain more than %u characters", (unsigned int) bufsize-1);

	return buffer;
}
