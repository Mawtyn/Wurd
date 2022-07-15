#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>


using namespace std;

TextEditor* createTextEditor(Undo* un)
{
	return new StudentTextEditor(un);
}

StudentTextEditor::StudentTextEditor(Undo* undo)
 : TextEditor(undo) {
	// TODO
     m_row = 0;
     m_col = 0;
     m_lineNums = 0;
//     writing = "";
     m_list.push_back("");
     it = m_list.begin();
     m_cor = true;
//     m_order = true;
//     m_lineNums = 0;
}

StudentTextEditor::~StudentTextEditor()
{
	// TODO
    m_list.clear();
    //iterator stuff too?
}

bool StudentTextEditor::load(std::string file) {
    
    string str; // will be initialized the first time the while loop runs
    ifstream infile(file);
//
    if (!infile){
	return false;
    } else {
    
    // making sure to reset everything if it is currently open and get the lines loaded
        reset();
        
        m_lineNums = 0;
        
        while (getline(infile, str)){
            if (str.at(str.size() -1) == '\r'){
                str.erase(str.size() -1, 1);
            }
                
                
                m_list.push_back(str);
                m_lineNums++;
          
            }
            
    }
    m_row = 0;
    m_col = 0;
    return true;


}

bool StudentTextEditor::save(std::string file) {
    
    
    ofstream notinfile(file);
    if (!notinfile){
        
        return false;
    }
    
    
  
    for (it = m_list.begin(); it != m_list.end(); it++){
        notinfile << *it << '\n';
    }
    
    
    
    
    
    
	return true;
}

void StudentTextEditor::reset() {
    StudentTextEditor::~StudentTextEditor();
    m_col = 0;
    m_row = 0;
    m_list.clear();
    getUndo()->clear();
    

}

void StudentTextEditor::move(Dir dir) {
    list<string>::iterator tempIt = it;
    switch (dir) {
        case LEFT: // implementing left first because its the first one I could test
                if (m_col > 0) {
                    m_col--;
                       }
                       break;
        case RIGHT:
                   if (m_col < (*tempIt).size()) {
                       m_col++;
                   } else if (m_col == (*tempIt).size() && m_row < m_lineNums && tempIt != m_list.end()) {
                       m_row++;
                       m_col = 0;
                       tempIt++;
                      
                   }
                   break;
        case UP:
                    if (tempIt != m_list.begin() && m_row > 0) {
                        m_row--;
                        tempIt--;
                       
                        
                        if ((*tempIt).size() < m_col){
                            m_col = (*tempIt).size();
                        }
                    }
                    break;
                case DOWN:
                    if (tempIt != m_list.end() && m_row < m_lineNums) {
                        m_row++;
                        tempIt++;
                      
                        
                        if ((*tempIt).size() < m_col){
                            m_col = (*tempIt).size();
                        }
                    }
                    break;
                case HOME:
                  m_col = 0;
                  break;
                case END:
                  m_col = (*tempIt).size();
                  break;
        }
            
        
            


}

void StudentTextEditor::del() {
    if (m_col < (*it).size()) {
           (*it).erase(m_col, 1);
       } else if (m_col == (*it).size() && it != m_list.end() && m_row < m_lineNums) {
           it++;
           string string = *it;
           it = m_list.erase(it);
           it--;
           (*it).append(string);
           m_lineNums--;
       }	// TODO
}

void StudentTextEditor::backspace() {
    if (m_col > 0) {
           (*it).erase(m_col - 1, 1);
           m_col--;
       } else if (m_col == 0 && it != m_list.begin()) {
           string string = *it;
           it = m_list.erase(it);
           it--;
           (*it).append(string);
           m_row--;
           m_col = (*it).size();
           m_lineNums--;
           
       }
	// TODO
}

void StudentTextEditor::insert(char ch) {
  //  if (it == m_list.begin()){
    
    
    if (ch == '\t'){
           string writing = "    ";
           (*it).insert(m_col, writing);
           m_col += 4; // tab should move the col over by 4 since its 4 spaces compared to just a regular space that would simply increment it
        getUndo()->submit(Undo::Action::INSERT, m_row, m_col, '\t');
       } else {
           string writing = "";
           writing += ch;
           (*it).insert(m_col, writing);
           m_col++;
           getUndo()->submit(Undo::Action::INSERT, m_row, m_col, ch);
       }
    
    

    
    
        return;
        
        
        
        
 
}

void StudentTextEditor::enter() {
    if (m_row == m_lineNums && m_col == (*it).size()) {
           m_list.push_back("");
           it++;
           m_row++;
           m_lineNums++;
           m_col = 0;
       } else if (m_col == (*it).size() && m_row != m_lineNums) {
           it++;
           m_list.insert(it, "");
           it--;
           m_row++;
           m_lineNums++;
           m_col = 0;
       } else if (m_row == m_lineNums && m_col != (*it).size()) {
           string string = (*it).substr(m_col, (*it).size());  //O(n)
           (*it).erase(m_col, (*it).size());   //O(N) so technically time complexity is 2n which rounds to just n (n being length of substring)
           m_list.push_back(string);
           it++;
           m_row++;
           m_lineNums++;
           m_col = 0;
       } else if (m_row != m_lineNums && m_col != (*it).size()){
           string string = (*it).substr(m_col, (*it).size());  //O(n)
           (*it).erase(m_col, (*it).size());   //O(N) so technically time complexity is 2n which rounds to just n (n being length of substring)
           it++;
           m_list.insert(it, string);
           it--;
           m_row++;
           m_lineNums++;
           m_col = 0;
       }
	
}

void StudentTextEditor::getPos(int& row, int& col) const {
	row = m_row;
    col = m_col;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
    if (startRow < 0 || numRows < 0 || startRow > m_lineNums) {
           return -1;
       }

       lines.clear();

       std::list<std::string>::const_iterator iter = m_list.begin();
       for (int i = 0; i < startRow; i++) {
           iter++;
       }
       
       int l = 0;
       for (; iter != m_list.end() && l < numRows; iter++) {
           string string = *iter;
           lines.push_back(string);
           l++;
       }

       return l;
  
}

void StudentTextEditor::undo() {
    int r, c, num;
       string text = "";
  

       Undo::Action actionTemp = getUndo()->get(r, c, num, text);
       
       if (actionTemp == Undo::Action::ERROR)
           return;
       
       if (actionTemp == Undo::Action::INSERT) {
           m_cor = false;
           m_row = r;
           m_col = c - 1;
           del();
       }
       
       if (actionTemp == Undo::Action::JOIN) {
           m_cor = false;
           m_row = r;
           m_col = c;
           enter();
       }
       
       if (actionTemp == Undo::Action::SPLIT) {
           m_cor = false;
           m_row = r;
           m_col = c;
           backspace();
       }
       
       if (actionTemp == Undo::Action::DELETE) {
           m_cor = false;
           m_row = r;
           m_col = c;
           insert(text.at(0));
       }
       
    m_cor = true;
}
