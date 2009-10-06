/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
 */
 
/* $Id: basic-auth.h 278 2008-12-15 09:16:04Z david $ */

#ifndef _BASIC_AUTH_H
#define _BASIC_AUTH_H 1
char *basic_sha1(char*, char*, char*, char*);
char *basic_crypt(char*, char*, char*, char*);
char *basic_apr1(char*, char*, char*, char*);
#endif /* !_BASIC_AUTH_H */
