#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
//flagger that identifies incorrect words from a dictionary of 10,000 words
void stringToVector(vector<string> &list, string input){
    string temp;
    char c;
    for(int i=0;i<input.length();i++){
        c=input[i];
        if(c==' '){
            list.push_back(temp);
            if(i<input.length()-1){
                temp="";
            }
        }
        else{
            temp+=c;
        }
    }
    list.push_back(temp);
}

bool isOneEdit(string s1, string s2){
    int count=0;
    const char *c1=s1.c_str(), *c2=s2.c_str();
    if(s1==s2){
        return false;
    }
    //check if the differnce of letters is valid, more than one fails the edit distance
    else if (abs(int(s1.length() - s2.length())) > 1){
        return false;
    }
    //main comparison
    else{
        while (*c1 != '\0' && *c2 != '\0')
        {
            //check for base case
            if(*c1==*c2){
                c1++;
                c2++;
            }
            else{
                //if vary by one letter then possible edit is to only remove a character
                //deletion or insertion
                count++;
                if (count > 1)
                    return false;
                if (s1.length() == s2.length()) {//if strings are of equal length, substitution
                    c1++;
                    c2++;
                } 
                else if (s1.length() < s2.length()) {
                    c2++;
                } 
                else {
                    c1++;
                }
            }
            
        }
        // Handle case where one string is longer
        if (*c1 != '\0' || *c2 != '\0') {
            count++;
        }
        return count == 1;
        //count cannot equal 0 as first if statement checks for equal strings
    }
}

int main() {
    //variable declaration
    ifstream dictionary;
    vector<string> list;
    string input, word;
    bool found=false;
    //opening file
    dictionary.open("google-10000-english.txt");
    //get input from user
    getline(cin,input);

    //put the words in a vector format to easily access
    stringToVector(list,input);

    //check every word in dictionary
    for(int i=0; i<list.size();i++){
        while(dictionary){
            dictionary>>word;
            if(word!=list.at(i)){
                found=false;
            }
            else{
                found=true;
                //break used to help compile times
                break;
            }
        }
        //starts back at the beginning of a file
        dictionary.close();
        dictionary.open("google-10000-english.txt");

        if(found==false){
        cout<<"Possible corrections for '"<<list.at(i)<<"'"<<endl;
        while(dictionary){
            dictionary>>word;
            if(isOneEdit(list.at(i), word)){
                cout<<word<<endl;
            }
        }
        dictionary.close();
        dictionary.open("google-10000-english.txt");
        }
    }
    
    return 0;
}