#ifndef PROJECTTITLE_DESIGNBYCONTRACT_H
#define PROJECTTITLE_DESIGNBYCONTRACT_H
//============================================================================
// Name        : DesignByContract.h
// Author      : Serge Demeyer, modified by Kasper Engelen
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : Declarations for design by contract in C++, compatible with Windows-based C++ buildsystems
//============================================================================

#include <assert.h>

#define REQUIRE(assertion, what) \
	if (!(assertion)) _assert (what, __FILE__, __LINE__)

#define ENSURE(assertion, what) \
	if (!(assertion)) _assert (what, __FILE__, __LINE__)
#endif //PROJECTTITLE_DESIGNBYCONTRACT_H
