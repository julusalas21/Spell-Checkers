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
        cout<<list.at(i)<<" is not a word!"<<endl;
        }
    }
    
    return 0;
}