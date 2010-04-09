// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `ginnungagap'.


/*--- Includes ----------------------------------------------------------*/
#include "gridConfig.h"
#include "gridPatch.h"
#include "gridPoint.h"
#include <assert.h>
#include <stdint.h>
#include "../libutil/xmem.h"
#include "../libutil/varArr.h"


/*--- Implemention of main structure ------------------------------------*/
#include "gridPatch_adt.h"


/*--- Local defines -----------------------------------------------------*/


/*--- Prototypes of local functions -------------------------------------*/


/*--- Implementations of exported functios ------------------------------*/
extern gridPatch_t
gridPatch_new(gridPointUint32_t idxLo, gridPointUint32_t idxHi)
{
	gridPatch_t gridPatch;

	for (int i = 0; i < NDIM; i++) {
		assert(idxLo[i] <= idxHi[i]);
	}

	gridPatch           = xmalloc(sizeof(struct gridPatch_struct));
	gridPatch->numCells = UINT64_C(1);
	for (int i = 0; i < NDIM; i++) {
		gridPatch->idxLo[i]  = idxLo[i];
		gridPatch->dims[i]   = idxHi[i] - idxLo[i] + 1;
		gridPatch->numCells *= gridPatch->dims[i];
	}
	gridPatch->vars = varArr_new(0);
	gridPatch->varData = varArr_new(0);

	return gridPatch;
}

extern void
gridPatch_del(gridPatch_t *gridPatch)
{
	int numVarData;
	gridVar_t var;

	assert(gridPatch != NULL && *gridPatch != NULL);

	numVarData = varArr_getLength((*gridPatch)->varData);
	for (int i = 0; i < numVarData; i++) {
		var = varArr_remove((*gridPatch)->vars, 0);
		gridVar_freeMemory(var, varArr_remove((*gridPatch)->varData, 0));
		gridVar_del(&var);
	}
	varArr_del(&((*gridPatch)->varData));
	varArr_del(&((*gridPatch)->vars));
	xfree(*gridPatch);

	*gridPatch = NULL;
}

extern uint32_t
gridPatch_getOneDim(gridPatch_t patch, int idxOfDim)
{
	assert(patch != NULL);
	assert(idxOfDim >= 0 && idxOfDim < NDIM);

	return patch->dims[idxOfDim];
}

extern uint64_t
gridPatch_getNumCells(gridPatch_t patch)
{
	assert(patch != NULL);

	return patch->numCells;
}

extern void
gridPatch_getIdxLo(gridPatch_t patch, gridPointUint32_t idxLo)
{
	assert(patch != NULL);

	for (int i = 0; i < NDIM; i++)
		idxLo[i] = patch->idxLo[i];
}

extern int
gridPatch_attachVarData(gridPatch_t patch, gridVar_t var)
{
	void *data;
	gridVar_t varClone;
	int posVar, posVarData;

	assert(patch != NULL);
	assert(var != NULL);

	varClone = gridVar_getRef(var);
	data = gridVar_getMemory(varClone, patch->numCells);

	posVar = varArr_insert(patch->vars, varClone);
	posVarData = varArr_insert(patch->varData, data);

	assert(posVar == posVarData);

	return posVar;
}

extern void *
gridPatch_detachVarData(gridPatch_t patch, int idxOfVarData)
{
	gridVar_t tmp;

	assert(idxOfVarData >= 0
	       && idxOfVarData < varArr_getLength(patch->varData));

	tmp = varArr_remove(patch->vars, idxOfVarData);
	gridVar_del(&tmp);

	return varArr_remove(patch->varData, idxOfVarData);
}

extern gridVar_t
gridPatch_getVarHandle(gridPatch_t patch, int idxOfVar)
{
	assert(idxOfVar >= 0 && idxOfVar < varArr_getLength(patch->vars));

	return varArr_getElementHandle(patch->vars, idxOfVar);
}

extern void *
gridPatch_getVarDataHandle(gridPatch_t patch, int idxOfVarData)
{
	assert(idxOfVarData >= 0
	       && idxOfVarData < varArr_getLength(patch->varData));

	return varArr_getElementHandle(patch->varData, idxOfVarData);
}

extern int
gridPatch_getNumVars(gridPatch_t patch)
{
	assert(patch != NULL);

	return varArr_getLength(patch->vars);
}

/*--- Implementations of local functions --------------------------------*/
