#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//loads a dictionary to put it into a vector
vector<string> loadDictionary(const string& filePath) {
    ifstream file(filePath);
    vector<string> dictionary;
    string word;
    while (getline(file, word)) {
        dictionary.push_back(word);
    }
    return dictionary;
}

//optimized levenshtein using wagner fischer approach
int wagnerFischer(const string& s1, const string& s2) {
    int lenS1 = s1.length(), lenS2 = s2.length();
    if (lenS1 > lenS2) {
        return wagnerFischer(s2, s1); // makes it so that s1 is the smaller string
    }

    //first matrix row
    vector<int> currentRow(lenS1 + 1);
    for (int i = 0; i <= lenS1; ++i) {
        currentRow[i] = i;
    }

    for (int i = 1; i <= lenS2; ++i) {
        vector<int> previousRow = currentRow;
        currentRow[0] = i;
        for (int j = 1; j <= lenS1; ++j) {
            int ins = previousRow[j] + 1; //insertion
            int del = currentRow[j - 1] + 1; //deletion
            int sub = previousRow[j - 1] + (s1[j - 1] != s2[i - 1]); //substitution
            currentRow[j] = min({ins, del, sub});
        }
    }

    return currentRow[lenS1]; // ensures to return the bottom right index
}

//iterates through the dictionary in order to spell check and return candidates
vector<pair<string, int>> spellCheck(const string& word, const vector<string>& dictionary) {
    vector<pair<string, int>> suggestions;

    for (const string& correctWord : dictionary) {
        int distance = wagnerFischer(word, correctWord);
        suggestions.push_back(make_pair(correctWord, distance));
        //adds the suggestion to vector
    }

//using the algorithm class I am able to sort from smallest to largest distance
    sort(suggestions.begin(), suggestions.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second < b.second;
    });

    return suggestions;
}

int main() {
    vector<string> dictionary = loadDictionary("google-10000-english.txt");

    //where the user input goes
    string misspelledWord = "whoool";

    vector<pair<string, int>> suggestions = spellCheck(misspelledWord, dictionary);

    cout << "Top candidates based on '" << misspelledWord << "':" << endl;
    // use the minimum for amount of candidates and the suggestions tuple
    for (int i = 0; i < min(15, static_cast<int>(suggestions.size())); ++i) {
        cout << suggestions[i].first << " Distance: " << suggestions[i].second << endl;
    }

    return 0;
}
