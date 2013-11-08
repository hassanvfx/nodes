//
//  FX3Dictionary.h
//  FX3C
//
//  Created by Brent Rabowsky on 8/7/12.


#ifndef FX3C_FX3Dictionary_h
#define FX3C_FX3Dictionary_h





#include "FX3.h"



#define FX3_FX3DICTIONARY_SIZE 31


//static const char * LOG_TAG = "FX3Dictionary";


typedef enum 
{
    FX_KEYTYPE_CHARPTR,
    FX_KEYTYPE_INT
    
} FXKeyType;



template <class KeyType, class ValueType>
class FX3TableEntry
{
public:
    
	KeyType key;
	ValueType value;
	FX3TableEntry<KeyType,ValueType> * next;
    
	FX3TableEntry( KeyType k, ValueType v ): key( k ), value( v ), next( NULL ) {}
};


template <class KeyType, class ValueType>
class FX3Dictionary {
    
private:
    
    int _size;
    FX3TableEntry<KeyType,ValueType> ** _table;
    FXKeyType _keyType;
    int _numEntries;
    
public:
    
    ~FX3Dictionary()
    {
        delete [] _table;
    }
    
    
    FX3Dictionary( FXKeyType keyType ) 
    {
        _numEntries = 0;
        _keyType = keyType;
        _size = FX3_FX3DICTIONARY_SIZE;
        _table = new FX3TableEntry<KeyType,ValueType>*[_size];
        
        for ( int i = 0; i < _size; ++i )
            _table[i] = NULL;
    }
    
    
    ValueType lookup( KeyType k ) 
    {
        
        int hash = hashMethod( k );
        if ( !_table[hash] )
            return NULL;
        
        FX3TableEntry<KeyType,ValueType> * entry = _table[hash];
        while ( entry ) {
            if ( isEqual( entry->key, k )  )
                return entry->value;
            entry = entry->next;
        }
        
        return NULL;
    }



    void releaseAll()
    {
		 for (int i = 0; i < _size; ++i) {
            if ( _table[i] == NULL ) {
                continue;
            }
            else {
            
                FX3TableEntry<KeyType,ValueType> * iter = _table[i];
                while ( iter ) {
                
                	if ( iter->value != NULL ) {
                			delete iter->value;
                    }
                    
                    iter = iter->next;
                    
                } // end while
                
            } // end else
            
        } // end for
    }


