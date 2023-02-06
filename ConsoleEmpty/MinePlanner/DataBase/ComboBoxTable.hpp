#ifndef MINEPLANNER_DATABASE_COMBOBOXTABLE_HPP
#define MINEPLANNER_DATABASE_COMBOBOXTABLE_HPP
#include <vector>
#include <sqlite3x.hpp>
namespace MinePlanner{
namespace DataBase{
class ComboBoxTable
{
public:
	ComboBoxTable(sqlite3x::sqlite3_connection& connection);
	std::vector<int> getComboboxOrder()const{ return m_combobox_order; }
private:
	std::vector<int> m_combobox_order;
};
}//DataBase
}//MinePlanner
#endif