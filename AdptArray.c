#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;




PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_;
	return pArr;
}


Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		
// Extend Array
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem
	if ((pArr->pElemArr)[idx]!=NULL){
	pArr->delFunc((pArr->pElemArr)[idx]);
	}
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if ((pArr->pElemArr)[i]!=NULL)
		{
		pArr->delFunc((pArr->pElemArr)[i]);
	}
	}
	free(pArr->pElemArr);
	free(pArr);
}
 

PElement GetAdptArrayAt(PAdptArray pArr, int idx){
	if (pArr == NULL||pArr->pElemArr[idx] == NULL|| idx<0|| idx >= pArr->ArrSize)
		return NULL;
	return pArr->copyFunc((pArr->pElemArr)[idx]);
}

int GetAdptArraySize(PAdptArray pArr){
	return (pArr != NULL)? pArr->ArrSize : -1;
};

void PrintDB(PAdptArray pArr){
	if (pArr ==NULL ||  pArr->pElemArr == NULL) return;
	int idx;
	for(idx = 0; idx < pArr->ArrSize; ++idx)
	{
		PElement elem = pArr->pElemArr[idx];
		if(elem != NULL) pArr->printFunc(elem);
	}
}
;
// In this file I used the formal answer of exam which published last semester  
