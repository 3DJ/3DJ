//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Common.h"
#include "DataPool.h"
using namespace Common;
using namespace DataPool;

bool CDataPool::initSounds()
{
    if ( !loadFromFile("config.3dj") ) {
        return false;
    }

    for ( mapEntity::iterator it = m_mapDataPool.begin(); it != m_mapDataPool.end(); it++ )
    {
        m_vectorRefEntity.push_back( it );
    }
    //    m_configFile.saveToFile( "3dj.config", m_mapDataPool);

    return true;
}

bool CDataPool::getEntityByName( string key, SEntity& entity)
{
    bool bRet = false;
    lock(); // add lock for thread safe
    mapEntity::iterator iterData = m_mapDataPool.find( key );
    if ( iterData != m_mapDataPool.end() )
    {
        entity = iterData->second;
        bRet = true;
    }
    unlock();

    return bRet;
}

bool CDataPool::getValueByName( string key, string& val )
{
    bool bRet = false;
    lock(); // add lock for thread safe
    mapEntity::iterator it = m_mapDataPool.find( key );
    if ( it != m_mapDataPool.end() )
    {
        val = it->second.value;
        bRet = true;
    }
    unlock();

    return bRet;
}

bool CDataPool::getPointerByName( string key, void* &val)
{
    return getRefByName( key, val);
}

bool CDataPool::getRefByName( string key, void* &val )
{
    bool bRet = false;
    lock(); // add lock for thread safe
    mapEntity::iterator it = m_mapDataPool.find( key );
    if ( it != m_mapDataPool.end() )
    {
        val = it->second.pointer;
        bRet = true;
    }
    unlock();

    return bRet;
}

mapEntity CDataPool::getDataPool()
{
    return m_mapDataPool;
}

vector<mapEntity::iterator> CDataPool::getVector()
{
    return m_vectorRefEntity;
}

bool CDataPool::setEntity( string key, SEntity entity)
{
    bool bRet = false;
    lock(); // add lock for thread safe
    mapEntity::iterator it = m_mapDataPool.find( key );

    try{
        if ( it == m_mapDataPool.end() ){
        }
        else{
            // this will be easy read. but it's inefficient.
            m_mapDataPool[key] = entity;
            bRet = true;
        }
    }
    catch(exception e){
        cout<<"CDataPool::setEntity exception:"<<e.what();
    }
    unlock();

    return bRet;
}

bool CDataPool::createEntity( string key, SEntity entity )
{
    bool bRet = false;
    lock(); // add lock for thread safe
    mapEntity::iterator it = m_mapDataPool.find( key );

    try{
        if ( it == m_mapDataPool.end() ){
            m_mapDataPool.insert( it, make_pair( key, entity));
            // update the vector
            m_vectorRefEntity.push_back(it);
            bRet = true;
        }
    }
    catch(exception e){
        cout<<"CDataPool::createEntity exception:"<<e.what();
        // exception
    }
    unlock();

    return bRet;

}

bool CDataPool::createRef( string key, void* val)
{
    bool bRet = false;
    lock(); // add lock for thread safe
    SEntity entity;
    entity.isSaved = false;
    mapEntity::iterator it = m_mapDataPool.find( key );

    try{
        if ( it == m_mapDataPool.end() ){
            entity.pointer = val;
            m_mapDataPool.insert( it, make_pair( key, entity));
            bRet = true;
            // update the vector
            //m_vectorRefEntity.push_back(it);
        }
    }
    catch(exception e){
        cout<<"CDataPool::createRef exception:"<<e.what();
    }
    unlock();

    return bRet;
}

bool CDataPool::setValue( string key, string val, bool cover )
{
    bool bRet = false;
    lock(); // add lock for thread safe
    SEntity entity;
    entity.isSaved = true;
    entity.value = val;

    mapEntity::iterator it = m_mapDataPool.find( key );
    try{
        if ( it == m_mapDataPool.end() ){
            if ( cover ){
                m_mapDataPool[key] = entity;
                bRet = true;
            }

        }
        else{
            // this will be easy read. but it's inefficient.
            m_mapDataPool[key] = entity;
            bRet = true;
        }
    }
    catch(exception e){
        cout<<"CDataPool::setValue exception:"<<e.what();
    }
    unlock();

    return bRet;
}

int CDataPool::findIndexInVector( string val )
{
    int iRet = -1;
    lock(); // add lock for thread safe
    for ( int index = 0; index < m_vectorRefEntity.size(); index ++)
    {
        if ( m_vectorRefEntity[index]->first == val )
        {
            iRet = index;
        }
    }
    unlock();

    return iRet;
}

string* CDataPool::findValueRef( string key)
{
    string* sRet = 0;
    lock(); // add lock for thread safe
    mapEntity::iterator it = m_mapDataPool.find( key );

    if ( it != m_mapDataPool.end() ){
        sRet = &(it->second.value);
    }
    unlock();

    return sRet;
}

SEntity* CDataPool::findEntityRefInVector( string val )
{
    lock(); // add lock for thread safe
    int index = findIndexInVector( val );
    unlock();

    return (&(m_vectorRefEntity[index]->second));
}

bool CDataPool::loadFromFile( string filePath )
{
    return m_configFile.loadFromFile( filePath.c_str(), m_mapDataPool);
}

bool CDataPool::saveToFile( string filePath )
{
    return m_configFile.saveToFile( filePath.c_str(), m_mapDataPool);
}
