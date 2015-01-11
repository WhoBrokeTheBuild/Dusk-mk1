#ifndef MAP_H
#define MAP_H

#include <map>

using std::less;
using std::map;
using std::pair;

template <class T>
class ArrayList;

template <class K, class T, typename Sort = less<K> >
class Map
{
protected:

    map<K, T, Sort> m_Map;

    size_t m_Size;

    virtual inline void updateSize( void )
    {
        m_Size = m_Map.size();
    }

public:

    typedef typename map<K, T>::iterator Iterator;

    typedef typename map<K, T>::reverse_iterator ReverseIterator;

    typedef typename map<K, T>::const_iterator ConstIterator;

    typedef typename map<K, T>::const_reverse_iterator ConstReverseIterator;

    typedef pair<K, T> Pair;

    inline Map( void )
        : m_Map(),
          m_Size()
    { }

    inline Map( const Map& rhs )
        : m_Map( rhs.m_Map ),
          m_Size( rhs.m_Map.size() )
    { }

    virtual inline ~Map( void )
    {
        clear();
    }

    inline Map& operator= ( const Map& rhs )
    {
        m_Map = rhs.m_Map;
        updateSize();
        return *this;
    }

    inline T& operator[]( const K& key )
    {
        return at( key );
    }

    inline T& operator[]( const K& key ) const
    {
        return at( key );
    }

    inline Iterator itBegin( void )
    {
        return m_Map.begin();
    }

    inline Iterator itEnd( void )
    {
        return m_Map.end();
    }

    inline ReverseIterator itRevBegin( void )
    {
        return m_Map.rbegin();
    }

    inline ReverseIterator itRevEnd( void )
    {
        return m_Map.rend();
    }

    inline ConstIterator itConstBegin( void ) const
    {
        return m_Map.cbegin();
    }

    inline ConstIterator itConstEnd( void ) const
    {
        return m_Map.cend();
    }

    inline ConstReverseIterator itConstRevBegin( void ) const
    {
        return m_Map.crbegin();
    }

    inline ConstReverseIterator itConstRevEnd( void ) const
    {
        return m_Map.crend();
    }

    inline Iterator find( const K& key )
    {
        return m_Map.find( key );
    }

    inline ConstIterator find ( const K& key ) const
    {
        return m_Map.find( key );
    }

    void add( const K& key, const T& item );

    void clear( void );

    // Remove element with the given key
    bool removeKey( const K& key );

    // Remove the first element with the given value
    bool removeFirstValue( const T& value );

    // Remove all elements with the given value
    bool removeAllValues ( const T& value );

    inline Iterator erase( const Iterator& it )
    {
        Iterator ret = m_Map.erase( it );
        updateSize();
        return ret;
    }

    inline T& at( const K& key )
    {
        return m_Map[key];
    }

    inline T& at( const K& key ) const
    {
        return m_Map[key];
    }

    bool containsKey( const K& key ) const;

    bool containsValue( const T& value ) const;

    inline bool isEmpty( void ) const
    {
        return ( m_Size == 0 );
    }

    // Get the index of a value
    K getIndexOf( T& item ) const;

    inline size_t getSize( void ) const
    {
        return m_Size;
    }

    ArrayList<K> getKeys( void ) const;

    ArrayList<T> getValues( void ) const;

    inline void insert( Iterator& first, Iterator& last )
    {
        m_Map.insert( first, last );
    }

    inline void insert( ConstIterator& first, ConstIterator& last ) const
    {
        m_Map.insert( first, last );
    }

}; // class Map<T, K, Sort>

#include "ArrayList.h"

template <class K, class T, typename Sort>
void Map<K, T, Sort>::add( const K& key, const T& item )
{
    m_Map.insert( Pair( key, item ) );
    updateSize();
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::removeKey( const K& key )
{
    bool removed = ( m_Map.erase( key ) == 1 );
    updateSize();
    return removed;
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::removeFirstValue( const T& value )
{
    for ( auto it = itBegin(); it != itEnd(); ++it )
    {
        if ( it->second == value )
        {
            m_Map.erase( it );
            updateSize();
            return true;
        }
    }

    return false;
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::removeAllValues( const T& value )
{
    bool found = false;

    for ( auto it = itBegin(); it != itEnd(); ++it )
    {
        if ( it->second == value )
        {
            m_Map.erase( it );
            found = true;
        }
    }

    updateSize();
    return found;
}

template <class K, class T, typename Sort>
void Map<K, T, Sort>::clear( void )
{
    m_Map.clear();
    updateSize();
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::containsKey( const K& key ) const
{
    return (m_Map.count(key) > 0);
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::containsValue( const T& value ) const
{
    for ( auto it = itConstBegin(); it != itConstEnd(); ++it )
    {
        if ( it->second == value )
            return true;
    }

    return false;
}

template <class K, class T, typename Sort>
K Map<K, T, Sort>::getIndexOf( T& item ) const
{
    for ( auto it = itConstBegin(); it != itConstEnd(); ++it )
    {
        if ( it->second == item )
            return it->first;
    }

    return K();
}

template <class K, class T, typename Sort>
ArrayList<K> Map<K, T, Sort>::getKeys( void ) const
{
    ArrayList<K> keys;

    for ( auto it = itConstBegin(); it != itConstEnd(); ++it )
        keys.add( it->first );

    return keys;
}

template <class K, class T, typename Sort>
ArrayList<T> Map<K, T, Sort>::getValues( void ) const
{
    ArrayList<T> values;

    for ( auto it = itConstBegin(); it != itConstEnd(); ++it )
        values.add( it->second );

    return values;
}

#endif // MAP_H
