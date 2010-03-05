#include <system.h>

extern char *program_name;

void syntax(char * s)
{
	warnx(s);
	printf("Try `%s --help' for more information.\n", program_name);
	exit(EXIT_SYNTAXERROR);
}
