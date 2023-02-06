#include "MinePlanner/graphic/DisplayList.hpp"

#include "MinePlanner/graphic/gl.hpp"
#include <boost/assert.hpp>
namespace MinePlanner{
namespace graphic{
class DisplayListImpl
{
public:
	DisplayListImpl():m_list(0)
	{
	}
	~DisplayListImpl()
	{
		this->clear();
	}
	void newList()
	{
		if(m_list){assert(0);}

		m_list = glGenLists(1);
		assert( m_list );
		glNewList(m_list,GL_COMPILE);
	}
	void endList()
	{
		assert( m_list );

		glEndList();
	}
	bool empty()const
	{
		return m_list == 0;
	}
	void clear()
	{
		if(m_list)
		{
			glDeleteLists(m_list,1);
			m_list = 0;
		}
	}
	void call()const
	{
		assert( m_list );
		glCallList(m_list);
	}
private:
	bool m_isNewList;
	unsigned m_list;
};

DisplayList::DisplayList():m_pimpl()
{
}
DisplayList::~DisplayList()
{
}
DisplayList DisplayList::create()
{
	DisplayList disp;
	disp.m_pimpl.reset(new DisplayListImpl());
	return disp;
}
bool DisplayList::hasInstance()const
{
	return m_pimpl;
}
void DisplayList::newList()
{
	m_pimpl->newList();
}
void DisplayList::endList()
{
	m_pimpl->endList();
}
bool DisplayList::empty()const
{
	return m_pimpl->empty();
}
void DisplayList::clear()
{
	m_pimpl->clear();
}
void DisplayList::call()const
{
	m_pimpl->call();
}
}//graphic
}//MinePlanner