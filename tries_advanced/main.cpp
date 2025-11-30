#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node{
    Node* arr[26];
    int cp;
    int ew;
public:
    Node(){
        for(int i=0;i<26;i++) arr[i] = nullptr;
        cp = 0;
        ew = 0;
    }

    bool checkExist(char ch){
        return arr[ch-97];
    }   

    void incrementPrefix(){
        cp++;
    }

    void incrementEnd(){
        ew++;
    }

    void decrementPrefix(){
        cp--;
    }

    void decrementEnd(){
        ew--;
    }

    int getPrefix(){
        return cp;
    }

    int getEnd(){
        return ew;
    }

    void put(char ch){
        Node* node = new Node();
        arr[ch-97] = node;
    }

    Node* get(char ch){
        return arr[ch-97];
    }

};

class Trie{
    Node* root;
public:
    
    Trie(){
        root = new Node();
    }

    void insert(string word){
        Node* curr = root;
        for(int i=0;i<word.length();i++){
            if(!curr->checkExist(word[i])){
                curr->put(word[i]);
            }
            curr = curr->get(word[i]);
            curr->incrementPrefix();
        }
        curr->incrementEnd();
    }

    int countPrefix(string word){
        Node* curr = root;
        for(int i=0;i<word.length();i++){
            if(curr->checkExist(word[i])){
                curr = curr->get(word[i]);
            }
            else return 0;
        }
        return curr->getPrefix();
    }

    int countMatches(string word){
        Node* curr = root;
        for(int i=0;i<word.length();i++){
            if(curr->checkExist(word[i])){
                curr = curr->get(word[i]);
            }
            else return 0;
        }
        return curr->getEnd();
    }

    void erase(string word){
        Node* curr = root;
        for(int i=0;i<word.length();i++){
            if(curr->checkExist(word[i])){
                curr = curr->get(word[i]);
                curr->decrementPrefix();
            }
            else return;
        }
        curr->decrementEnd();
    }
};



vector<string> run_operations(vector<vector<string>>& operations, bool debug=false){
    vector<string> results;
    Trie* trie;
    for(auto operation : operations){
        if(operation[0]=="trie"){
            trie = new Trie();
            if(debug) cout<<"Trie Initialized"<<endl;
            results.push_back("null");
        }
        else if(operation[0]=="insert"){
            trie->insert(operation[1]);
            if(debug) cout<<"Inserted: "<<operation[1]<<endl;
            results.push_back("null");
        }
        else if(operation[0]=="countPrefix"){
            int count = trie->countPrefix(operation[1]);
            if(debug)  cout<<"Count Prefix "<<operation[1]<<": "<<count<<endl;
            results.push_back(to_string(count));
        }
        else if(operation[0]=="countMatches"){
            int count = trie->countMatches(operation[1]);
            if(debug) cout<<"Count Matches "<<operation[1]<<": "<<count<<endl;
            results.push_back(to_string(count));
        }
        else if(operation[0]=="erase"){
            trie->erase(operation[1]);
            if(debug) cout<<"Erased: "<<operation[1]<<endl;
            results.push_back("null");
        }
    }
    return results;
}

int run_code(){
    vector<vector<string>> operations = {
        {"trie",""},
        {"insert","apple"},
        {"countMatches","apple"},
        {"insert","app"},
        {"countPrefix","app"},
        {"erase","apple"},
        {"countPrefix","app"},
    };

    vector<string> expected = {
        "null",
        "null",
        "1",
        "null",
        "2",
        "null",
        "1",
    };
    vector<string> results = run_operations(operations, false);
    if(expected.size() != 0){
        (expected == results) ? cout<<"✅ Test Case Passed!"<<endl : cout<<"❌ Test Case Failed!"<<endl;
    }
    cout<<"Results:  ";
    for(auto result:results){
        cout<<result<<" ";
    }
    cout<<endl<<"Expected: ";
    for(auto result:expected){
        cout<<result<<" ";
    }
    cout<<endl;
    return 0;
}

int main(){
    run_code();
}