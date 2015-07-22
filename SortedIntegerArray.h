#ifndef SORTEDINTEGERARRAY_H
#define SORTEDINTEGERARRAY_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INTEGER_TYPE int

class SortedIntegerArray
{
    INTEGER_TYPE* m_integreBuffer;
    int m_size;
public:
    SortedIntegerArray(int size);
    ~SortedIntegerArray();

    bool insertValue(INTEGER_TYPE value);
    bool deleteValue(INTEGER_TYPE value);
    INTEGER_TYPE* searchValue(INTEGER_TYPE value);
    INTEGER_TYPE* binarySearch(INTEGER_TYPE &key,INTEGER_TYPE imin,INTEGER_TYPE imax);

};

#endif // SORTEDINTEGERARRAY_H
