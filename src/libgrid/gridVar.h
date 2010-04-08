// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `ginnungagap'.

#ifndef GRIDVAR_H
#define GRIDVAR_H


/*--- Includes ----------------------------------------------------------*/
#include "gridConfig.h"
#include "gridVarType.h"
#include <stdlib.h>
#include <stdint.h>


/*--- ADT handle --------------------------------------------------------*/
typedef struct gridVar_struct *gridVar_t;


/*--- Prototypes of exported functions ----------------------------------*/
extern gridVar_t
gridVar_new(const char *name, gridVarType_t type, int numComponents);

extern void
gridVar_del(gridVar_t *var);

extern gridVar_t
gridVar_getRef(gridVar_t var);

extern size_t
gridVar_getSizePerElement(gridVar_t var);

extern int
gridVar_getNumComponents(gridVar_t var);

extern gridVarType_t
gridVar_getType(gridVar_t var);

extern char *
gridVar_getName(gridVar_t var);

extern void *
gridVar_getMemory(gridVar_t var, uint64_t numElements);

extern void
gridVar_freeMemory(gridVar_t var, void *data);


#endif
