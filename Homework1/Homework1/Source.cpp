#include<iostream>

using namespace std;


struct Node {
     int data;
     Node* left;
     Node* right;
};

//function to count number of nodes in tree
int countNodes(Node* root) {
     int count = 0;
     queue < Node* > q;
     Node* temp;
     q.push(root);
     while (!q.empty()) {
          temp = q.front(); //store front node of queue
          q.pop(); //remove front node as it will be processed
          count++;
          //store left and right subtree of current node
          if (temp -> left)
               q.push(temp -> left);
          if (temp -> right)
               q.push(temp -> right);
     }
     return count;
}

//function to count number of leaves in tree
int countLeaves(Node* root) {
     int count = 0;
     queue < Node* > q;
     Node* temp;
     q.push(root);
     while (!q.empty()) {
          temp = q.front(); //store front node of queue
          q.pop(); //remove front node as it will be processed
          //check whether it is a root node
          if (temp -> left == NULL && temp - > right == NULL)
               count++;
          //store left and right subtree of current node
          if (temp -> left)
               q.push(temp -> left);
          if (temp -> right)
               q.push(temp -> right);
     }
     return count;
}

//function to count number of full nodes in tree
int countFullNodes(Node* root) {
     int count = 0;
     queue < Node* > q;
     Node* temp;
     q.push(root);
     while (!q.empty()) {
          temp = q.front(); //store front node of queue
          q.pop(); //remove front node as it will be processed
          if (temp->left != NULL && temp->right != NULL)
               count++;
               //store left and right subtree of current node
               if (temp -> left)
                    q.push(temp -> left);
          if (temp -> right)
               q.push(temp -> right);
     }
     return count;
}