/*
 * Copyright (c) 2008 David Winter (dawi2332@gmail.com)
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

/* $Id: getpass.c 277 2008-12-14 00:23:50Z david $ */

/*
 * getpass.c -- Wrapper/replacement for getpass(3) function.
 */

#include "system.h"
#include "error.h"

#ifdef HAVE_SIGNAL_H
#include	<signal.h>
#endif /* HAVE_SIGNAL_H */
#ifdef HAVE_TERMIOS_H
#include	<termios.h>
#endif /* HAVE_TERMIOS_H */

char *
getpass(const char *prompt)
{
	static char		buf[MAX_STRING_LEN];
	char			*ptr;
	sigset_t		sig, osig;
	struct termios	ts, ots;
	FILE			*fp;
	int				c;

	if ((fp = fopen(ctermid(NULL), "r+")) == NULL)
		error(EXIT_INVALIDFILE, "can't read from terminal");
	setbuf(fp, NULL);

	sigemptyset(&sig);
	sigaddset(&sig, SIGINT);
	sigaddset(&sig, SIGTSTP);
	sigprocmask(SIG_BLOCK, &sig, &osig);

	tcgetattr(fileno(fp), &ts);
	ots = ts;
	ts.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
	tcsetattr(fileno(fp), TCSAFLUSH, &ts);
	fputs(prompt, fp);

	if (fgets(buf, MAX_STRING_LEN, fp) != NULL)
	{
		ptr = strchr(buf, '\n');
		if (ptr != NULL)
			*ptr = '\0';
		putc('\n', fp);
	}
	if (feof(fp))
	{
		error(EXIT_OVERFLOW, "reached EOF before first character");
	}
	if (ferror(fp))
	{
		error(EXIT_OVERFLOW, "the password must not contain more than %i characters", MAX_STRING_LEN);
	}

	tcsetattr(fileno(fp), TCSAFLUSH, &ots);
	sigprocmask(SIG_SETMASK, &osig, NULL);
	fclose(fp);
	return(buf);
}
