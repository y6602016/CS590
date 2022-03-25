
#include "bs_tree.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
bs_tree::bs_tree()
{
}

bs_tree::~bs_tree()
{
}

void bs_tree::insert(int key, bs_tree_i_info &t_info)
{
  bs_tree_node *z;

  z = new bs_tree_node;
  z->key = key;

  insert(z, t_info);
}

void bs_tree::insert(bs_tree_node *z, bs_tree_i_info &t_info)
{
  // use two pointers: x and y to run the insert algo
  bs_tree_node *x;
  bs_tree_node *y;

  // initialize y = NULL and x = root
  y = NULL;
  x = T_root;

  // traverse x to the correct position to insert z
  while (x != NULL)
  {
    y = x;
    if (z->key < x->key)
    { // z val < x val, go left
      x = x->left;
    }
    else if (z->key > x->key)
    { // z val > x val, go left
      x = x->right;
    }
    else
    { // z val = x val, return
      return;
    }
  }

  // now x = NULL and y is at the position of being the parent of z
  z->p = y;

  if (y == NULL)
  { // if y = NULL, it's an empty tree, set z as the root
    T_root = z;
  }
  else
  {
    if (z->key < y->key)
    { // if z val < y val, then z is y's left child
      y->left = z;
    }
    else
    {
      y->right = z; // otherwise z is y's right child
    }
  }
}

// TODO: modified inorder tree walk method to save the
// sorted numbers in the first argument: int* array.
// question 2
int bs_tree::convert(int *array, int n)
{
  return n;
}
