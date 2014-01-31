
#include "stdafx.h"
#include "SystemIcon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CImageList * CSystemImageList::m_gpLargeImageList = NULL;
CImageList * CSystemImageList::m_gpSmallImageList = NULL;

int CSystemImageList::m_gRefCount = 0;

void CSystemImageList::DestroyGlobalList( CImageList *& rpImageList )
{
    if( rpImageList )
    {
		rpImageList->Detach();

		delete rpImageList;
		rpImageList = NULL;
    }
}

BOOL CSystemImageList::InitGlobalList( CImageList *& rpImageList, BOOL bSmall /* = TRUE */ )
{
    BOOL bRet = FALSE;

    if( ! rpImageList )
    {
		// Create the singleton CImageList object, which will be
		// passed around to anyone who needs it
		rpImageList = new CImageList;
    
		if( rpImageList )
		{
			SHFILEINFO sfi;
			DWORD dwFlags = SHGFI_USEFILEATTRIBUTES|SHGFI_SYSICONINDEX;
			
			if( bSmall )
				dwFlags |= SHGFI_SMALLICON;

			size_t size = sizeof( SHFILEINFO );

			rpImageList->Attach( (HIMAGELIST)SHGetFileInfo( NULL, FILE_ATTRIBUTE_NORMAL, 
						&sfi, size, dwFlags ) );
			
			// Make the background colour transparent, works better for lists etc.
			rpImageList->SetBkColor( CLR_NONE );

			bRet = TRUE;
		}
    }

    return( bRet );
}

CSystemImageList::CSystemImageList()
{
    // Initialise both lists when the first instance is created
    if( m_gRefCount == 0 )
    {
		ASSERT( ! m_gpSmallImageList && ! m_gpLargeImageList );

		InitGlobalList( m_gpSmallImageList, TRUE );
		InitGlobalList( m_gpLargeImageList, FALSE );
    }

    // Keep a reference count
    m_gRefCount++;
}

CSystemImageList::~CSystemImageList()
{
    // One less instance using the lists
    m_gRefCount--;

    // Nobody's using the list now, so throw 'em away
    if( m_gRefCount == 0 )
    {
		DestroyGlobalList( m_gpLargeImageList );
		DestroyGlobalList( m_gpSmallImageList );
    }
}

// Helper function to get the icon index of a particular file/object
void CSystemImageList::GetIcon(SHFILEINFO &sfi, const CInode& info, BOOL bOpen = FALSE)const
{
	memset(&sfi, 0, sizeof(sfi));
    DWORD dwFlags = SHGFI_DISPLAYNAME  | SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES | 
				SHGFI_SMALLICON | SHGFI_SYSICONINDEX | (bOpen ? SHGFI_OPENICON : 0);
	
	CString type;
	type = info.lpszFileName;
	type = type.Right(type.GetLength()-type.ReverseFind('\\')-1);

   	if (info.bIsDir)
		SHGetFileInfo(type, FILE_ATTRIBUTE_DIRECTORY, &sfi, sizeof(sfi), dwFlags);  
	else
		SHGetFileInfo(type, FILE_ATTRIBUTE_NORMAL, &sfi, sizeof(sfi), dwFlags);
 

}

CImageList * CSystemImageList::GetImageList( BOOL bSmall  = TRUE  ) const 
{
    CImageList * pList = NULL;
    
    if( bSmall )
		pList = m_gpSmallImageList;
    else
		pList = m_gpLargeImageList;

    // Ought to return a const pointer here (so noone tries to delete
    // the lists). However, SetImageList in the common controls requires
    // a non-const pointer, so it wouldn't be much use to anyone.
    return( pList ); 
}
