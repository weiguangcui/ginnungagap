// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `ginnungagap'.

#ifndef GRIDREGULAR_TESTS_H
#define GRIDREGULAR_TESTS_H


/*--- Includes ----------------------------------------------------------*/
#include "gridConfig.h"
#include <stdbool.h>


/*--- Prototypes of exported functions ----------------------------------*/
extern bool
gridRegular_new_test(void);

extern bool
gridRegular_del_test(void);

extern bool
gridRegular_getName_test(void);

extern bool
gridRegular_attachVar_test(void);

extern bool
gridRegular_detachVar_test(void);

extern bool
gridRegular_getNumPatches_test(void);

extern bool
gridRegular_getPatchHandle_test(void);

extern bool
gridRegular_getOrigin_test(void);

extern bool
gridRegular_getDelta_test(void);

#endif