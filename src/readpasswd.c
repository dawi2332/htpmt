/*
 * Copyright 2008-2014 David Winter
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

#include "system.h"
#ifdef HAVE_SIGNAL_H
#include <signal.h>
#endif /* HAVE_SIGNAL_H */
#ifdef HAVE_TERMIOS_H
#include <termios.h>
#endif /* HAVE_TERMIOS_H */
#include "readpasswd.h"

struct termios oattr;

/*
 * reset_terminal -- resets interrupts and terminal attributes to whatever
 *                   it was before calling setup_terminal
 */
void reset_terminal() {
  if (!isatty(STDIN_FILENO)) return;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &oattr);
}

/*
 * setup_terminal -- masks interrupts and changes terminal attributes
 */
void setup_terminal() {
  struct termios attr;
  sigset_t set;

  if (!isatty(STDIN_FILENO)) return;

  tcgetattr(STDIN_FILENO, &attr);
  tcgetattr(STDIN_FILENO, &oattr);
  attr.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
  atexit(reset_terminal);
}

/*
 * readpasswd -- reads bufsize-1 chars from stdin or tty
 */
char *readpasswd(const char *prompt, char *buffer, size_t bufsize, bool echo) {
  char c;
  int has_prompt;
  int has_extras = 0;

  has_prompt = ((prompt != NULL) && (strlen(prompt) > 0) ? 1 : 0);
  memset(buffer, 0, bufsize);

  if (!echo) setup_terminal();

  if (has_prompt) {
	fputs(prompt, stdout);
	fflush(stdout);
  }

  if (fgets(buffer, bufsize, stdin) == NULL && ferror(stdin)) {
	err(EXIT_FAILURE, NULL);
  }

  if (buffer[strlen(buffer) - 1] == '\n') {
	buffer[strlen(buffer) - 1] = '\0';
  } else {
	if (((c = getchar()) != '\n') && (c != EOF)) {
	  has_extras = 1;
	}
  }

  if (has_prompt) {
	putchar('\n');
  }

  if (!echo) reset_terminal();

  if (has_extras) {
	errx(EXIT_OVERFLOW, "the password must not contain more than %zu characters", bufsize - 1);
  }

  return buffer;
}
