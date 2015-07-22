#include "SortedIntegerArray.h"

SortedIntegerArray::SortedIntegerArray(int size)
{
    m_integreBuffer = NULL;
    m_size = 0;
    m_integreBuffer = new INTEGER_TYPE[size];
    *(m_integreBuffer+m_size) = 50;
    ++m_size;
}

SortedIntegerArray::~SortedIntegerArray()
{
    if(m_integreBuffer)
        delete m_integreBuffer;
}

bool SortedIntegerArray::insertValue(INTEGER_TYPE value)
{
    INTEGER_TYPE* loc = binarySearch(value,0,m_size);

    if(loc == NULL)
    {
        fprintf(stderr,"Its Null\n");
        //        return false;
    }
    else
    {

        printf("Location: %u:> %d", loc,*loc );
    }
    //    memmove();
    ++m_size;
    return true;
}

bool SortedIntegerArray::deleteValue(INTEGER_TYPE value)
{
    return true;
}

INTEGER_TYPE* SortedIntegerArray::searchValue(INTEGER_TYPE key)
{
    return binarySearch(key,0,m_size);
}

INTEGER_TYPE* SortedIntegerArray::binarySearch(INTEGER_TYPE &key,INTEGER_TYPE imin,INTEGER_TYPE imax)
{

    for(INTEGER_TYPE* i= m_integreBuffer; i < m_integreBuffer+imax; ++i)
    {
        if(key < *i)
        {
            fprintf(stderr,"%d\n",*i);

            return i;
        }
    }

    return NULL;
#if 0
    if(imax < imin)
    {
        fprintf(stderr,"imax < imin\n");
        return NULL;
    }
    else
    {
        fprintf(stderr,"imax < imin  - Fails\n");

        int imid = (imin +imax) / 2;
        fprintf(stderr,"Mid Value %d\n",*(m_integreBuffer+imid));

        if(*(m_integreBuffer+imid) > key)
            return binarySearch(key,imin,imid-1);
        else if(*(m_integreBuffer+imid) < key)
            return binarySearch(key,imid+1,imax);
        else
            return (m_integreBuffer+imid);
    }
#endif
}
