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

/* $Id$ */

/*
 * version -- combines svnversion and 'svn info' into a compact representation
 *            of working copy revision and repository path so almost every
 *            possible version of htpmt can be reconstructed from --version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int eq(char *a, char *b)
{
	int x;

	x = strcmp(a, b);

	switch (x)
	{
		case 0:
			return 1;
			break;
		default:
			return 0;
	}
}

void usage()
{
	fprintf(stderr, "Usage: version WCPATH");
	exit(1);
}

int main(int argc, char *argv[])
{
	FILE *pipe;
	char cmd[1024];
	char version[1024];
	char buf[1024];
	char url[1024];
	char *ptr, *path1, *path2, *path3;

	if (argc != 2)
	{
		usage();
	}
	sprintf(cmd, "svnversion -n %s", argv[1]);

	pipe = popen(cmd, "r");
	fscanf(pipe, "%s", version);
	pclose(pipe);

	sprintf(cmd, "svn info %s", argv[1]);
	pipe = popen(cmd, "r");

	while (fgets(buf, sizeof(buf), pipe) != NULL)
	{
		ptr = strtok(buf, ": ");

		if (ptr != NULL && eq(ptr, "URL"))
		{
			ptr = strtok(NULL, " ");
			strcpy(url, ptr);
			ptr = strrchr(url, '\n');
			*ptr = '\0';
			
		}
	}

	pclose(pipe);

	if (!eq(version, "exported"))
	{
		path1 = strrchr(url, '/');
		*path1 = '\0';
		path1++;
		path2 = strrchr(url, '/');
		*path2 = '\0';
		path2++;
		path3 = strrchr(url, '/');
		*path3 = '\0';
		path3++;
		printf("#define SVN_VERSION \"%s\"\n", version);
		printf("#define SVN_URL \"%s/%s/%s/%s\"\n", url, path3, path2, path1);

		if (eq(path1, "trunk"))
		{
			printf("#define REVISION \"r%s\"\n", version);
			printf("#undef VERSION\n");
		}
		else if(eq(path3, "branches") && eq(path2, "releases"))
		{
			printf("#define REVISION \"releases/%s@r%s\"\n", path1, version);
			printf("#undef VERSION\n");
		}
		else if(eq(path3, "branches") && eq(path2, "features"))
		{
			printf("#define REVISION \"branches/%s@r%s\"\n", path1, version);
			printf("#undef VERSION\n");
		}
		else if(eq(path3, "tags") && eq(path2, "releases"))
		{
			printf("#define REVISION \"releases/%s@r%s\"\n", path1, version);
		}
	}
	else
	{
		return 1;
	}
	return 0;
}