    bool replace( KeyType k, ValueType  v ) 
    {
        
    	 remove(k);
    	 insert( k, v );
    	 return true;
    	 /*
        int hash = hashMethod( k );
        



        // if not in table, just insert it
        if ( !_table[hash] ) {
        		insert( k, v );
            return true;
        }
        
        // if in table, delete old value of entry and replace it
        FX3TableEntry<KeyType,ValueType> * entry = _table[hash];
        while ( entry ) {
            if ( isEqual( entry->key, k )  ) {
            	delete entry->value;
            	entry->value = v;
                return true;
            }
            entry = entry->next;
        }
        
        return false;
        */
    }
    
    
    bool insert( KeyType k, ValueType  v )
    {
        // if already in table, don't re-insert
        if ( lookup( k ) )
            return true;
        
        int hash = hashMethod( k );
        
        if ( !_table[hash] ) {
            _table[hash] = new FX3TableEntry<KeyType,ValueType>( k, v );
            ++_numEntries;
            return true;
        }
        else {
            FX3TableEntry<KeyType,ValueType> * entry = new FX3TableEntry<KeyType,ValueType>( k, v );
            entry->next = _table[hash];
            _table[hash] = entry;
            ++_numEntries;
            return true;
        }
        
        return false;
    }
    
    
    bool remove( KeyType k )
    {
        int hash = hashMethod( k );
        
        // not in table?
        if ( !lookup( k ) ) {
            return true;
        }
        
        FX3TableEntry<KeyType,ValueType> * entry = _table[hash];
        // check if first node must be removed
        if ( isEqual( entry->key, k ) ) {
            if ( entry->next == NULL ) {
                _table[hash] = NULL;
                --_numEntries;
                return true;
            }
            else {
                _table[hash] = entry->next;
                --_numEntries;
                return true;
            }
        }
        // first node didn't have the key, so continue
        FX3TableEntry<KeyType,ValueType> * prev = entry;
        FX3TableEntry<KeyType,ValueType> * iter = entry->next;
        while ( iter ) {
            if ( isEqual( entry->key, k ) ) {
                // case 1:  this node is the last in chain
                if ( iter->next == NULL) {
                    prev->next = NULL;
                    --_numEntries;
                    return true;
                }
                // case 2:  this node is between two nodes
                else {
                    prev->next = iter->next;
                    --_numEntries;
                    return true;
                }
            }
            
            iter = iter->next;
            prev = prev->next;
        }
        
        return false;
    }
    
    
    bool isEqual( KeyType k1, KeyType k2 )
    {
        switch ( _keyType ) {
                
            case FX_KEYTYPE_CHARPTR:
                if ( strcmp( (char*)k1, (char*)k2 ) == 0 )
                    return true;
                break;  
                
            case FX_KEYTYPE_INT:
                if ( k1 == k2 )
                    return true;
                break;
        }
        
        return false;
        
    }
    
    
    FX3TableEntry<KeyType, ValueType> ** getEntries()
    {
        FX3TableEntry<KeyType, ValueType> ** entries = new FX3TableEntry<KeyType,ValueType>*[_numEntries];
        
        int i = 0;
        int k = 0;
        while ( i < _size ) {
            if ( _table[i] == NULL ) {
                ++i;
                continue;
            }
            else {
                FX3TableEntry<KeyType,ValueType> * iter = _table[i];
                while ( iter ) {
                    entries[k] = iter;
                    ++k;
                    iter = iter->next;
                } // end inner while
                
            }
            
            ++i;
            
        } // end outer while
        
        return entries;
    }
    
    
    void printTable()
    {
        for (int i = 0; i < _size; ++i) {
            printf("table[%d] = ", i);
            if ( _table[i] == NULL ) {
                printf("NULL\n");
            }
            else {
                FX3TableEntry<KeyType,ValueType> * iter = _table[i];
                while ( iter ) {
                    switch ( _keyType ) {
                        case FX_KEYTYPE_CHARPTR:
                            printf("%s ", iter->key);                            
                            break;  
                        case FX_KEYTYPE_INT:
                            printf("%d ", iter->key);                            
                            break;  
                    }
                    iter = iter->next;
                }
                printf("\n");
            }
        }
    }
    
    
    int getCount()
    {
        return _numEntries;
    }
    
    
    // overloaded hash method for char * keys
    unsigned hashMethod(char * k )
    {
        unsigned char * key = (unsigned char *)k;
        unsigned long hash = 5381;
        int c; 
        while ( (c = *key++) ) 
            hash = ((hash << 5) + hash) + c; // hash*33 + c
        return hash % FX3_FX3DICTIONARY_SIZE;
    }
    
    
    // overloaded hash method for int keys, see http://www.concentric.net/~ttwang/tech/inthash.htm
    unsigned hashMethod(int k)
    {
        unsigned hash = (unsigned)k;
        
        hash = (hash+0x7ed55d16) + (hash<<12);
        hash = (hash^0xc761c23c) ^ (hash>>19);
        hash = (hash+0x165667b1) + (hash<<5);
        hash = (hash+0xd3a2646c) ^ (hash<<9);
        hash = (hash+0xfd7046c5) + (hash<<3);
        hash = (hash^0xb55a4f09) ^ (hash>>16);
        
        return hash % FX3_FX3DICTIONARY_SIZE;
    }
    
    
    
    
};




#endif
