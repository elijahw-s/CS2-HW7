#pragma once

#include "htree.cc"

class HForest {
  public:

    using tree_ptr_t = std::shared_ptr<const HTree>;
    using forest_ptr_t = std::shared_ptr<HForest>;
    using vector_t = std::vector<tree_ptr_t>;
    using vector_ptr_t = std::shared_ptr<vector_t>;

    // construct a forest
    HForest(vector_ptr_t trees);

    // returns number of trees in forest
    int size() const;

    // add a tree to the forest
    void add_tree(tree_ptr_t tree);

    // remove lowest-root tree, return pointer
    tree_ptr_t pop_tree();


  private:
    bool static compare_trees(tree_ptr_t t1, tree_ptr_t t2){
        return t1->get_value() < t2->get_value();
    }
    vector_ptr_t vec_;
};