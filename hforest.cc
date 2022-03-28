#include "hforest.hh"
#include <memory>
#include <algorithm>


bool static compare_trees(HForest::tree_ptr_t t1, HForest::tree_ptr_t t2){
    return t1->get_value() < t2->get_value();
}

HForest::HForest(tree_vector_t trees){
  vec_ = trees;
  std::make_heap(trees.begin(), trees.end(), compare_trees);
}


void HForest::add_tree(tree_ptr_t tree){
  vec_.push_back(tree);
  std::make_heap(vec_.begin(), vec_.end(), compare_trees);
}

HForest::tree_ptr_t
HForest::pop_tree(){
  std::make_heap(vec_.begin(), vec_.end(), compare_trees);
  std::pop_heap(vec_.begin(), vec_.end(), compare_trees); // error: no member named 'pop_heap' in 'std::vector<std::shared_ptr<const HTree>>'
  tree_ptr_t smallest = vec_.back(); // I think this is where the later problems are coming from??
  vec_.pop_back();
  return smallest;  // error: no viable conversion from returned value of type 'HForest::tree_ptr_t' (aka 'shared_ptr<const HTree>') to function return type 'int'
  // smallest thinks it's an int, but the contents of the vector are tree_ptr_t, confusing!
}


int HForest::size() const{
    return vec_.size();
}
