// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `ginnungagap'.

#ifndef GRIDREGULARFFT_ADT_H
#define GRIDREGULARFFT_ADT_H


/*--- Includes ----------------------------------------------------------*/
#include "gridConfig.h"


/*--- ADT implementation ------------------------------------------------*/
struct gridRegularFFT_struct {
	gridRegular_t        grid;
	gridRegularDistrib_t gridDistrib;
	int                  idxFFTVar;
};


#endif