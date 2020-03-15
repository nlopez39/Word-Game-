#ifndef MYLIB
#define MYLIB

#include <string>
#include <server.h>

// Functions that serve the endpoints
struct WordGame{
    

ucm::json checkWord(std::string);

ucm::json getList();

ucm::json allSubWords(std::string);


// Some helper functions

std::vector<std::string> readWordsFile(std::string filename);
std::vector<std::string> distinct_powerset(std::string str);
void permute(std::string a, int l, int r, std::unordered_map<std::string, bool>& results);
bool isShuffled(std::vector<char> one, std::vector<char> two);
bool equivalent(std::vector<std::string> one, std::vector<std::string> two);
std::vector<char> mixup(std::string word);
std::vector<std::string> getAllPossibleSubstrings(std::string word);
};
#endif
