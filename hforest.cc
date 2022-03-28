#include "hforest.hh"
#include <memory>
#include <algorithm>
#include <vector>

HForest::HForest(vector_ptr_t trees){
  this->vec_ = trees;
  std::make_heap(*trees->begin(), *trees->end(), HForest::compare_trees);
}


void HForest::add_tree(tree_ptr_t tree){
  this->vec_->push_back(tree);
  std::make_heap(this->vec_->begin(), this->vec_->end(), HForest::compare_trees);
}

HForest::tree_ptr_t
HForest::pop_tree(){
  std::make_heap(this->vec_->begin(), this->vec_->end(), HForest::compare_trees);
  //this->vec_->pop_heap(this->vec_->begin(), this->vec_->end(), HForest::compare_trees); // error: no member named 'pop_heap' in 'std::vector<std::shared_ptr<const HTree>>'
  tree_ptr_t smallest = this->vec_->back(); // I think this is where the later problems are coming from??
  this->vec_->pop_back();
  return smallest;  // error: no viable conversion from returned value of type 'HForest::tree_ptr_t' (aka 'shared_ptr<const HTree>') to function return type 'int'
  // smallest thinks it's an int, but the contents of the vector are tree_ptr_t, confusing!
}


int HForest::size() const{
    return this->vec_->size();
}
