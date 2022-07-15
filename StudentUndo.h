#ifndef STUDENTUNDO_H_
#define STUDENTUNDO_H_

#include "Undo.h"
#include <stack>
using namespace std;

class StudentUndo : public Undo {
public:

	void submit(Action action, int row, int col, char ch = 0);
	Action get(int& row, int& col, int& count, std::string& text);
	void clear();

private:
    struct Struct
       {
           int s_row, s_col;
           char s_ch;
           Action s_action;
           int s_count;
       };
       Struct m_struct;
       std::stack<Struct> stack;
};

#endif // STUDENTUNDO_H_
