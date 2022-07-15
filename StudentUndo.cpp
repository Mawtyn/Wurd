#include "StudentUndo.h"

Undo* createUndo()
{
	return new StudentUndo;
}

void StudentUndo::submit(const Action action, int row, int col, char ch) {
    m_struct.s_row = row;
       m_struct.s_col = col;
       m_struct.s_ch = ch;
       m_struct.s_action = action;
       stack.push(m_struct);
       
       if (action == DELETE) {
           m_struct.s_count++;
       } else  {
           m_struct.s_count = 1;
       }
	// TODO
}

StudentUndo::Action StudentUndo::get(int& row, int& col, int& count, std::string& text) {
    if (stack.empty())
           return Undo::Action::ERROR;
       
       Struct temp;
       temp = stack.top();
       
       Action tempA;
       tempA = temp.s_action;
       
       count = temp.s_count;
    count = temp.s_count;
       row = temp.s_row;
       col = temp.s_col;
       text += temp.s_ch;
       
       stack.pop();
       
       return tempA;  // TODO
}

void StudentUndo::clear() {
    while (!stack.empty()) {
           stack.pop();
       }
	// TODO
}
