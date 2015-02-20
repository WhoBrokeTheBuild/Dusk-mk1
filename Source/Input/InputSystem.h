#pragma once

#ifndef DUSK_INPUT_SYSTEM_H
#define DUSK_INPUT_SYSTEM_H

#include <Arc/ManagedObject.h>
#include <Events/IEventDispatcher.h>

using namespace Dusk::Events;

namespace Dusk
{

namespace Input
{

class InputSystem :
    public Arc::ManagedObject,
    public IEventDispatcher
{
public:

    InputSystem( void );

    virtual inline string getClassName( void ) const { return "Input System"; }

    void handleKeyUp      ( const Event& event );
    void handleKeyDown    ( const Event& event );
    void handleMouseUp    ( const Event& event );
    void handleMouseDown  ( const Event& event );
    void handleMouseMove  ( const Event& event );
    void handleMouseScroll( const Event& event );


private:


}; // class InputSystem

} // namespace Input

} // namespace Dusk

#endif // DUSK_INPUT_SYSTEM_H
