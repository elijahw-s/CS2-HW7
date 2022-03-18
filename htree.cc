/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#include "htree.hh"


// Construct a tree
HTree::HTree(key_t key,
      value_t value,
      tree_ptr_t left,
      tree_ptr_t right)
  :key_(key), value_(value), left_(left), right_(right)
  {
  }

// recursively destroy a tree
//HTree::~HTree(){
//  this->get_child(HTree::Direction(0)).~HTree();
//  this->get_child(HTree::Direction(1)).~HTree();
//  delete this;
//}

// return the key of the current node
HTree::key_t HTree::get_key() const{
  return this->key_;
}

// return the value of the current node
HTree::value_t HTree::get_value() const{
  return this->value_;
}

// get the child indicated by the directions
HTree::tree_ptr_t HTree::get_child(Direction dir) const{
  if (dir == HTree::Direction(0)){
    return this->left_;
  } else if (dir == HTree::Direction(1)){
    return this->right_;
  } else {
    return nullptr;
  }
}

// Return an optional list of directions from root to a node of a given key.
// If key not contained in this tree, returns nullptr
HTree::possible_path_t
HTree::path_to(key_t key) const
{
  //if (!this){ //??? how to check if not *this
    //return nullptr;
  //}
  auto pointPath = std::make_unique<path_t>(new path_t());
  if (this->get_key() == key){
    //HTree::possible_path_t pointPath = path;
    return pointPath;
  }

  //const auto testLeft = this->get_child(HTree::Direction(0)).path_to(key);
  //if (!*testLeft.empty()){
    //path.push_back(HTree::Direction(0));
    //path.push_back(*testLeft);
    //auto pointPath(std::make_unique<HTree::possible_path_t>(path));
    //HTree::possible_path_t pointPath = path;
    //return pointPath;
  //}

  //const auto testRight = this->get_child(HTree::Direction(1)).path_to(key);
  //if (*testRight.empty()){
    //return nullptr;
  //} else {
    //path.push_back(HTree::Direction(1));
    //path.push_back(*testRight);
    //auto pointPath(std::make_unique<HTree::possible_path_t>(path));
    //HTree::possible_path_t pointPath = path;
    //return pointPath;
  }

}
