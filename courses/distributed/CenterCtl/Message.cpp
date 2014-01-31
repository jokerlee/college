// Message.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterCtl.h"
#include "Message.h"

////////////////////////// CSlaveMessage 成员函数 //////////////////////////////

// copy constructor
CSlaveMessage::CSlaveMessage( )
    :type(0), mode(0), id(0), speed(0), trgtTemp(0), crntTemp(0), optional(0)
{

}


CSlaveMessage::CSlaveMessage( const CSlaveMessage & rhs )
{
    this->type      =   rhs.type;
    this->mode      =   rhs.mode;
    this->id        =   rhs.id;
    this->speed     =   rhs.speed;
    this->crntTemp  =   rhs.crntTemp;
    this->trgtTemp  =   rhs.trgtTemp;
    this->optional  =   rhs.optional;
}

void CSlaveMessage::Serialize( CArchive & ar )
{
    if ( ar.IsStoring() )
    {
        ar << this->type;
        ar << this->mode;
        ar << this->id;
        ar << this->speed;
        ar << htonl( this->crntTemp );
        ar << htonl( this->trgtTemp );
        ar << htonl( this->optional );
    }
    else
    {
        DWORD tmp;
        ar >> this->type;
        ar >> this->mode;
        ar >> this->id;
        ar >> this->speed;
        ar >> tmp; this->crntTemp = ntohl( (long)tmp );
        ar >> tmp; this->trgtTemp = ntohl( (long)tmp );
        ar >> tmp; this->optional = ntohl( (long)tmp );
    }
}


////////////////////////// CCenterMessage 成员函数 //////////////////////


// copy constructor

CCenterMessage::CCenterMessage( )
    :type(0), mode(0), info(0), optional(0)
{

}

CCenterMessage::CCenterMessage( const CCenterMessage & rhs )
{
    this->type      =   rhs.type;
    this->mode      =   rhs.mode;
    this->info      =   rhs.info;
    this->optional  =   rhs.optional;
}


void CCenterMessage::Serialize( CArchive & ar )
{
    if ( ar.IsStoring() )
    {
        ar << this->type;
        ar << this->mode;
        ar << (DWORD)htonl( this->info );
        ar << (DWORD)htonl( this->optional );
    }
    else
    {
        DWORD tmp;
        ar >> this->type;
        ar >> this->mode;
        ar >> tmp; this->info = ntohl( (long)tmp );
        ar >> tmp; this->optional = ntohl( (long)tmp );
    }
}
