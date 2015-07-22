#ifndef CALLBACKCLASS_H
#define CALLBACKCLASS_H
#include <stdlib.h>

class CallBackClass
{
public:
    CallBackClass();
    virtual void CallBack(void* a1=NULL,void* a2=NULL);
};

#endif // CALLBACKCLASS_H
