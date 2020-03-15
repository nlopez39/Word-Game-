#include <myLib.h>
#include <algorithm>
#include <random>
#include <unordered_map>

// Global variables

std::vector<std::string> dictionary;
std::unordered_map<std::string,bool> HashMap;

// A function to check if a string is a valid English word
ucm::json WordGame::checkWord(std::string word){
    ucm::json x;

    x["word"] = word;
    x["valid"] = false;

    auto got = HashMap.find(word);
    if (got != HashMap.end()){
        x["valid"] = true;
    }
    
    return x;
}


// A function that generates 9 letters as a starting set for the game
ucm::json WordGame::getList(){

    dictionary = readWordsFile("misc/english.txt");

    std::vector<std::string> wordN;

    for(int i = 0;i <dictionary.size();i++){
        if(dictionary[i].length()==9){
            wordN.push_back(dictionary[i]);
        }
    }
    std::random_device dev;
     std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(65, 90);
   
    std::string Nine;
    int t = dist(rng);
    Nine = wordN[t];
    std::vector<char>shuffledNine = mixup(Nine);
    std::cout << Nine <<std::endl;

    ucm::json result;

  
    
    for (int i = 0; i < 9; i++){
        //int r = dist(rng);
        result.push_back(shuffledNine[i]);
    }

    for(int j = 0; j< dictionary.size(); j++){
        HashMap.insert({dictionary[j],1});
    }
    

    return result;
 }

// A function that finds all words that can be made up of a given word
ucm::json WordGame::allSubWords(std::string word){
	 ucm::json answer;
    
    std::vector<std::string> allPossible;
    allPossible = getAllPossibleSubstrings(word);
    for(int i=0;i< allPossible.size();i++){
        if(checkWord(allPossible[i])["valid"]){
            answer.push_back(allPossible[i]);
        }
    }
    
       //answer.push_back("NO SOLUTION AVAILABLE");
    
     //permutation of the word that is given or in this case the re
    //answer.push_back("SOLUTIONS:");

     return answer;



// Helper functions...



std::vector<std::string> distinct_powerset(std::string str){
    if (str.size() == 0){
        std::vector<std::string> result;
        result.push_back("");

        return result;
    }

    else{
        char head = str[0];
        std::string tail;
        tail = str.substr (1,std::string::npos);

        std::vector<std::string> res = distinct_powerset(tail);
        std::vector<std::string> ans = res;

        for (auto element : res){
            std::string temp = element;
            temp.insert(temp.begin(), head);
            bool found = false; 
            
            for (std::string curr : ans){
                if (curr == temp){
                    found = true;
                    break;
                }
                else{
                    if (curr != "" && std::is_permutation(temp.begin(), temp.end(), curr.begin())){
                        found = true;
                        break;
                    }
                }
            }

            if (!found){
                ans.push_back(temp);
            }
        }

        return ans;
    }
}

bool isShuffled(std::vector<char> one, std::vector<char> two){
    bool different = !std::equal(one.begin(), one.end(), two.begin());
    bool permutation = std::is_permutation(one.begin(), one.end(), two.begin());

    return different && permutation;
}

void permute(std::string a, int l, int r, std::unordered_map<std::string, bool>& results) {

    if (l == r)  {
        auto got = results.find(a);
        if (got == results.end()){
            results.insert({a, true});
        }
    }  
    else {  
        for (int i = l; i <= r; i++) {   //permutations 
            char temp = a[l];
            a[l] = a[i];
            a[i] = temp;
             
            permute(a, l+1, r, results);  

            temp = a[l];
            a[l] = a[i];
            a[i] = temp;  
            
        }  
    }  
       
}  

bool equivalent(std::vector<std::string> one, std::vector<std::string> two){
    if (one.size() == two.size()){
        bool oneInTwo = true;
        for (int i = 0; i < one.size(); i++){
            bool found = false;

            for (std::string curr : two){
                if (curr == one[i] || std::is_permutation(one[i].begin(), one[i].end(), curr.begin())){
                    found = true;
                    break;
                }
            } 
            if (!found){
                oneInTwo = false;
                break;
            }
        }

        return oneInTwo;
    }
    else{
        return false;
    }
}

std::vector<std::string> getAllPossibleSubstrings(std::string word){
    std::vector<std::string> ps = distinct_powerset(word)
    

	std::vector<std::string> possible;

    for (std::string item : ps){
        //std::cout << item << std::endl;
        if(item.size() > 0){
			if (item.size() == 1){
				possible.push_back(item);
			}
			else{
				std::unordered_map<std::string, bool> curr;
				permute(item, 0, item.size()-1, curr);

				for (auto element : curr){
					possible.push_back(element.first);
				}
			}
		} 
    }
    return possible;
}

std::vector<char> mixup(std::string word){

    // Transfer the characters of the string into a vector of chars
    std::vector<char> result;

    for (int i = 0; i < word.size(); i++){
        result.push_back(word[i]);
    }
    
    // Shuffle the vector
    std::random_shuffle(result.begin(), result.end());

    return result;
}

std::vector<std::string> readWordsFile(std::string filename){
    std::ifstream file(filename);
    std::string str; 

    std::vector<std::string> words;

    while (std::getline(file, str)){
        words.push_back(boost::to_upper_copy(str));
        
    }

    return words;
}


