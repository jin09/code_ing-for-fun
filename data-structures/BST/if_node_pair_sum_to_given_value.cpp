/*    Given a binary tree, check whether there are two nodes in it whose sum equals a given value.

      Approach 1(time O(n), space O(n) ) : inorder of BST to array then http://www.geeksforgeeks.org/write-a-c-program-that-given-a-set-a-of-n-numbers-and-another-number-x-determines-whether-or-not-there-exist-two-elements-in-s-whose-sum-is-exactly-x/

      Approach 2 (time O(n), space O(n) ): convert the BST to doubly linked list then use the same algo as above used for arrays
      
      Approach 3 : try the stack solution (look for alfo online)
*/

#include<bits/stdc++.h>
using namespace std;

class BST;

class binaryTreeNode{
public:
    int data;
    binaryTreeNode* left;
    binaryTreeNode* right;
    binaryTreeNode* parent;

    binaryTreeNode(int data){
        this->data = data;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   PRETTY PRINT   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

// Find the maximum height of the binary tree
int maxHeight(binaryTreeNode *p) {
  if (!p) return 0;
  int leftHeight = maxHeight(p->left);
  int rightHeight = maxHeight(p->right);
  return (leftHeight > rightHeight) ? leftHeight + 1: rightHeight + 1;
}

// Convert an integer value to string
string intToString(int val) {
  ostringstream ss;
  ss << val;
  return ss.str();
}

// Print the arm branches (eg, /    \ ) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<binaryTreeNode*>& nodesQueue, ostream& out) {
  deque<binaryTreeNode*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel / 2; i++) {
    out << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
    out << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
  }
  out << endl;
}

// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<binaryTreeNode*>& nodesQueue, ostream& out) {
  deque<binaryTreeNode*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
    out << setw(branchLen+2) << ((*iter) ? intToString((*iter)->data) : "");
    out << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
  }
  out << endl;
}

// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<binaryTreeNode*>& nodesQueue, ostream& out) {
  deque<binaryTreeNode*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << ((*iter) ? intToString((*iter)->data) : "");
  }
  out << endl;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void printPretty(binaryTreeNode *root, int level, int indentSpace, ostream& out) {
  int h = maxHeight(root);
  int nodesInThisLevel = 1;

  int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);  // eq of the length of branch for each node of each level
  int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);  // distance between left neighbor node's right arm and right neighbor node's left arm
  int startLen = branchLen + (3-level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)

  deque<binaryTreeNode*> nodesQueue;
  nodesQueue.push_back(root);
  for (int r = 1; r < h; r++) {
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    branchLen = branchLen/2 - 1;
    nodeSpaceLen = nodeSpaceLen/2 + 1;
    startLen = branchLen + (3-level) + indentSpace;
    printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

    for (int i = 0; i < nodesInThisLevel; i++) {
      binaryTreeNode *currNode = nodesQueue.front();
      nodesQueue.pop_front();
      if (currNode) {
	      nodesQueue.push_back(currNode->left);
	      nodesQueue.push_back(currNode->right);
      } else {
        nodesQueue.push_back(NULL);
        nodesQueue.push_back(NULL);
      }
    }
    nodesInThisLevel *= 2;
  }
  printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
  printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  END OF PRETTY PRINT   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

void insertIntoBST(binaryTreeNode*& root, int data){
    if(root == NULL){
        root = new binaryTreeNode(data);
        root->left = NULL;
        root->right = NULL;
        return;
    }
    if(data < root->data){
        insertIntoBST(root->left,data);
    }
    if(data > root->data){
        insertIntoBST(root->right,data);
    }
}

vector <int> vec;

void BSTtovector(binaryTreeNode* root){
    if(root== NULL){
        return ;
    }
    BSTtovector(root->left);
    vec.push_back(root->data);
    BSTtovector(root->right);
}

bool isPairPresent(binaryTreeNode* root , int sum){
    if(root == NULL){
        return false;
    }
    BSTtovector(root);
    int s = vec.size();
    int i = 0;
    int j = s-1;

    while(i < j){

        if(vec[i] + vec[j] == sum){
            return true;
        }
        else if(vec[i] + vec[j] < sum){
            i++;
        }
        else if(vec[i] + vec[j] > sum){
            j--;
        }
    }
    return false;
}

int main(){

binaryTreeNode* root = NULL;
insertIntoBST(root,15);
insertIntoBST(root,10);
insertIntoBST(root,20);
insertIntoBST(root,8);
insertIntoBST(root,12);
insertIntoBST(root,16);
insertIntoBST(root,25);
printPretty(root,3,4,cout);
cout<<endl;
if(isPairPresent(root,33)){
    cout<<"Pair is present with target 33 !!"<<endl;
}
else{
    cout<<"Pair not present !!"<<endl;
}
return 0;
}

