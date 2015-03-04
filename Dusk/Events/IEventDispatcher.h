#ifndef DUSK_EVENT_DISPATCHER_H
#define DUSK_EVENT_DISPATCHER_H

#include <Events/Event.h>
#include <Events/Delegate.h>

#include <Arc/ArrayList.h>
#include <Arc/Map.h>

using Arc::ArrayList;
using Arc::Map;

namespace Dusk
{

namespace Events
{

typedef Delegate<void, const Event&> EventDelegate;

class IEventDispatcher
{
public:

    IEventDispatcher( void );
    virtual ~IEventDispatcher( void );

    void addEventListener   ( const EventID& eventId, const EventDelegate& funcDelegate );
    void removeEventListener( const EventID& eventId, const EventDelegate& funcDelegate );

    void addEventListener   ( const EventID& eventId, void (*pFunction)(const Event&) );
    void removeEventListener( const EventID& eventId, void (*pFunction)(const Event&) );

    template <typename ObjectType, typename Method>
    void addEventListener   ( const EventID& eventId, ObjectType* pObject, Method method );
    template <typename ObjectType, typename Method>
    void removeEventListener( const EventID& eventId, ObjectType* pObject, Method method );

    template <typename ObjectType>
    void removeAllMethods( ObjectType* pObject );

    void removeAllListeners( void );
    void removeAllListeners( const EventID& eventId );

    void dispatch( const Event& event );

    static void cleanEvents( void )
    {
        int length = s_Dispatchers.getSize();
        for (int i = 0; i < length; ++i)
            s_Dispatchers[i]->cleanMap();
    }

private:

    void cleanMap( void );
    virtual inline void noop( void ) { }

    static ArrayList<IEventDispatcher*>         s_Dispatchers;
    Map<EventID, ArrayList<EventDelegate*>>     m_EventMap;

    bool    m_Changed;


}; // class EventDispatcher

template <typename ObjectType, typename Method>
void IEventDispatcher::addEventListener( const EventID& eventId, ObjectType* object, Method method )
{
    addEventListener(eventId, EventDelegate(object, method));
}

template <typename ObjectType, typename Method>
void IEventDispatcher::removeEventListener( const EventID& eventId, ObjectType* object, Method method )
{
    removeEventListener(eventId, EventDelegate(object, method));
}

template <typename ObjectType>
void IEventDispatcher::removeAllMethods( ObjectType* object )
{
    bool needRepeat = true;
    Map<EventID, ArrayList<EventDelegate*>>::Iterator mapIt;
    ArrayList<EventDelegate*>::Iterator listIt;

    while(needRepeat)
    {
        needRepeat = false;
        for(mapIt = m_EventMap.itBegin(); !needRepeat && mapIt != m_EventMap.itEnd(); ++mapIt)
        {
            for(listIt = mapIt->second.itBegin(); !needRepeat && listIt != mapIt->second.itEnd(); ++listIt)
            {
                if ( *listIt == nullptr )
                    continue;

                if ( (*listIt)->isMethodOf(object) )
                {
                    (*listIt) = nullptr;
                    needRepeat = true;
                    break;
                }
            }
        }
    }
}


} // namespace Events

} // namespace Dusk

#endif // DUSK_EVENT_DISPATCHER_H
