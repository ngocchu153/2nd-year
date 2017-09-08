//  Created by Ngoc on 12/1/16.
//  Copyright © 2016 Ngoc. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;
class Node {
public:
    string word;
    int count;
    Node* pLeft;
    Node* pRight;
    Node() {
        pLeft = pRight = NULL;
        count = 1;
    }
};

class BST {
public: Node* root;
    BST() { root = NULL; }
    bool isEmpty() {
        return root==NULL;
    }
    Node* CreatNode(string word);
    void InsertNode(Node* &root,string word);
    void insertWordsIntoBST(string str);
    void exportToFile(string fileName, Node *root);

};

Node* BST::CreatNode(string word) {
    Node* newNode = new Node;
    newNode->word = word;
    return newNode;
}

//void BST::InsertNode(string word) {
//    Node* newNode = CreatNode(word);
//    if (!root) {
//        root = newNode;
//        return;
//    }
//    Node* curr = root;
//    Node* prev = new Node;
//    while (curr) {
//        prev = curr;
//        if (word < curr->word) {
//            curr = curr->pLeft;
//        }
//        else if (word > curr->word) {
//            curr = curr->pRight;
//        }
//        else if (word == curr->word) {
//            curr->count++ ;
//            return;
//        }
//    }
//    if (prev != NULL) {
//        if (prev->word > word)
//            prev->pLeft = newNode;
//        else if(prev->word < word)
//            prev->pRight = newNode;
//    }
//}

void BST::InsertNode(Node* &root, string word) {
    if (!root)
        root = CreatNode(word);
    else {
        if (word < root->word) {
            InsertNode(root->pLeft, word);
        }
        if (word > root->word) {
            InsertNode(root->pRight, word);
        }
        if (root->word == word) {
            root->count++;
            return;
        }
    }
    return;
}

string toLower(string str) {
    for(int i=0;i<str.length();i++) {
        if(str[i]>='A'&&str[i]<='Z') {
            str[i]+=32;
        }
    }
    return str;
}

string standardize(string str) {
    str=toLower(str);
    long length = str.length();
    for(long i=0;i<=length;i++) {
        if(str[i]=='.') {
            if((str[i+1] >= 'a' && str[i+1]<='z')||(str[i+1] >= '0' && str[i+1]<='9'))
                continue;
            else str[i]=NULL;
        }
        if(str[i]==' ')
            str[i]='\n';
        else if (str[i] == '(' || str[i]==')'|| str[i]=='<'|| str[i]=='>'|| str[i]=='['|| str[i]==']'|| str[i]==39||
                 str[i]==34|| str[i]==','|| str[i]==';'|| str[i]==':')
            str[i]=NULL;
        else if ((str[i]=='-'&&str[i+1]=='-'))
            str[i]=str[i+1]=NULL;
    }
    return str;
}

void BST::insertWordsIntoBST(string str) {
    string temp;
    long length = str.length();
    for(long i=0; i<=length; i++ ) {
        if(str[i]==0) continue;
        else if(str[i]=='\n') {
            if(!temp.empty())
                InsertNode(root, temp);
            temp.erase();
            continue;
        }
        else if(((str[i]>='a' && str[i]<='z') || str[i]=='.' || (str[i] >= '0' && str[i] <= '9')
                 || str[i] == '-'))
            temp+=str[i];
    }
    InsertNode(root,temp);
}

void recursiveExportFunc(fstream &f, Node* node) {
    if (node == NULL)
        return;
    recursiveExportFunc(f, node->pLeft);
    string count = to_string(node->count);
    f << left << setw(25)<<node->word << setw(8) << count << endl;
    recursiveExportFunc(f, node->pRight);
}

void exportToFile(string fileName,fstream &f,Node *node) {
    f.open("output.txt", ios::out);
    f << left << setw(25) << "Word/Number" << setw(8) << "TimesAppear" << endl << endl;
    recursiveExportFunc(f, node);
    f.close();
}

void getData(string fileName, fstream &f, string &data,string &line) {
    f.open(fileName, ios::in);
    
    getline(f, line);
    data+=line;
    while (!f.eof()) {
        getline(f, line);
        if(!line.empty())
            data += ' ' + line;
    }
    
    f.close();
}

int main() {
    fstream f;
    string data;
    string line;
    string fileName;
    
    cout<<"Enter your file name: ";
    cin>>fileName;
    getData(fileName, f, data, line);
    
    BST T;
    
    T.insertWordsIntoBST(standardize(data));
    exportToFile("output.txt",f, T.root);
    
    return 0;
}
