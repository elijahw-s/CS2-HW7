/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#include "htree.hh"


// Construct a tree
HTree::HTree(key_t key,
      value_t value,
      tree_ptr_t left = nullptr,
      tree_ptr_t right = nullptr);
  :key_(key), value_(value), left_(left = nullptr), right_(right = nullptr)
  {
  }

// recursively destroy a tree
HTree::~HTree(){
  if(*this){
    *this->left_.~HTree();
    *this->right_.~HTree();
    delete *this;
  }
}

// return the key of the current node
HTree::key_t HTree::get_key() const{
  if(*this){
    return *this->key_;
  } // what do if not *this?
}

// return the value of the current node
HTree::value_t HTree::get_value() const;{
  if (*this){
    return *this->value_
  }
}

// get the child indicated by the directions
HTree::tree_ptr_t HTree::get_child(Direction dir) const{
  if (dir == 0){
    return *this->left_;
  } else if (dir == 1){
    return *this->right_
  }
}

// Return an optional list of directions from root to a node of a given key.
// If key not contained in this tree, returns nullptr
HTree::possible_path_t
HTree::path_to(key_t key) const
{
  if (*this == nullptr){ //??? how to check if not *this
    return nullptr;
  }

  HTree::path_t path;
  auto pointPath(std::make_unique<HTree::possible_path_t>(path)); // will this point to the right thing if path grows?
  if (this.get_key() == key){
    return pointPath;
  }

  const auto testLeft = this.get_child(HTree::Direction(0)).path_to(key);
  if (!*testLeft.empty()){
    path.push_back(HTree::Direction(0));
    path.push_back(*testLeft);
    return pointPath;
  }

  const auto testRight = *this->_right.path_to(key);
  if (*testRight.empty()){
    return nullptr;
  } else {
    path.push_back(HTree::Direction(1));
    path.push_back(*testRight);
    return *pointPath
  }

}
