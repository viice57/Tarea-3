#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/treemap.h"

typedef struct TreeNode TreeNode;

struct TreeNode {
  TreePair * pair;
  TreeNode * left;
  TreeNode * right;
  TreeNode * parent;
};

struct TreeMap {
  TreeNode * root;
  TreeNode * current;
  int (*lower_than) (void * key1, void * key2);
};

int is_equal_tree(TreeMap* tree, void * key1, void * key2){
  if(tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0) return 1;
  else return 0;
}


TreeNode * createTreeNode(void * key, void * value) {
  TreeNode * new = (TreeNode *) malloc(sizeof(TreeNode));
  if (!new) return NULL;
  new->pair = (TreePair *) malloc(sizeof(TreePair));
  new->pair->key = key;
  new->pair->value = value;
  new->parent = new->left = new->right = NULL;
  
  return new;
}

TreeMap * createTreeMap(int (*lower_than) (void * key1, void * key2)) {
  TreeMap * new = (TreeMap *) malloc(sizeof(TreeMap));
  new->root = NULL;
  new->current = NULL;
  new->lower_than = lower_than;
  
  return new;
}

void insertTreeMap(TreeMap * tree, void * key, void * value) {
  tree->current = tree->root;

  while(tree->current) {
    if(is_equal_tree(tree, key, tree->current->pair->key)) return;
    else {
      if(tree->lower_than(tree->current->pair->key, key)) {
        if(!tree->current->right) break;
        tree->current = tree->current->right;
      } else {
        if(!tree->current->left) break;
        tree->current = tree->current->left;
      }
    }
  }
  
  if(tree->lower_than(tree->current->pair->key, key)) {
    tree->current->right = createTreeNode(key, value);
    tree->current->right->parent = tree->current;
    tree->current = tree->current->right;
  } else {
    tree->current->left = createTreeNode(key, value);
    tree->current->left->parent = tree->current;
    tree->current = tree->current->left;
  }
}

TreeNode * minimum(TreeNode * x) {
  while(x->left) x = x->left;
  return x;
}

void removeNode(TreeMap * tree, TreeNode * node) {
  TreeNode *parentNode = node->parent;

  if(!node->left  && !node->right) {
    if(tree->lower_than(parentNode->pair->key, node->pair->key)) {
      parentNode->right = NULL; 
    } else if(tree->lower_than(node->pair->key, parentNode->pair->key)) {
      parentNode->left = NULL; 
    }
  } else if((node->left && !node->right) || (!node->left && node->right)) {
    if(!node->left) {
      if(tree->lower_than(parentNode->pair->key, node->pair->key)) {
        parentNode->right = node->right; 
      } else if(tree->lower_than(node->pair->key, parentNode->pair->key)) {
        parentNode->left = node->right; 
      }
      
      node->right->parent = parentNode; 
    }
    
    if(!node->right) {
      if(tree->lower_than(parentNode->pair->key, node->pair->key)) {
        parentNode->right = node->left; 
      } else if(tree->lower_than(node->pair->key, parentNode->pair->key)) {
        parentNode->left = node->left;
      }
      
      node->left->parent = parentNode;
    }
    
    free(node);
  } else {
    TreeNode * min = minimum(node->right);
    node->pair->key = min->pair->key;
    node->pair->value = min->pair->value;
    
    removeNode(tree, min);
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
  if(!tree || !tree->root) return;

  if(!searchTreeMap(tree, key)) return;
  TreeNode* node = tree->current;
  removeNode(tree, node);

}

TreePair * searchTreeMap(TreeMap * tree, void* key) {
  if(!tree || !tree->root) return NULL;
  
  tree->current = tree->root;
  while(tree->current) {
      if (is_equal_tree(tree, tree->current->pair->key, key)) return tree->current->pair;
    
      if(tree->lower_than(tree->current->pair->key, key)) tree->current = tree->current->right;
      else tree->current = tree->current->left;
  }
  
  return NULL;
}

TreePair * upperBound(TreeMap * tree, void* key) {
  TreeNode * ub_node = NULL;
  tree->current = tree->root;

  while(tree->current) {
    if(tree->lower_than(tree->current->pair->key, key)) {
      if(!tree->current->right) break;
      tree->current = tree->current->right;
    } else {
      if(!tree->current->left) break;
      tree->current = tree->current->left;
      ub_node = tree->current->parent;
    }
  }

  if(tree->lower_than(tree->current->pair->key, key) && ub_node) return ub_node->pair;
  if(!ub_node) return NULL;

  return tree->current->pair;
}

TreePair * firstTreeMap(TreeMap * tree) {
  if(!tree) return NULL;

  TreeNode * firstNode = minimum(tree->root);
  return firstNode->pair;
}

TreePair * nextTreeMap(TreeMap * tree) {
  if (!tree) return NULL;
  
  TreeNode *aux = tree->current;
  TreeNode *parentNode = aux->parent;
    
  if(aux->right) tree->current = minimum(aux->right);
  else {
    
    while(parentNode) {
      if(tree->lower_than(parentNode->pair->key, aux->pair->key)) parentNode = parentNode->parent;
      else break;
    }
    
    if(!parentNode) return NULL;
    tree->current = parentNode;
  }
  
  return tree->current->pair;
}