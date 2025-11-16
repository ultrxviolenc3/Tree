#include <iostream>
#include <queue>

using namespace std;

class Tree;

class Node{
int val;
Node *left,*right,*parent;
Node (int x) : val(x), left(nullptr), right(nullptr), parent(nullptr){}
friend class Tree;
};

class Tree{

Node *root;
public:
Tree() : root(nullptr){}
bool search(int x){
    
Node *current=root;
while(current){

if(x==current->val) return true;
if(x<current->val) current=current->left;
else current=current->right;
}
return false;
}

bool add(int x){

Node *temp=new(nothrow) Node(x);
if(!temp){

    return false; //exit
}

if(root==nullptr)
{
 root=temp;
return true;
}
Node *current=root;
while(current){ /// while(1)
if(x<=current->val)
{
if(current->left!=nullptr) current=current->left;
else{
    
    current->left=temp;
    temp->parent=current;
return true;
}
}
else {
if(current->right!=nullptr) current=current->right;
else{
current->right=temp;
temp->parent=current;
return true;

}

}



}
}



};