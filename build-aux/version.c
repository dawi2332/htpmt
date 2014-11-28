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

/* $Id$ */

/*
 * version.c:
 * Uses `git describe' to generate a version number from git
 * tags or branches.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include <config.h>

int eq(char *a, char *b)
{
	return strcmp(a, b) == 0;
}

int main(int argc, char *argv[])
{
	FILE *pipe;
	char version[1024];
	char complete_info[1024];
	char *ptr, *path1, *path2, *path3;

	pipe = popen("git describe --always --tags", "r");
	fscanf(pipe, "%s", version);
	pclose(pipe);

	pipe = popen("git describe --always --all --long --dirty", "r");
	fscanf(pipe, "%s", complete_info);
	pclose(pipe);

	printf("#define GIT_VERSION \"%s\"\n", complete_info);
	printf("#define REVISION \"%s\"\n", version);

	char *wrk = strdup(complete_info);

	path1 = strsep(&wrk, "/");
	path2 = strsep(&wrk, "/");
	if (path2 != NULL) {
		path3 = strsep(&wrk, "/");
	}

	printf("#define VERSION_LONG \"");

	if (eq(path1, "tags")) {
		printf("%s (%s)\"\n", version, complete_info);
	} else {
		printf("%s-g%s (%s)\"\n", VERSION, version, complete_info);
	}
	return 0;
}
