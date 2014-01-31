#if !defined _CFILETREE_H__INCLUDED_
#define _CFILETREE_H__INCLUDED_


#include <list>
#include <afxmt.h>
using namespace std;

typedef struct Inode
{
	CString lpszFileName;
	BOOL bHasChild;
	BOOL bHasSibling;
	BOOL bIsDir;
	UINT nFileSize;
	UINT nBegin;
	// default constructor
	Inode(CString FileName="", BOOL isDir=0, UINT FileSize=0, 
		BOOL HasChild=0, BOOL HasSibling=0, UINT Begin=0)
	{
		lpszFileName = FileName;
		bIsDir = isDir;
		nFileSize = FileSize;
		bHasChild = HasChild;
		bHasSibling = HasSibling;
		nBegin = Begin;
	}
	// copy constructor
	Inode(const Inode & cp)
	{
		lpszFileName = cp.lpszFileName;
		bIsDir = cp.bIsDir;
		nFileSize = cp.nFileSize;
		bHasChild = cp.bHasChild;
		bHasSibling = cp.bHasSibling;
		nBegin = cp.nBegin;
	}
	//copy assignment
	Inode & operator=(const Inode & cp)
	{
		if (&cp != this)
		{
			lpszFileName = cp.lpszFileName;
			bIsDir = cp.bIsDir;
			nFileSize = cp.nFileSize;
			bHasChild = cp.bHasChild;
			bHasSibling = cp.bHasSibling;
			nBegin = cp.nBegin;
		}
		return *this;
	}
	// write into file
	void Write(CFile * & ofp)
	{
		ofp->Write((char*)lpszFileName.GetBuffer(0), 512);
		ofp->Write((char*)&bHasChild, sizeof(BOOL));
		ofp->Write((char*)&bHasSibling, sizeof(BOOL));
		ofp->Write((char*)&bIsDir, sizeof(BOOL));
		ofp->Write((char*)&nFileSize, sizeof(UINT));
		ofp->Write((char*)&nBegin, sizeof(UINT));
	}
	// read from file
	void Read(CFile * & ifp)
	{
		char buffer[512];
		ifp->Read((char*)buffer, 512);
		lpszFileName = (LPTSTR)buffer;
		ifp->Read((char*)&bHasChild, sizeof(BOOL));
		ifp->Read((char*)&bHasSibling, sizeof(BOOL));
		ifp->Read((char*)&bIsDir, sizeof(BOOL));
		ifp->Read((char*)&nFileSize, sizeof(UINT));
		ifp->Read((char*)&nBegin, sizeof(UINT));
	}

}CInode;

typedef struct {
		UINT nDataStart;
		UINT nTreeStart;
}CFileHead;

typedef list<CInode> CInodeList;


/////////////////////////////////////////////////////////////////
// CTreeNode

class CTreeNode : public CObject
{
protected:
	CInode m_fileinfo;
	CTreeNode * lchild;
	CTreeNode * rchild;
	
//operations:
public:
	void new_lchild(const CInode inode=CInode());
	void new_rchild(const CInode inode=CInode());
	void set_inode(const CInode inode);
	CInode & get_inode();
	CTreeNode * get_lchild();
	CTreeNode * get_rchild();
	BOOL has_rchild();
	BOOL has_lchild();
	BOOL is_leaf(){ return has_lchild() && has_rchild(); }
	void free();

public:
	CTreeNode()
	{ 
		lchild = rchild = NULL;
	} 

	CTreeNode(const CTreeNode & cp)
	{
		m_fileinfo = cp.m_fileinfo;
	}

	CTreeNode& operator=(const CTreeNode & cp)
	{
		if (&cp != this)
			CTreeNode(cp);
		return *this;
	}
	~CTreeNode()
	{
	} 
};


class CFileTree : public CObject
{

public: 
	CTreeNode * m_pRoot;

private:
	UINT m_nFileNum;
	void serial(CTreeNode *, CInodeList &);
	void build_tree(CTreeNode * &, CInodeList &);

//Operations
public:
	void clear();
	UINT m_nTotolSize;
	
	void serial(CInodeList &);
	void build_tree(CInodeList &);

	UINT get_filenum() { return m_nFileNum; };
	void set_filenum(UINT n) { m_nFileNum = n; }
	void inc_filenum() { m_nFileNum ++; }
	void dec_filenum() { if (m_nFileNum) m_nFileNum --; };

public:
	CFileTree()
	{
		m_pRoot = NULL;
		m_nFileNum = 0;
	}

	~CFileTree()
	{	
		if (m_pRoot)
			m_pRoot->free();
	}

};


#endif