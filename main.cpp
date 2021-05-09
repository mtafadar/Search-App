// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.

// Remove starter comments and add your own
// comments on each function and on complex code sections.

#include <iostream>
#include "search.h"
using namespace std;

int main() {
    
    // string ans = "hello";

    // cout << "1. " << (ans == cleanToken(".hello")) << endl;

    // cout << "2. " << (ans == cleanToken("...hello")) << endl;
    
    // set<string> tokens = gatherTokens("to be or not to be");

    // set<string> tokensANS;

    // tokensANS.insert("to");

    // tokensANS.insert("be");

    // tokensANS.insert("or");

    // tokensANS.insert("not");

    // cout << "1. " << (tokens.size() == 4) << endl;

    // cout << "2. " << (tokens == tokensANS) << endl;
    
    // map <string, set <string>>indexS;
    //  map <string, set <string>>index;
    //  buildIndex("tiny.txt", index);
    // smartBuildIndex("tiny.txt", indexS);
    
    // for(pair<string, set<string >>x:indexS) {
    //     cout << x.first << " ";
    //     for(string y: x.second){
    //         cout << y << " ";
    //     }
    //     cout << endl;
    // }
     //maxSearch(indexS);
     // minSearch(indexS);
    //findQueryMatches(index, "fish");
    
    searchEngine("tiny.txt");
    
    

    return 0;
}

