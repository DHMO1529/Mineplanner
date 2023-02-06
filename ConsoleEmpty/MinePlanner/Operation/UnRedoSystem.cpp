#include "MinePlanner/Operation/UnRedoSystem.hpp"

#include <list>
namespace MinePlanner{
namespace Operation{
namespace{
class UnRedoStack
{
public:
	UnRedoStack():m_stack()
	{
	}
	Work::ptr top()const
	{
		return m_stack.back();
	}
	void push(Work::ptr work)
	{
		m_stack.push_back(work);
		if(MAX_STACK < static_cast<int>(m_stack.size()))
		{
			m_stack.pop_front();
		}
	}
	void pop()
	{
		if(!m_stack.empty())
		{
			m_stack.pop_back();
		}
	}
	bool empty()const
	{
		return m_stack.empty();
	}	
	void clear()
	{
		m_stack.clear();
	}
	int size()const
	{
		return m_stack.size();
	}
private:
	std::list<Work::ptr> m_stack;
	static const int MAX_STACK;
};
const int UnRedoStack::MAX_STACK = 300;

class UnRedoSystemImpl : public UnRedoSystem
{
public:
	UnRedoSystemImpl():m_undoStack(),m_redoStack()
	{
	}

	virtual void execute(Work::ptr work)
	{
		bool result = work->exe();
		if(result)
		{
			m_undoStack.push(work);
		}
		m_redoStack.clear();
	}
	virtual void undo()
	{
		if(m_undoStack.empty())
		{
			return;
		}

		Work::ptr work = m_undoStack.top();
		m_undoStack.pop();

		work->undo();

		m_redoStack.push(work);
	}
	virtual void redo()
	{
		if(m_redoStack.empty())
		{
			return;
		}

		Work::ptr work = m_redoStack.top();
		m_redoStack.pop();

		work->redo();

		m_undoStack.push(work);
	}
	virtual void clear()
	{
		m_undoStack.clear();
		m_redoStack.clear();
	}
private:
	UnRedoStack m_undoStack;
	UnRedoStack m_redoStack;
};
}

UnRedoSystem::ptr UnRedoSystem::create()
{
	return ptr(new UnRedoSystemImpl());
}
}//Operation
}//MinePlanner