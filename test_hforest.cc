#include "hforest.hh"
#include <cassert>
#include <iostream>
#include <vector>

HTree::tree_ptr_t create_test_tree_1()
{
  return
    std::make_shared<HTree>(126, 1, std::make_shared<HTree>(-5, 2,
      std::make_shared<HTree>(12, 3),
      std::make_shared<HTree>(6, 4,
        std::make_shared<HTree>(9, 5))),
    std::make_shared<HTree>(12, 6,
      std::make_shared<HTree>(3, 7)));
}

HTree::tree_ptr_t create_test_tree_2()
{
  return
    std::make_shared<HTree>(2,100, std::make_shared<HTree>(3,6),
      std::make_shared<HTree>(4,12));
}

HTree::tree_ptr_t create_test_tree_3()
{
  return
    std::make_shared<HTree>(4,-21, std::make_shared<HTree>(6,0,
      std::make_shared<HTree>(5,10), std::make_shared<HTree>(32,-45)),
      std::make_shared<HTree>(4,12,
      nullptr, std::make_shared<HTree>(33,12)));
}

void test_hforest(){
  auto tree1 = create_test_tree_1(); // root value == 1
  auto tree2 = create_test_tree_2(); // root value == 100
  auto tree3 = create_test_tree_3(); // root value == -21


  auto treesVec(new std::vector<HForest::tree_ptr_t>({tree1})); // not initalizing well, no matching constructor for initialization of...


  auto forest = std::make_shared<HForest>(treesVec);
  assert(forest->size() == 1);

  forest->add_tree(tree2);
  assert(forest->size() == 2);

  forest->add_tree(tree3);
  assert(forest->size() == 3);

  auto lowest = forest->pop_tree();
  assert(lowest->get_value() == tree3->get_value());
  assert(forest->size() == 2);

  auto middle = forest->pop_tree();
  assert(middle->get_value() == tree1->get_value());
  assert(forest->size() == 1);

  auto highest = forest->pop_tree();
  assert(highest->get_value() == tree2->get_value());
  assert(forest->size() == 0);
}

int main(){
  test_hforest();
  return 0;
}
