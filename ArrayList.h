#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "MathFunctions.h"

#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

template <class T>
class ArrayList
{
public:

    typedef typename vector<T>::iterator Iterator;

    typedef typename vector<T>::reverse_iterator ReverseIterator;

    typedef typename vector<T>::const_iterator ConstIterator;

    typedef typename vector<T>::const_reverse_iterator ConstReverseIterator;

    inline ArrayList ( void )
        : m_List(),
          m_Size()
    { }

    inline ArrayList ( const ArrayList& rhs )
        : m_List( rhs.m_List ),
          m_Size( rhs.m_List.size() )
    { }

    virtual inline ~ArrayList( void )
    {
        clear();
    }

    inline ArrayList& operator=( const ArrayList& rhs )
    {
        m_List = rhs.m_List;
        updateSize();
        return *this;
    }

    inline T& at( int index )
    {
        return m_List[index];
    }

    inline const T& at( int index ) const
    {
        return m_List[index];
    }

    inline T& operator[]( const int& index )
    {
        return at( index );
    }

    inline const T& operator[]( const int& index ) const
    {
        return at( index );
    }

    void add( const T& item );

    inline size_t getSize( void ) const
    {
        return m_Size;
    }

    inline bool isEmpty( void ) const
    {
        return ( m_Size == 0 );
    }

    bool contains( const T& item ) const;

    int getIndexOf( const T& item ) const;

    bool hasIndex( const int& index ) const;

    inline T& getFront( void )
    {
        return m_List.front();
    }

    inline T& getBack ( void )
    {
        return m_List.back();
    }

    inline const T& getFront( void ) const
    {
        return m_List.front();
    }

    inline const T& getBack ( void ) const
    {
        return m_List.back();
    }

    T popFront( void );

    T popBack( void );

    void insertAt( const T& item, const int& index );

    inline void resize( unsigned int size, const T& value = T() )
    {
        m_List.resize( size, value );
        updateSize();
    }

    inline void fill( T value, unsigned int amount )
    {
        m_List.assign( amount, value );
        updateSize();
    }

    template <class InputIterator>
    inline void assign( InputIterator first, InputIterator last )
    {
        m_List.assign( first, last );
        updateSize();
    }

    template <class InputIterator>
    inline ArrayList<T>* insert( Iterator pos, InputIterator first, InputIterator last )
    {
        m_List.insert( pos, first, last );
        updateSize();
        return this;
    }

    void clear( void );

    void erase( const Iterator& it );

    bool remove( const T& item );

    bool removeAll( const T& item );

    bool removeAt( const unsigned int& index );

    bool removeFront( void );

    bool removeBack( void );

    inline Iterator itBegin( void )
    {
        return m_List.begin();
    }

    inline Iterator itEnd( void )
    {
        return m_List.end();
    }

    inline ReverseIterator itRevBegin( void )
    {
        return m_List.rbegin();
    }

    inline ReverseIterator itRevEnd( void )
    {
        return m_List.rend();
    }

    inline ConstIterator itConstBegin( void ) const
    {
        return m_List.cbegin();
    }

    inline ConstIterator itConstEnd( void ) const
    {
        return m_List.cend();
    }

    inline ConstReverseIterator itConstRevBegin( void ) const
    {
        return m_List.crbegin();
    }

    inline ConstReverseIterator itConstRevEnd( void ) const
    {
        return m_List.crend();
    }

protected:

    vector<T> m_List;

    size_t m_Size;

    virtual inline void updateSize( void )
    {
        m_Size = m_List.size();
    }

}; // class ArrayList<T>

template <class T>
void ArrayList<T>::add( const T& item )
{
    m_List.push_back( item );
    updateSize();
}

template <class T>
bool ArrayList<T>::contains( const T& item ) const
{
    if ( isEmpty() )
        return false;

    return ( std::find( itConstBegin(), itConstEnd(), item ) != itConstEnd() );
}

template <class T>
int ArrayList<T>::getIndexOf( const T& item ) const
{
    if ( isEmpty() )
        return -1;

    auto it = std::find( itConstBegin(), itConstEnd(), item );

    if ( it == itConstEnd() )
        return -1;

    return it - itConstBegin();
}

template <class T>
bool ArrayList<T>::hasIndex( const int& index ) const
{
    if ( isEmpty() )
        return false;

    return ( Between( index, 0, ( const int )getSize() - 1 ) );
}

template <class T>
void ArrayList<T>::insertAt( const T& item, const int& index )
{
    m_List.insert( m_List.begin() + index, item );
    updateSize();
}

template <class T>
T ArrayList<T>::popFront( void )
{
    T tmp = getFront();
    removeFront();
    return tmp;
}

template <class T>
T ArrayList<T>::popBack( void )
{
    T tmp = getBack();
    removeBack();
    return tmp;
}

template <class T>
bool ArrayList<T>::remove( const T& item )
{
    Iterator it;

    for ( it = itBegin(); it != itEnd(); ++it )
    {
        if ( *it == item )
        {
            m_List.erase( it );
            updateSize();
            return true;
        }
    }

    return false;
}

template <class T>
void ArrayList<T>::erase( const Iterator& it )
{
    m_List.erase( it );
    updateSize();
}

template <class T>
bool ArrayList<T>::removeAll( const T& item )
{
    Iterator it;

    bool found = false;

    for ( it = itBegin(); it != itEnd(); ++it )
    {
        if ( it->second == item )
        {
            m_List.erase( it );
            found = true;
        }
    }

    updateSize();
    return found;
}

template <class T>
bool ArrayList<T>::removeAt( const unsigned int& index )
{
    if ( ! hasIndex( index ) )
        return false;

    m_List.erase( itBegin() + index );
    updateSize();
    return true;
}

template <class T>
bool ArrayList<T>::removeFront( void )
{
    if ( isEmpty() )
        return false;

    removeAt( 0 );
    return true;
}

template <class T>
bool ArrayList<T>::removeBack( void )
{
    if ( isEmpty() )
        return false;

    m_List.pop_back();
    updateSize();
    return true;
}

template <class T>
void ArrayList<T>::clear( void )
{
    m_List.clear();
    updateSize();
}

#endif // ARRAY_LIST_H
