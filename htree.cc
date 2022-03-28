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

// recursively destroy a tree
HTree::~HTree(){
  //this->get_child(HTree::Direction(0)).~HTree();
  //this->get_child(HTree::Direction(1)).~HTree();
  delete this;
}

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

void HTree::print_path(possible_path_t pointPath) const{
  std::cout << "The path is: ";
  if (pointPath->empty()){
    std::cout << "empty"; // returns empty, then segmentation fault coming from somewhere
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


//HTree::possible_path_t HTree::path_help(key_t key, possible_path_t pointPath) const {

//  if (this->key_ == key){
    // initalize point path here
//    return pointPath;
//  }

//  if (this->get_child(Direction(0))){
//    auto leftTest = this->get_child(Direction(0))->path_help(key, move(pointPath));
//    if (leftTest && !leftTest->empty()){
//      leftTest->push_front(Direction(0));
//      return leftTest;
//    }
//  }

//  if (this->get_child(Direction(1))){
//    auto rightTest = this->get_child(Direction(1))->path_help(key, move(pointPath));
//    if (rightTest && rightTest->empty()){
//      return nullptr;
//    } else {
//      rightTest->push_front(Direction(1));
//      return rightTest;
//    }
//  }


//}

HTree::possible_path_t HTree::path_to(key_t key) const{


  if (key_ == key){
    std::unique_ptr<path_t> pointPath(new path_t({ }));
    return pointPath;
  }
  if (get_child(Direction(0))){
    auto leftTest = get_child(Direction(0))->path_to(key);
    if (leftTest && !leftTest->empty()){
      leftTest->push_front(Direction(0));
      return leftTest;
    }
  }

  if (get_child(Direction(1))){
    auto rightTest = this->get_child(Direction(1))->path_to(key);
    if (rightTest && rightTest->empty()){
      return nullptr;
    } else {
      rightTest->push_front(Direction(1));
      return rightTest;
    }
  } else {
    return nullptr; // for key = 3, recurses properly through left, returns empty then goes right. right ends up being nullptr
    // somewhow (even through we check that it isn't) so line 116 generates a segmentation fault
  }


  //possible_path_t foundPath = path_help(key, move(pointPath)); // becomes nullptr when moved? no problems with the first test, where root == key

  //if (foundPath->empty()){
    //return nullptr;
  //}
  //return foundPath;
}
