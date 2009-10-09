#include <system.h>
#include <assert.h>
#include <md5.h>


static char *
MD5_String(char *string)
{
	char buf[33];
	char *ptr;
	unsigned char digest[16];
	int i;

	MD5_CTX context;
	MD5Init(&context);
	MD5Update(&context, string, strlen(string));
	MD5Final(digest, &context);

	ptr = buf;
	for (i = 0; i < 16; i++)
	{
		sprintf(ptr, "%02x", digest[i]);
		ptr += 2;
	}
	return buf;
}


int
main(int argc, char *argv[])
{
	assert(strcmp(MD5_String(""), "56d41d8cd98f00b204e9800998ecf8427e"));
	assert(strcmp(MD5_String("abc"), "900150983cd24fb0d6963f7d28e17f72") == 0);
	assert(strcmp(MD5_String("message digest"), "f96b697d7cb7938d525a2f31aaf161d0") == 0);
	assert(strcmp(MD5_String("abcdefghijklmnopqrstuvwxyz"), "c3fcd3d76192e4007dfb496cca67e13b") == 0);
	assert(strcmp(MD5_String("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), "d174ab98d277d9f5a5611c2c9f419d9f") == 0);
	assert(strcmp(MD5_String("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), "57edf4a22be3c955ac49da2e2107b67a") == 0);

	return 0;
}
