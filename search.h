// Author: Morour Tafadar
// Project 2
// This projet is about search and corresponding result
// is url just like google search
#pragma once
#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <iterator>
using namespace std;
//

//
// ----1. gatherTokensStopwords
// this function tokenize each of the word
// however, this does not  take anyword which
// stops word ex:if, on, to, the, a etc
// and finally this token will be inputed
// into a set  and returns the set
// ----------##------------------
//
// -----2. smartBuildIndex
// this function  put all the word in a key
// and corresponding website of the webiste in a set
// this smartBuildIndex does not take any redundant
// word  such as stops word
// -----------##-------------
//
// -----3. maxSearch
// this function  prints out the word
//  which is seen highest number of time in a file
//  this function can be used by smartBuildIndex
//  it can also be used with regular buildIndex
// -----------##------------
//
// -----4. minSearch
// this function return the word
// which is seen minimal time in a file
// this function also can be used by smartBuildIndex
// and it can also be used by regular buildIndex
//
//
// -----5. searchEngine2
// parameter  just file
// All direction is followd
//
//
// this function  takes a string and
// if any alphbet found it makes lower case
string making_lowerCase(string s) {
    for (char &c : s) {
        c = tolower(c);
    }
    return s;
}

// this is also a helper function of cleantoken
// which checks if the string has atleast one alphebet
// if any alphebet found the founction  immedietly retun the string
// else it return a empty string

string checkAlphabet(string s) {
    int n = s.size();
    for (int i = 0; i < n; i++) {
        if (isalpha(s.at(i))) {
            return s;
        }
    }
    return "";
}

// this function is a helper function for  cleantoken
// this update lower and higher index

void cleanTokenHelper(int &i, int &lastIndex, string &s) {
    while (i <= lastIndex && ispunct(s[i])) {
        i++;  //  increment i as long as punctuation found
    }
    while (i <= lastIndex && ispunct(s[lastIndex])) {
        lastIndex--;  //  decrement as long as last index is punct
    }
}

// This function will take a string and will
// get rid of any punctuation before the start of the
// string and end of the string. However,
// it will not get rid of any punctuation if its
// middle of a string
// Special case: It will  return empty sring if
// the string does not contain at least one alphabet letters

string cleanToken(string s) {
    s = making_lowerCase(s);
    string alphabetCheck = checkAlphabet(s);
    int i = 0;
    int lastIndex = s.size() -1;
    if (alphabetCheck == "") {
        return "";
    }

    cleanTokenHelper(i, lastIndex, s);
    if (i > lastIndex) {
        return "";
    } else {
        return s.substr(i, lastIndex - i +1);
    }
}

// this function  break down a string and
// tokenize them and  returns a set of tokens
// so  there is no element inserted twice

set<string> gatherTokens(string text) {
    set<string> tokens;
    string token;
    istringstream buffer(text);
    while (buffer >> token) {
        //  cleaning up each token
        string s = cleanToken(token);
        if (s == "") {
            // if cleanToken return empty string then
            // we don't put that into the set
            continue;
        }
        tokens.insert(s);
    }
    return tokens;
}
// this function retuns a number of count of url
// from the file. Also, it gives a inverted index
// of key values. A key can have a set of unique url
int buildIndex(string filename, map<string, set<string>>& index) {
    ifstream infile(filename);
    if (!infile.good()) {
        cout <<"Please enter a valid file" << endl;
        return 0;
    }
    int count = 0;
    string webAddress;
    string textfile;
    while (!infile.eof()) {
        getline(infile, webAddress);
        getline(infile, textfile);
        if (!infile.fail()) {
            count++;
            set<string> temp = gatherTokens(textfile);
            for (auto &i : temp) {
                // inserting each token with webAddress
               index[i].insert(webAddress);
            }
        }
    }
    // return number of urls
    return count;
}

// this function return the match finded word of their website
// the search term can be just single or compound
// using built in set function

set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    string operation;
    istringstream buffer(sentence);
    while (buffer >> operation) {
        set <string> temp;
        set <string> insertValues;
        string cleanV = cleanToken(operation);
        if (index.count(cleanV) == 1) {
            temp = index[cleanV];
        }
        if (operation[0] == '+') {
            set_intersection(result.begin(), result.end(),
                            temp.begin(), temp.end(),
                            inserter(insertValues, insertValues.end()));
        } else if (operation[0] == '-') {
            set_difference(result.begin(), result.end(),
                           temp.begin(), temp.end(),
                           inserter(insertValues, insertValues.end()));
        } else {
          set_union(result.begin(), result.end(),
                      temp.begin(), temp.end(),
                      inserter(insertValues, insertValues.end()));
        }
        // assining inservalues to result
        // insertValues found  in union, intersection or difference
        // or the value was a single search
        result = insertValues;
    }
    // for(auto iterator = result.begin();
    // iterator != result.end(); iterator++) {
    //     cout << *iterator << endl;
    // }
    return result;
}

