#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node{
    Node* arr[26];
    bool flag;
public:
    Node(){
        for(int i=0;i<26;i++) arr[i]=nullptr;
        flag=false;
    }

    Node* get(char ch){
        return this->arr[ch-97];
    }

    void put(char ch){
        Node* node = new Node();
        this->arr[ch-97] = node;
    }

    bool checkExist(char ch){
        return this->arr[ch-97];
    }

    void markEnd(){
        flag = true;
    } 

    bool getEnd(){
        return flag;
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
        }
        curr->markEnd();
    }

    bool search(string word){
        Node* curr = root;
        for(int i=0;i<word.length();i++){
            if(curr->checkExist(word[i])){
                curr = curr->get(word[i]);
            }
            else return false;
        }
        return curr->getEnd();
    }

    bool startsWith(string word){
        Node* curr = root;
        for(int i=0;i<word.length();i++){
            if(curr->checkExist(word[i])){
                curr = curr->get(word[i]);
            }
            else return false;
        }
        return true;
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
        else if(operation[0]=="search"){
            bool found = trie->search(operation[1]);
            if(debug)  cout<<"Search "<<operation[1]<<": "<<(found ? "Found" : "Not Found")<<endl;
            (found) ? results.push_back("true") : results.push_back("false");
        }
        else if(operation[0]=="startsWith"){
            bool exists = trie->startsWith(operation[1]);
            if(debug) cout<<"Prefix Check "<<operation[1]<<": "<<(exists ? "Exists" : "Does Not Exist")<<endl;
            (exists) ? results.push_back("true") : results.push_back("false");
        }
    }
    return results;
}

int run_code(){
    vector<vector<string>> operations = {
        {"trie",""},
        {"insert","apple"},
        {"search","apple"},
        {"search","app"},
        {"startsWith","app"},
        {"insert","app"},
        {"search","app"}
    };
    vector<string> expected = {
        "null",
        "null",
        "true",
        "false",
        "true",
        "null",
        "true"
    };
    vector<string> results = run_operations(operations, false);
    if(expected.size() != 0){
        (expected == results) ? cout<<"Test Case Passed!"<<endl : cout<<"Test Case Failed!"<<endl;
    }
    cout<<"Results: ";
    for(auto result:results){
        cout<<result<<" ";
    }
    cout<<endl;
    return 0;
}

int main(){
    run_code();
}