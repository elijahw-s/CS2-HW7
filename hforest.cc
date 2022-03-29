#include "hforest.hh"
#include <memory>
#include <algorithm>


bool static compare_trees(HForest::tree_ptr_t t1, HForest::tree_ptr_t t2){
    return t1->get_value() > t2->get_value();
}

HForest::HForest(tree_vector_t trees){
  vec_ = trees;
  std::make_heap(trees.begin(), trees.end(), compare_trees); // sorts vector into min-heap
}


void HForest::add_tree(tree_ptr_t tree){
  vec_.push_back(tree); // add new tree to back
  std::make_heap(vec_.begin(), vec_.end(), compare_trees); // re-sort heap, now with the new tree
}

HForest::tree_ptr_t
HForest::pop_tree(){
  std::pop_heap(vec_.begin(), vec_.end(), compare_trees); // moves first (smallest) element of the heap to back
  tree_ptr_t smallest = vec_.back(); // save last (smallest) element of the heap
  vec_.pop_back(); // remove the last (smallest) element of the heap
  return smallest;
}


int HForest::size() const{
    return vec_.size(); // standard vector size function
}