//
// this function let user to prompt and  shows
// according to their search
// this also shows how many url and how many unqiue
// eliments found in the file
void searchEngine(string filename) {
    map <string, set <string>> index;
    cout <<"Stand by while building index..."<< endl;
    int x = buildIndex(filename, index);
    cout <<"Indexed " << x << " pages containing " <<
    index.size()<< " unique terms" << endl;
    string userSearch;
    cout << "Enter query sentence (press enter to quit): ";
    getline(cin, userSearch);
    while (userSearch != "") {
        set <string> result = findQueryMatches(index, userSearch);
        cout << "Found " << result.size() << " matching pages" << endl;
        for (auto iterator = result.begin();
             iterator != result.end(); iterator++) {
            cout << *iterator << endl;
        }
        cout <<"Enter query sentence (press enter to quit): ";
        getline(cin, userSearch);
    }
    cout << "Thank you for searching!" << endl;
}
// @creative component function
// this function will tokenize the words
// and it will also  avoid redundant words like
// articles and some preposition and
// then it will put then into a set
set<string> gatherTokensStopwords(string text) {
    set<string> tokens;
    string token;
    istringstream buffer(text);
    while (buffer >> token) {
        //  cleaning up each token
        string s = cleanToken(token);
        if (s == "" || s == "if" || s==  "the" || s==  "a"
           || s == "and" ||s ==  "with" || s==  "for" ||
            s==  "on" ||s ==  "off" || s == "to") {
            // if cleanToken return empty string then
            // we don't put that into the set
            continue;
        }
        tokens.insert(s);
    }
    // for(auto iterator = tokens.begin();
    // iterator != tokens.end(); iterator++) {
    //     cout << *iterator << endl;
    // }
    return tokens;
}
// this is a smart buildIndex which ignore all the
// the redundant  words and marginalize into map
// the won't be any copy of the word duplicated
//
int smartBuildIndex(string filename, map<string, set<string>>& indexS) {
    ifstream infile(filename);
    if (!infile.good()) {
        cout <<"Please enter a valid file" << endl;
        return 0;
    }
    int count = 0;
    string webAddress;
    string textfile;
    while (!infile.eof()) {
        getline(infile, webAddress);
        getline(infile, textfile);
        if (!infile.fail()) {
            count++;
            set<string> temp = gatherTokensStopwords(textfile);
            for (auto &i : temp) {
                // inserting each token with webAddress
               indexS[i].insert(webAddress);
            }
        }
    }
    // return number of urls
    return count;
}
// this function works and give the highest key that
// maximum number of  sets along with that key
// condition: User must need to use  SmartbuildIndex to
//  see the highest word without stops words
// Flexsibility: user also can search the regular
// key whihc holds highest number of set by
// using regular build Index;
void maxSearch(map<string, set<string>>&indexS) {
    map <string, set<string> > :: iterator itr;
    int max = 0;
    string LargeS;
    for (itr = indexS.begin(); itr != indexS.end(); ++itr) {
        if (max < itr -> second.size()) {
            max = itr->second.size();
            LargeS = itr->first;
        }
    }
    cout << LargeS << endl;
}
//
// this function gives a word which is shown minimal
// amount of time in a website
// This function can be use with SmartbuildIndex
// or a user also can use it with  general buildIndex
void minSearch(map<string, set<string>>&indexS) {
    map <string, set<string> > :: iterator itr;
    int min = 9999;
    string smallS;
    for (itr = indexS.begin(); itr != indexS.end(); ++itr) {
        if (min > itr -> second.size()) {
            min = itr->second.size();
            smallS = itr->first;
        }
    }
    cout << smallS << endl;
}



void searchEngine2(string filename) {
    cout << "Welcome" << endl;
    cout <<"Here you can see which which keyword has highest";
    cout <<"and lowest number of set" << endl;
    cout << endl;
    cout <<"For regular search please enter 1 and";
    cout << "for advanced search please enter 2:   ";
    int value;
    cin >> value;
    if (value == 1){
       map <string, set <string>>index;
       buildIndex(filename, index);
       cout << "For highest word please enter High";
       cout <<" and fow lowest please enter MIN: ";
       string S;
       cin >> S;
       if (S == "HIGH") {
           maxSearch(index);
       } else{
           minSearch(index);
       }
    }
    else {
        map <string, set <string>>indexS;
        smartBuildIndex(filename,indexS);
        cout << "For highest word please enter HIGH ";
       cout <<"and fow lowest please enter MIN:  ";
       string S;
       cin >> S;
       if (S == "HIGH") {
           maxSearch(indexS);
       } else{
           minSearch(indexS);
       }
        
    }
    cout << "Thank you " << endl;
}

