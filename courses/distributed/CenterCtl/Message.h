#pragma once

// CMessage 

class CSlaveMessage : public CObject
{
public:
    CSlaveMessage();
    CSlaveMessage( const CSlaveMessage & rhs );  
    virtual ~CSlaveMessage(){};
    void Serialize( CArchive & ar );

public:
    char type;
    char mode;
    char id;
    char speed;
    int trgtTemp;
    int crntTemp;
    int optional;

public:
    static enum frame_t { FRAME_REQUEST, FRAME_ACK };
    static enum mode_t { MODE_INFO, MODE_REFRIGE, MODE_HEAT };
};


class CCenterMessage : public CObject
{
public:
    CCenterMessage();
    CCenterMessage( const CCenterMessage & rhs );  
    virtual ~CCenterMessage(){};
    void Serialize( CArchive & ar );

public:
    char type;
    char mode;
    int info;
    int optional;

public:
    static enum frame_t { FRAME_INIT, FRAME_INFO, FRAME_REQUEST };
    static enum mode_t { MODE_NACK, MODE_REFRIGE, MODE_HEAT };
};


