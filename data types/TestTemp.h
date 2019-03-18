// TestTemp.h
#ifndef _TESTTEMP_H_
#define _TESTTEMP_H_
template<class T>
class TestTemp
{
public:
    TestTemp();
    void SetValue( T obj_i );
    T Getalue();
private:
    T m_Obj;
};
#include "TestTemp.cpp"

#endif
