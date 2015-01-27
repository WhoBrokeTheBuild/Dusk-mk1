#ifndef DUSK_TEXTURE_H
#define DUSK_TEXTURE_H

#include <Arc/ManagedObject.h>
#include <Graphics/Graphics.h>

namespace Dusk
{

namespace Graphics
{

class Texture :
    public Arc::ManagedObject
{
public:

    inline Texture( void ) :
        m_Texture(0)
    { }

    virtual ~Texture( void );

	virtual inline string getClassName( void ) const { return "Texture"; }

    bool load( const string& filename );
    void bind( void );

private:

    GLTexture   m_Texture;

}; // class Texture

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_TEXTURE_H
