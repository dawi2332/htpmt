/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
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
		return NULL;
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

	fgets(buf, MAX_STRING_LEN, fp);
	ptr = strchr(buf, '\n');
	*ptr = '\0';
	putc('\n', fp);

	tcsetattr(fileno(fp), TCSAFLUSH, &ots);
	sigprocmask(SIG_SETMASK, &osig, NULL);
	fclose(fp);
	return(buf);
}
