/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#include "htree.hh"
#include <iostream>
#include <memory>


// Construct a tree
HTree::HTree(key_t key,
      value_t value,
      tree_ptr_t left,
      tree_ptr_t right)
  :key_(key), value_(value), left_(left), right_(right)
  {
  }

HTree::~HTree()=default;

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
    return left_;
  } else if (dir == HTree::Direction(1)){
    return right_;
  } else { // there is no child in the direction or an invalid direction was passed
    return nullptr;
  }
}


// Iterate over a path and print the directions stored in it.
// Used heavily in the debugging process.
void HTree::print_path(possible_path_t pointPath) const{
  std::cout << "The path is: ";
  if (pointPath->empty()){
    std::cout << "empty";
  } else {
    for (auto const &i: *pointPath) {
      if (i == HTree::Direction(0)){
        std::cout << "0 ";
      } else{
        std::cout << "1 ";
      }
    }
  }
  std::cout <<"\n";
}

// Return an optional list of directions from root to a node of a given key.
// If key not contained in this tree, returns nullptr
HTree::possible_path_t HTree::path_to(key_t key) const{


  if (key_ == key){
    std::unique_ptr<path_t> pointPath(new path_t({ }));
    return pointPath;
  }
  if (get_child(Direction(0))){
    auto leftTest = get_child(Direction(0))->path_to(key); // will be nullptr if key is not to left
    if (leftTest){
      leftTest->push_front(Direction(0)); // equivalent to return "L" + leftTest in old tree system
      return leftTest;
    }
  }

  if (get_child(Direction(1))){
    auto rightTest = get_child(Direction(1))->path_to(key); // will be nullptr if key is not to right
    if (!rightTest){
      return nullptr; // if we've reached this nullptr, the key is not in the tree
    } else {
      rightTest->push_front(Direction(1));
      return rightTest;
    }
  } else {
    return nullptr;
  }
}
