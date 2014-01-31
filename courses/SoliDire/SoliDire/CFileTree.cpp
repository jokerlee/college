#include "stdafx.h"
#include "CFileTree.h"


void CTreeNode::new_lchild(const CInode inode /*=Inode()*/)
{
	if (!lchild)
		lchild = new CTreeNode;
	lchild->set_inode(inode);
}

void CTreeNode::new_rchild(const CInode inode /*=Inode()*/)
{
	if (!rchild)
		rchild = new CTreeNode;
	rchild->set_inode(inode);
}

void CTreeNode::set_inode(const CInode inode)
{
	m_fileinfo = inode;
}

CInode & CTreeNode::get_inode()
{
	return m_fileinfo;
}

CTreeNode * CTreeNode::get_lchild()
{
	return lchild;
}

CTreeNode * CTreeNode::get_rchild()
{
	return rchild;
}

BOOL CTreeNode::has_rchild()
{
	return (rchild!=NULL);
}
BOOL CTreeNode::has_lchild()
{
	return (lchild!=NULL);
}

void CTreeNode::free()
{
	if (has_lchild())
		if (lchild->is_leaf())
			delete lchild;
		else
			lchild->free();
	if (has_rchild())
		if (rchild->is_leaf())
			delete get_rchild();
		else
			rchild->free();
}


/////////////////////////////////////////////////////////////////////////////
// CTreeNode

void CFileTree::clear()
{
	delete m_pRoot;
	m_pRoot = NULL;
}

void CFileTree::serial(CInodeList & files)
{
	if (m_pRoot)
		serial(m_pRoot, files);
}

void CFileTree::serial(CTreeNode * p, CInodeList & files)
{
	files.push_back(p->get_inode());
	CInode & tmp = files.back();

	if (p->has_lchild())
	{
		tmp.bHasChild = TRUE;
		serial(p->get_lchild(), files);
	}
	else
		tmp.bHasChild = FALSE;

	if (p->has_rchild())
	{
		tmp.bHasSibling = TRUE;
		serial(p->get_rchild(), files);
	}
	else
		tmp.bHasSibling = FALSE;

}



void CFileTree::build_tree(CInodeList & files)
{
	CTreeNode * p;
	if (!m_pRoot)
	{
		m_pRoot = new CTreeNode;
		p = m_pRoot;
	}
	else
	{
		p = m_pRoot;
		while (p->has_rchild())
			p = p->get_rchild();
		p->new_rchild();
		p = p->get_rchild();
	}
	build_tree(p, files);
}	

void CFileTree::build_tree(CTreeNode * & root, CInodeList & files)
{
	Inode tmp = files.front();
	files.pop_front();
	root->set_inode(tmp);

	CTreeNode * p = root;
	
	if (tmp.bHasChild)
	{
			p->new_lchild();
			p = p->get_lchild();
			build_tree(p, files);
			p = root;
	}

	if (tmp.bHasSibling)
	{
			p->new_rchild();
			p = p->get_rchild();
			build_tree(p, files);
			p = p->get_rchild();
	}
}

