#include <iostream>
#include <queue>
#include <fstream>
#include <cmath>

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

bool Delete(int x)
{
  Node *current=root;
  
  while(current && current->val!=x){
    if(x<current->val) current=current->left;
    else current=current->right;
  }
  
  if(!current) return false;
  
  if(current->left)
  {
    Node *max=current->left;
    while(max->right) max=max->right;
    current->val=max->val;
    if(max->parent->left==max) max->parent->left=max->left;
    else max->parent->right=max->left;
    if(max->left) max->left->parent=max->parent;
    delete max;
  }
  
  else
  {
    Node *child = current->right;
    if(!current->parent) root=child;
    else if(current->parent->left==current) current->parent->left=child;
    else current->parent->right=child;
    if(child) child->parent=current->parent;
    delete current;
  }
  
  return true;
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

void mermaid(ofstream &f){
  int count=0;
  pair<bool,int> a[200];
  
  for(int i=0;i<200;i++)
  {
	  a[i].first=false;
	  a[i].second=0;
	  }
	  
  if(!root){
    f<<"<div align=\"center\">Дерево пусто</div>"<<endl;
    return;
  }
  
  queue<pair<int,Node*>>q;
  
  q.push({0,root});
  a[0].first=true;
  a[0].second=root->val;

  
  while(!q.empty()){
    int i=q.front().first;
    Node* curr=q.front().second;
    q.pop();
    if(!curr) continue;
    a[i].first=true;
    a[i].second=curr->val;
    if(curr->left)
   { 
	   q.push({ i*2+1,curr->left});
	   count=i*2+1;
	   }
    if(curr->right)
    {
		q.push({i*2+2,curr->right});
		count=i*2+2;
		}
  }

int levels= log2(count+1) + 1 ;
int maxsize=pow(2,levels)-1;

f<<"</div>"<<endl
<<"<div class=\"mermaid\" align=\"center\" style=\"padding-bottom: 10px; margin-bottom: 10px; border-bottom: 2px solid black\">"<<endl
<<"graph TD"<<endl;



for(int i=0;i<maxsize;i++)
{
	int l=i*2+1;
	int r=i*2+2;
	if(a[i].first)
	{
    if(l<maxsize)
    {
    if(a[l].first)
    f<<i<<"[\""<<a[i].second<<"\"]---"<<l<<"[\""<<a[l].second<<"\"]"<<endl;
    else
    f<<i<<"[\""<<a[i].second<<"\"]~~~"<<l<<":::hidden"<<endl;
   }
  if(r<maxsize)
  {
   if(a[r].first)
   f<<i<<"[\""<<a[i].second<<"\"]---"<<r<<"[\""<<a[r].second<<"\"]"<<endl;
   else
   f<<i<<"[\""<<a[i].second<<"\"]~~~"<<r<<":::hidden"<<endl;
   }
  }
}

    f<<"classDef hidden display: none;"<<endl;
    f<<"</div>"<<endl;
 }


};


void start(ofstream &f)
{
f<<"<!DOCTYPE html>"<<endl
    <<"<html lang=\"ru\">"<<endl
    <<"<head>"<<endl
	<<"<meta charset=\"UTF-8\">"<<endl
	<<"<title>Дерево поиска</title>"<<endl
	<<"<script type=\"module\">"<<endl
	<<"import mermaid from \"https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs\";"<<endl
	<<"mermaid.initialize({ startOnLoad: true,"<<endl
	<<"flowchart: {"<<endl
	<<"useMaxWidth: false,"<<endl
	<<"curve: 'linear',"<<endl
	<<"nodeSpacing: 30,"<<endl
	<<"rankSpacing: 30"<<endl
	<<"}"<<endl
	<<"});"<<endl
	
	<<"</script>"<<endl
	<<"</head>"<<endl
	<<"<body>"<<endl;
	}


void end(ofstream &f)
{
f<<"</div>"<<endl	
 <<"</body>"<<endl
 <<"</html>"<<endl;
	
}




int main(){
ofstream f("tree.html");

if(!f.is_open())
{
	cout<<"Oshibka otkritiya fayla"<<endl;
	return -1;
	}
	start(f);
	Tree t;
int com=-1;
cout<<"1-Добавление"<<endl
    <<"2-Поиск"<<endl
    <<"3-Удаление"<<endl
    <<"4-Выход"<<endl;
while(1)
{
	 cin>>com;
switch(com)	
	{
	case 1:	
		{
			int num;
			cout<<"Введите число"<<endl;
			cin>>num;
			f<<"<div align=\"center\">В дерево добавлен элемент "<<num<<"</div>"<<endl;
			cout<<"В дерево добавлен элемент "<<endl;
			t.add(num);
			t.mermaid(f);
			break;
			}
		case 2:
		{ int num;
			cout<<"Введите число"<<endl;
			cin>>num;
			if(t.search(num))
			{cout<<"Найден"<<endl;
				break;
				}
			cout<<"Не найден"<<endl;
			break;
			}
		case 3:
		{ cout<<"Введите число"<<endl;
			int num;
			cin>>num;
			if(t.Delete(num))
			{f<<"<div align=\"center\">В дереве удалён элемент "<<num<<"</div>"<<endl;
				cout<<"Удалён элемент "<<endl;
				t.mermaid(f);
				break;
				}
			f<<"<div align=\"center\">Элемент "<<num<<" не найден"<<"</div>"<<endl;
			cout<<"Элемент не найден"<<endl;
			break;
			}
		
		case 4:
		{ 
			end(f);
			exit(1);
			}
		
		
		default:
		cout<<"Такой команды нет "<<endl;
		
		}
}
	return 0;
	}

