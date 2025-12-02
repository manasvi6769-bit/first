#include<iostream>
#include<vector>
using namespace std;
class Node{
    public:
    int val;
    int height;
    Node* left;
    Node* right;
    
    Node(int val){
        this->val=val;
        left=NULL;
        right=NULL;
        height=0;
    }
};
int height(Node* n){
    if (n==NULL ) return 0;
    return n->height;
}
Node* left_rotate(Node* y){
    Node* x=y->right;
    Node* t1=x->left;
    x->left=y;
    y->right=t1;
    y->height=max(height(y->left),height(y->right));
    x->height=max(height(x->left),height(x->right));
    return x;
}
Node* right_rotate(Node* y){
    Node* x=y->left;
    Node* t2=x->right;
    x->right=y;
    y->left=t2;
    y->height=max(height(y->left),height(y->right));
    x->height=max(height(x->left),height(x->right));
    return x;
}

int get_balance(Node* n){
    int a=height(n->left);
    int b=height(n->right);
    return a-b;
}
void insert(Node* root,int val){
    Node* curr; Node* prev;
    Node* t=new Node(val);
    curr=root;
    prev=NULL;
    vector<Node*> path;
    while(curr){
        prev=curr;
        path.push_back(curr);
        if(curr->val<val){
            curr=curr->left;
        }
        else{
            curr=curr->right;
        }
    }
    if( prev->val<val){
        prev->left=t;
    }
    else {
        prev->right=t;
    }
    for(int i=path.size()-1;i>=0;i--){
        Node* t=path[i];
        t->height=1+max(height(t->left),height(t->right));
        int b=get_balance(path[i]);
        
        if(b>1 && t->left->val>val){//LL
            Node* r=right_rotate(t);
            if(i==0){

            }
            else {
                if(path[i-1]->left=t){
                    path[i-1]->left=r;
                }
                else{
                    path[i-1]->right=r;
                }
            }
        }
        else if(b>1 && t->right->val<val){//LR
            Node* m=left_rotate(t->left);
            t->left=m;
            Node* r=right_rotate(t);
            if(i==0){

            }
            else {
                if(path[i-1]->left=t){
                    path[i-1]->left=r;
                }
                else{
                    path[i-1]->right=r;
                }
            }


        }
        else if(b<-1 && t->left->val>val){//RL
            Node* m=right_rotate(t->right);
            t->right=m;
            Node* r=left_rotate(t);
            if(i==0){

            }
            else {
                if(path[i-1]->left=t){
                    path[i-1]->left=r;
                }
                else{
                    path[i-1]->right=r;
                }
            }

        }
        else if(b<-1 && t->right->val<val){//RR
            Node* r=left_rotate(t);
            if(i==0){

            }
            else {
                if(path[i-1]->left=t){
                    path[i-1]->left=r;
                }
                else{
                    path[i-1]->right=r;
                }
            }
        }
    }
    
}






Node* insert_to(Node* root,int key){
    if(root==NULL){
        return new Node(key);
    }
    else if(root->val>key){
        root->left=insert_to(root->left,key);
    }
    else{
        root->right=insert_to(root->right,key);
    }
    root->height=1+max(height(root->left),height(root->right));
    int b=get_balance(root);
    if(b>1 && get_balance(root->left)>=0){
        //LL
    }
    else if (b>1 && get_balance(root->left)<0){
        //LR
    }
    else if(b<-1 && get_balance(root->right)>=0){
        //RL
    }
    else if(b<-1 && get_balance(root->right)<0){
        //RR
    }
    return root;
}
Node* get_SUCC(Node* n){
    if(n==NULL) return NULL;
    while(n->left){
        n=n->left;
    }
    return n;
}

Node* Delete(Node* root,int key){
    if(root==NULL){
        return NULL;
    }
    else if(root->val<key){
        root->right=Delete(root->right,key);
    }
    else if(root->val>key){
        root->left=Delete(root->left,key);
    }
    else{
        if(root->left && root->right){
            Node* t=get_SUCC(root->right);
            root->val=t->val;
            root->right=Delete(root->right,t->val);
        }
        else{
            if(root->left ){
                return root->right;
            }
            if(root->right){
                return root->left;
            }
            return NULL;
        }
    }
}

int fact(int n) {
    vector<int> a(6);
    a[0]=1;a[1]=1;a[2]=2;a[3]=6,a[4]=24,a[5]=120;
    return a[n];

}


int cn(int n, int l,int prev_node,int* cb){ //mera wala (i think i fixed it this time , the factorial logic can be updated a little)
    if(n==0) return 1;
    //if(n<0) return 0;
    if(n==1 && l==0) return 1;
    if(l==0) {
        return cn(n-1,1,1,cb);
    }
    int child=2*prev_node;
    int end,i,a,b,c;a=1;b=1;c=0;
    if(child<=n) end=child;
    else if(child>n) end=n;
    i=1;
    while(i<=end){
        b=fact(child)/(fact(child-i)* fact(i));
        a=cn(n-i,l+1,i,cb);
        c+=a*b;
        i++;
    }
    return c;

}

#include <bits/stdc++.h>
using namespace std;

// Compute nCr (combination)
long long nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    long long res = 1;
    for (int i = 1; i <= r; i++) {
        res *= n - r + i;
        res /= i;
    }
    return res;
}

// Recursive counting function
long long countTrees(int n, int level, int prevLevelNodes) { //chatgpt wala
    if (n <= 0) return 0;
    if (n == 1) return 1; // only root

    long long total = 0;
    int maxChildren = 2 * prevLevelNodes;        // possible child positions at this level
    int maxHere = min(maxChildren, n - prevLevelNodes); // can’t exceed nodes left

    // Try all possible numbers of nodes in this level
    for (int nodesHere = 1; nodesHere <= maxHere; nodesHere++) {
        // Choose which 'nodesHere' positions (out of 2*prevLevelNodes) are filled
        long long ways = nCr(maxChildren, nodesHere);
        // Recurse for remaining nodes
        ways *= countTrees(n - prevLevelNodes - nodesHere, level + 1, nodesHere);
        total += ways;
    }

    return total;
}
int fact1(int n, int r) {
    int a = 1;
    int j = n;
    for (int i = 1; i <= r; i++) {
        a *= j;
        j--;
    }
    return a;
}

int cn1(int n, int l, int prev_node, int* cb) { //prepelexity wala
    if (n == 0) return 0;
    if (n == 1 && l == 0) return 1;
    if (l == 0) {
        
        cn(n - 1, 1, 1, cb);
        return *cb;
    }

    int child = 2 * prev_node;  // fixed syntax
    int end = (child <= n) ? child : n;

    int i = 1;
    while (i <= end) {
        *cb += 1; //did a little diff (but still wrong)
        cn1(n - i, l + 1, i, cb);
        i++;  // fixed infinite loop
    }

    return *cb;
}


int main() {
    int n = 3;
    int * cb=new int(0);
    cout << "Total possible binary trees for level order of size " << n << ": "
         << cn(n, 0, 0,cb) << endl;
}


