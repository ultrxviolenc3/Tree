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

    return false; 
}

if(root==nullptr)
{
 root=temp;
return true;
}
Node *current=root;
while(1){ 
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
return false;
}

void show(){
  
  if(!root){
    cout<<"дерево пустое";
    return;
  }
  queue<pair<int,Node*>>q;
  q.push({1,root});
  while(!q.empty()){
    int x=q.front().first;
    Node* curr=q.front().second;
    q.pop();
    cout<<"("<<x<<", "<<curr->val<<") "<<endl;
    if(curr->left)
    q.push({ x*2,curr->left});
    if(curr->right)
    q.push({x*2+1,curr->right});
  }
}


};


int main(){
	 Tree t;
    t.add(10);
    t.add(5);
    t.add(15);
    t.add(12);
    t.add(3);
    t.add(7);
    t.add(20);
	t.show();
	
	if(t.search(7))
	{
		cout<<"Найден"<<endl;
		}
	
	return 0;
	}
