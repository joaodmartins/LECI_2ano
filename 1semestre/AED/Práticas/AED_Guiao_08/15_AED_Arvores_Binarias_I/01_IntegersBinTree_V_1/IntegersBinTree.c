//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, November 2023, November 2024
//
// Adapted from an old example (2003, 2020)
//
// Integers Binary Tree --- FIRST VERSION --- INCOMPLETE
//
// SOME FUNCTIONS ARE INCOMPLETE on IntegersBinTree.c
//

#include "IntegersBinTree.h"

#include <assert.h>
#include <stdlib.h>

struct _TreeNode {
  ItemType item;
  struct _TreeNode* left;
  struct _TreeNode* right;
};

Tree* TreeCreate(void) { return NULL; }

void TreeDestroy(Tree** pRoot) {
  Tree* root = *pRoot;

  if (root == NULL) return;

  TreeDestroy(&(root->left));

  TreeDestroy(&(root->right));

  free(root);

  *pRoot = NULL;
}

int TreeIsEmpty(const Tree* root) { return root == NULL; }

int TreeEquals(const Tree* root1, const Tree* root2) {
  if (root1 == NULL && root2 == NULL) {
    return 1;
  }
  if (root1 == NULL || root2 == NULL) {
    return 0;
  }
  if (root1->item != root2->item) {
    return 0;
  }
  return TreeEquals(root1->left, root2->left) &&
         TreeEquals(root1->right, root2->right);
}

int TreeMirrors(const Tree* root1, const Tree* root2) {
  if (root1 == NULL && root2 == NULL) {
    return 1;  // Both trees are empty, so they are mirrors
  }
  if (root1 == NULL || root2 == NULL) {
    return 0;  // One tree is empty and the other is not, so they are not mirrors
  }
  // Check if the roots are the same and the left subtree of one is the mirror of the right subtree of the other
  return (root1->item == root2->item) &&
         TreeMirrors(root1->left, root2->right) &&
         TreeMirrors(root1->right, root2->left);
}

int TreeGetNumberOfNodes(const Tree* root) {
  if (root == NULL) return 0;

  return 1 + TreeGetNumberOfNodes(root->left) +
         TreeGetNumberOfNodes(root->right);
}

int TreeGetHeight(const Tree* root) {
  if (root == NULL) return -1;

  int heightLeftSubTree = TreeGetHeight(root->left);

  int heightRightSubTree = TreeGetHeight(root->right);

  if (heightLeftSubTree > heightRightSubTree) {
    return 1 + heightLeftSubTree;
  }

  return 1 + heightRightSubTree;
}

void TreeTraverseInPREOrder(Tree* root, void (*function)(ItemType* p)) {
  if (root == NULL) return;

  function(&(root->item));

  TreeTraverseInPREOrder(root->left, function);

  TreeTraverseInPREOrder(root->right, function);
}

void TreeTraverseINOrder(Tree* root, void (*function)(ItemType* p)) {
  if (root == NULL) return;

  TreeTraverseINOrder(root->left, function);
  function(&(root->item));
  TreeTraverseINOrder(root->right, function);
}

void TreeTraverseInPOSTOrder(Tree* root, void (*function)(ItemType* p)) {
  if (root == NULL) return;

  TreeTraverseInPOSTOrder(root->left, function);
  TreeTraverseInPOSTOrder(root->right, function);
  function(&(root->item));
}

// ...

int TreeContains(const Tree* root, const ItemType item) {
  if (root == NULL) return 0;  // Item not found
  if (root->item == item) return 1;  // Item found

  // Recursively search in the left and right subtrees
  return TreeContains(root->left, item) || TreeContains(root->right, item);
}

int TreeAdd(Tree** pRoot, const ItemType item) {
  if (*pRoot == NULL) {  // Found the right place to add the item
    *pRoot = (Tree*)malloc(sizeof(Tree));
    if (*pRoot == NULL) return 0;  // Memory allocation failed

    (*pRoot)->item = item;
    (*pRoot)->left = NULL;
    (*pRoot)->right = NULL;
    return 1;
  }

  // Insert item into left or right subtree depending on its value
  if (item < (*pRoot)->item) {
    return TreeAdd(&(*pRoot)->left, item);
  } else if (item > (*pRoot)->item) {
    return TreeAdd(&(*pRoot)->right, item);
  }

  return 0;
}

int TreeRemove(Tree** pRoot, const ItemType item) {
  if (*pRoot == NULL) return 0;  // Item not found

  if (item < (*pRoot)->item) {
    return TreeRemove(&(*pRoot)->left, item);
  } else if (item > (*pRoot)->item) {
    return TreeRemove(&(*pRoot)->right, item);
  } else {
    // Node with only one child or no child
    if ((*pRoot)->left == NULL) {
      Tree* temp = *pRoot;
      *pRoot = (*pRoot)->right;
      free(temp);
    } else if ((*pRoot)->right == NULL) {
      Tree* temp = *pRoot;
      *pRoot = (*pRoot)->left;
      free(temp);
    } else {
      // Node with two children: get the inorder successor
      Tree* temp = (*pRoot)->right;
      while (temp && temp->left != NULL) temp = temp->left;

      // Copy the inorder successor's content to this node
      (*pRoot)->item = temp->item;

      // Delete the inorder successor
      return TreeRemove(&(*pRoot)->right, temp->item);
    }
    return 1;
  }
}

// ...

// JUST FOR RUNNING EXAMPLES - REMOVE FROM THE INTERFACE

Tree* createExampleTree(void) {
  // SHOULD NEVER BE DONE LIKE THIS !!!???!!!

  int numNodes = 8;

  Tree* nodes[numNodes];

  for (int i = 0; i < numNodes; i++) {
    nodes[i] = (Tree*)malloc(sizeof(Tree));
    nodes[i]->item = i + 1;
    nodes[i]->left = nodes[i]->right = NULL;
  }

  nodes[3]->left = nodes[7];

  nodes[1]->left = nodes[3];
  nodes[1]->right = nodes[4];

  nodes[2]->left = nodes[5];
  nodes[2]->right = nodes[6];

  nodes[0]->left = nodes[1];
  nodes[0]->right = nodes[2];

  return nodes[0];
}