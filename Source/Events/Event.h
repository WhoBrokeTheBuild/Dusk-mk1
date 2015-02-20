#pragma once

#ifndef DUSK_EVENT_H
#define DUSK_EVENT_H

#include <Arc/ManagedObject.h>

namespace Dusk
{

namespace Events
{

typedef unsigned int EventID;

class IEventDispatcher;

class EventData :
    public Arc::ManagedObject
{
public:

    static const EventData BLANK_EVENT_DATA;

    inline EventData( void ) { }
    inline EventData( const EventData& rhs ) { }

    virtual inline string getClassName( void ) const { return "Event Data"; }

    virtual EventData* clone( void ) const { return New EventData(); };

}; // class EventData

class Event :
    public Arc::ManagedObject
{
public:

    Event( const EventID& eventId, const EventData& data = EventData::BLANK_EVENT_DATA ) :
        m_ID(eventId),
        mp_Data(nullptr),
        mp_EventTarget(nullptr)
    {
        mp_Data = data.clone();
    }

    Event( const Event& rhs ) :
        m_ID(rhs.m_ID),
        mp_Data(nullptr),
        mp_EventTarget(nullptr)
    {
        mp_Data = (rhs.mp_Data == nullptr ? nullptr : rhs.mp_Data->clone() );
    }

    virtual inline ~Event( void )
    {
        delete mp_Data;
    }

    virtual inline string getClassName( void ) const { return "Event"; }

    inline EventID getID( void ) const { return m_ID; }

    inline IEventDispatcher* getTarget( void ) const { return mp_EventTarget; }
    template <typename T>
    inline T* getTargetAs( void ) const { return dynamic_cast<T*>(mp_EventTarget); }

    inline void setTarget( IEventDispatcher* pTarget ) { mp_EventTarget = pTarget; }

    inline EventData* getData( void ) const { return mp_Data; }
    template <typename T>
    inline T* getDataAs( void ) const { return dynamic_cast<T*>(mp_Data); }

protected:

    EventID             m_ID;
    EventData*          mp_Data;
    IEventDispatcher*   mp_EventTarget;

}; // class Event

} // namespace Events

} // namespace Dusk

#endif // DUSK_EVENT_H
