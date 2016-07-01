#include<bits/stdc++.h>
using namespace std;

class binaryTreeNode{
public:
    int data;
    binaryTreeNode* left;
    binaryTreeNode* right;

    binaryTreeNode(int data){
        this->data = data;
        left = NULL;
        right = NULL;
    }

    ~binaryTreeNode(){
        if(left!=NULL)
            delete left;
        if(right!=NULL)
            delete right;
    }
};



binaryTreeNode* takeInputByLevel(){

    int data;
    cout<<"Enter data of the node : ";
    cin>>data;
    binaryTreeNode* root = new binaryTreeNode(data);

    queue<binaryTreeNode*> q;
    q.push(root);

    while(!q.empty()){
        binaryTreeNode* temp = q.front();
        q.pop();
        int leftData;
        int rightData;
        cout<<"Enter the left data of the node with value "<<temp->data<<" : ";
        cin>>leftData;
        if(leftData!=-1){
            temp->left = new binaryTreeNode(leftData);
            q.push(temp->left);
        }
        cout<<"Enter the right data of the node with value "<<temp->data<<" : ";
        cin>>rightData;
        if(rightData!=-1){
            temp->right = new binaryTreeNode(rightData);
            q.push(temp->right);
        }
    }

    return root;
}

void printPreOrder(binaryTreeNode* root){
    if(root==NULL){
        return ;
    }
    cout<<root->data<<"-->";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

int removeLeafNodes(binaryTreeNode*& root){
    if(root==NULL){
        return -1;
    }
    int left = removeLeafNodes(root->left);
    int right = removeLeafNodes(root->right);

    if(left == 1){
        delete root->left;
        root->left = NULL;
    }
    if(right == 1){
        delete root->right;
        root->right = NULL;
    }
    if(left== -1 && right == -1){
        return 1;
    }
    else{
        return 2;
    }

}

int main(){

binaryTreeNode * root1 = NULL;
root1 = takeInputByLevel();
printPreOrder(root1);
cout<<endl;
cout<<"removing leaf nodes from the tree !"<<endl;
removeLeafNodes(root1);
printPreOrder(root1);
return 0;
}
