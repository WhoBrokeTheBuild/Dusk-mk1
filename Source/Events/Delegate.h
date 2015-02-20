#pragma once

#ifndef DUSK_DELEGATE_H
#define DUSK_DELEGATE_H

#include <Arc/ManagedObject.h>

#include <Events/Callbacks.h>

namespace Dusk
{

namespace Events
{

template <typename ReturnType, typename Param = void>
class Delegate :
    public Arc::ManagedObject
{
public:

    Delegate( ReturnType (*pFunction)(Param) )
    {
        mp_Callback = New FunctionCallback<ReturnType, Param>(pFunction);
    }

    template <typename ObjectType, typename Method>
    Delegate( ObjectType* pObject, Method method )
    {
        mp_Callback = New MethodCallback<ReturnType, Param, ObjectType, Method>(pObject, method);
    }

    Delegate( const Delegate<ReturnType, Param>& rhs )
    {
        mp_Callback = rhs.mp_Callback->clone();
    }

    virtual inline ~Delegate( void ) { delete mp_Callback; mp_Callback = nullptr; }

    virtual inline string getClassName( void ) const { return "Delegate"; }

    inline ReturnType invoke( Param param ) { return mp_Callback->invoke(param); }
    inline ReturnType operator()( Param param ) { return invoke(param); }

    inline bool isMethodOf( void* pObject )
    {
        if (!mp_Callback) return false;
        return mp_Callback->isMethodOf(pObject);
    }

    bool operator==( const Delegate<ReturnType, Param>& rhs )
    {
        if (!mp_Callback || !rhs.mp_Callback)
            return false;

        if (mp_Callback == rhs.mp_Callback)
            return true;

        return ( *(mp_Callback) == *(rhs.mp_Callback) );
    }

    bool operator!=( const Delegate<ReturnType, Param>& rhs ) { return !((*this) == rhs); }

private:

    Callback<ReturnType, Param>*    mp_Callback;


}; // class Delegate

} // namespace Events

} // namespace Dusk

#endif // DUSK_DELEGATE_H
