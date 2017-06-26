#include "fct.h"
#include <libmd/md5.h>
#include <libmd/sha.h>

static char * MD5_String(char *string) {
	static char buf[33];
	char *ptr;
	unsigned char digest[16];
	int i;

	MD5_CTX context;
	MD5Init(&context);
	MD5Update(&context, (const unsigned char *) string, strlen(string));
	MD5Final(digest, &context);

	ptr = buf;
	for (i = 0; i < 16; i++) {
		sprintf(ptr, "%02x", digest[i]);
		ptr += 2;
	}
	return buf;
}

static char * SHA1_String(char *string) {
	static char buf[41];
	char *ptr;
	unsigned char digest[21];
	int i;

	SHA_CTX context;
	SHA1_Init(&context);
	SHA1_Update(&context, (const unsigned char *) string, strlen(string));
	SHA1_Final(digest, &context);

	ptr = buf;
	for (i = 0; i < 20; i++) {
		sprintf(ptr, "%02x", digest[i]);
		ptr += 2;
	}
	return buf;
}


FCT_BGN() {
	FCT_QTEST_BGN(libmd__md5) {
		fct_chk_eq_str(MD5_String(""), "d41d8cd98f00b204e9800998ecf8427e");
		fct_chk_eq_str(MD5_String("abc"), "900150983cd24fb0d6963f7d28e17f72");
		fct_chk_eq_str(MD5_String("message digest"), "f96b697d7cb7938d525a2f31aaf161d0");
		fct_chk_eq_str(MD5_String("abcdefghijklmnopqrstuvwxyz"), "c3fcd3d76192e4007dfb496cca67e13b");
		fct_chk_eq_str(MD5_String("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), "d174ab98d277d9f5a5611c2c9f419d9f");
		fct_chk_eq_str(MD5_String("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), "57edf4a22be3c955ac49da2e2107b67a");
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(libmd__sha1) {
		fct_chk_eq_str(SHA1_String(""), "da39a3ee5e6b4b0d3255bfef95601890afd80709");
		fct_chk_eq_str(SHA1_String("abc"), "a9993e364706816aba3e25717850c26c9cd0d89d");
		fct_chk_eq_str(SHA1_String("message digest"), "c12252ceda8be8994d5fa0290a47231c1d16aae3");
		fct_chk_eq_str(SHA1_String("abcdefghijklmnopqrstuvwxyz"), "32d10c7b8cf96570ca04ce37f2a19d84240d3a89");
		fct_chk_eq_str(SHA1_String("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), "761c457bf73b14d27e9e9265c46f4b4dda11f940");
		fct_chk_eq_str(SHA1_String("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), "50abf5706a150990a08b2c5ea40fa0e585554732");
	}
	FCT_QTEST_END();
}
FCT_END();
