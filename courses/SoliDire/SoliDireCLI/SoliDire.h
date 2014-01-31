// SoliDireDoc.h : interface of the CSoliDireDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _SOLIDIRE_H_
#define _SOLIDIRE_H_

#include "CFileTree.h"

using namespace std;



class CSoliDire
{

// Attributes
private:
	BOOL m_bIsPacked;
	BOOL m_bIsModified;
	CString path;
public:
	CInodeList m_files;
	CFileHead m_CSDHead;
	CFileTree * m_DirTree;
	void pack_file(CFile *, CInodeList::iterator);
	CSoliDire();
	~CSoliDire();

public:
	BOOL is_packed() { return m_bIsPacked; }
	BOOL add_file();
	BOOL add_folder();
	void pack_all_files();
	void set_packed(BOOL isPacked) { m_bIsPacked = isPacked; }
	BOOL save_file();
	BOOL open_file();
	void read_file(CFile *);
	void pack_all_file(CFile *);
	void pack_added_file(CFile *);
	void extract_file(CInode, CFile *, CString);
	void extract_all_files();
	void extract_all_files(CTreeNode *, CFile *, CString);
	void insert_file(CString);
	void build_dir_tree(CString);
	void list_files();
	BOOL IsModified(){ return m_bIsModified; }
	CFileTree * get_dir_tree(){ return m_DirTree; }

private:
	void build_dir_tree(CTreeNode * &, CString);
	void SetModifiedFlag(BOOL ism){ m_bIsModified = ism; }
	CString GetPathName(){ return path; }
	CString SetPathNane(CString p){ path = p; }
	void CSoliDire::list_files(CTreeNode *, UINT);

};

#endif