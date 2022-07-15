#include "StudentSpellCheck.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

SpellCheck* createSpellCheck()
{
	return new StudentSpellCheck;
}

StudentSpellCheck::TrieNode::TrieNode(){
    end_word = false;
    
    for (int i = 0; i < 27; i++){
        children[i] = nullptr;//sets eachchild to null ptr as a defualt 
    }
    
    
}


void StudentSpellCheck::insert(TrieNode *root, string word){
    struct TrieNode* p = root;
    
    
    for (int i = 0; i < word.length(); i++){
        int alp;
        if (word[i] == '\''){
            alp = 26;
        } else {
            
            
            alp = word[i] - 'a';
        }
        if (!p->children[alp]){
            p->children[alp] = new TrieNode();
        }
        p = p->children[alp];
        
        
        
    }
    
    
    
    p->end_word = true;
    
    
    
    
    
    
}


bool StudentSpellCheck::search(TrieNode* root, string word){
    struct TrieNode* p = root;
    
    
    for (int i = 0; i < word.length(); i++){
        int alp;
        if (word[i] == '\''){
            alp = 26;
        } else {
            
            
            alp = word[i] - 'a';
        }
        if (!p->children[alp]){
            return false;
        }
        p = p->children[alp];
        
        
        
    }
    
    
    
    return (p != NULL && p->end_word);
    
}







void StudentSpellCheck::deleteAll(TrieNode* root){
    if (root == nullptr){
        return;
    }
    
    for (int i = 0; i < 27; i++){
        deleteAll(root->children[i]); // will loop through with recursion
    }
    delete root;
    root = nullptr;
}




//void StudentSpellCheck::findSuggestion(TrieNode* root, string word, string &suggestion, int maxSug){
//    struct TrieNode* p = root;
//    
//    
//    for (int i = 0; i < word.size();i++){
//        
//        
//        
//        
//        
//    }
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//}

StudentSpellCheck::~StudentSpellCheck() {
    TrieNode* temp = m_head;
    deleteAll(temp); 
	// TODO
}

bool StudentSpellCheck::load(std::string dictionaryFile) {
    ifstream infile(dictionaryFile);
    if (!infile){
        return false;
    }
//    deleteAll(m_head);
    string s;
    m_head = new TrieNode;
    TrieNode* temp = m_head;
    while (getline(infile, s)){
    insert(temp, s);
    }
    return true;
}

bool StudentSpellCheck::spellCheck(std::string word, int max_suggestions, std::vector<std::string>& suggestions) {
    
    string r = "";
    for (int i = 0; i < word.size(); i++){
        
       r += tolower(word[i]);
    }
    
    
    if (search(m_head, r)){
        suggestions.clear();
        return true;
    }
    
  
//
//    for (int i = word.size() -1; i >= 0; i--){
//
//        string word2 = r;
//        for (int j = 0; j < 26)
//
//
//
//
//    }
//
    
    
    
    
    
    
    
//    struct TrieNode* p = m_head;
//
//
//    for (int i = 0; i < word.length(); i++){
//        int alp;
//        if (word[i] == '\''){
//            alp = 26;
//        } else {
//
//
//            alp = word[i] - 'a';
//        }
//        if (!p->children[alp]){
//            return false;
//        }
//        p = p->children[alp];
//
//        if (i == word.length() -1){
//
            
            
            
            
            
            
            
      //  }
        
        
        
   // }
    
    
    
    
    
    
    
    
   
//    suggestions.push_back(word);
    
    
    
    
    
    
    
	return false;
}

void StudentSpellCheck::spellCheckLine(const std::string& line, std::vector<SpellCheck::Position>& problems) {
    

    
    int c = 0;
    for (int i = 0; i < line.length(); i++){
        while (isalpha(line[i])){
            
            c++;
            
        
//        
//        
            Position t;
            t.start = i - c;
            t.end = c;
           string r = line.substr(i - c , c);
           if (!search(m_head, r) ){
           problems.push_back(t);
                   
               c = 0;
               
        }
//        
//        
//        
//
//        
    }
//    
//    
//    
//    
//    
    
    }
}
