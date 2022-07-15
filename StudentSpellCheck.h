#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>

class StudentSpellCheck : public SpellCheck {
public:
    StudentSpellCheck() { }
	virtual ~StudentSpellCheck();
	bool load(std::string dict_file);
	bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
	void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:

   
    struct TrieNode {
        TrieNode();
        struct TrieNode* children[27]; // possible ammount of children
       bool end_word;
    };
    
    void insert(TrieNode* root, std::string word);
    bool search(TrieNode* root, std::string word);
    void deleteAll(TrieNode* root);
//    void findSuggestion(TrieNode* root, std::string word, std::string &suggestion, int maxSug);
    TrieNode* m_head;
    
    
    
};

#endif  // STUDENTSPELLCHECK_H_
