/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
 */

/* $Id: fileio.h 277 2008-12-14 00:23:50Z david $ */

#ifndef _FILEIO_H
#define _FILEIO_H 1
#include "system.h"

#define delete_from_file(x,y,z) update_file(x,y,z,NULL)
void create_file(char*, char*, char*, char*);
void update_file(char*, char*, char*, char*);

#endif /* !_FILEIO_H */
