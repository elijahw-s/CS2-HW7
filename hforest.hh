#pragma once

#include "htree.hh"
#include <vector>
#include <iostream>

class HForest {
  public:

    using tree_ptr_t = HTree::tree_ptr_t;
    using forest_ptr_t = std::shared_ptr<HForest>;
    using tree_vector_t = std::vector<tree_ptr_t>;
    //using vector_t = std::shared_ptr<vector_t>;

    // construct a forest
    HForest(tree_vector_t trees = std::vector<tree_ptr_t>{});

    ~HForest()=default;

    // returns number of trees in forest
    int size() const;

    // add a tree to the forest, maintaining heap sorting
    void add_tree(tree_ptr_t tree);

    // remove the tree with the lowest root value, return its pointer
    tree_ptr_t pop_tree();

    void print_forest(){
      for (auto const &i: vec_){
        std::cout << i->get_value()<<"\n";
      }
    };


  private:

    tree_vector_t vec_;
};
