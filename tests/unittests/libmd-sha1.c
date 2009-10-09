#include <system.h>
#include <assert.h>
#include <sha.h>


static char *
SHA1_String(char *string)
{
	static char buf[41];
	char *ptr;
	unsigned char digest[21];
	int i;

	SHA_CTX context;
	SHA1_Init(&context);
	SHA1_Update(&context, string, strlen(string));
	SHA1_Final(digest, &context);

	ptr = buf;
	for (i = 0; i < 20; i++)
	{
		sprintf(ptr, "%02x", digest[i]);
		ptr += 2;
	}
	return buf;
}


int
main(int argc, char *argv[])
{
	assert(strcmp(SHA1_String(""), "da39a3ee5e6b4b0d3255bfef95601890afd80709") == 0);
	assert(strcmp(SHA1_String("abc"), "a9993e364706816aba3e25717850c26c9cd0d89d") == 0);
	assert(strcmp(SHA1_String("message digest"), "c12252ceda8be8994d5fa0290a47231c1d16aae3") == 0);
	assert(strcmp(SHA1_String("abcdefghijklmnopqrstuvwxyz"), "32d10c7b8cf96570ca04ce37f2a19d84240d3a89") == 0);
	assert(strcmp(SHA1_String("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), "761c457bf73b14d27e9e9265c46f4b4dda11f940") == 0);
	assert(strcmp(SHA1_String("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), "50abf5706a150990a08b2c5ea40fa0e585554732") == 0);

	return 0;
}
