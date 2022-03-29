#include "hforest.hh"
#include <cassert>
#include <iostream>
#include <vector>

HTree::tree_ptr_t create_test_tree_1()
{
  return
    std::make_shared<HTree>(126, 17, std::make_shared<HTree>(-5, 2,
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
    std::make_shared<HTree>(4,1, std::make_shared<HTree>(6,0,
      std::make_shared<HTree>(5,10), std::make_shared<HTree>(32,-45)),
      std::make_shared<HTree>(4,12,
      nullptr, std::make_shared<HTree>(33,12)));
}

HTree::tree_ptr_t create_test_tree_4()
{
  return
    std::make_shared<HTree>(4,33);
}

HTree::tree_ptr_t create_test_tree_5()
{
  return
    std::make_shared<HTree>(5,1);
}


void test_hforest(){
  auto tree1 = create_test_tree_1(); // root value == 17
  auto tree2 = create_test_tree_2(); // root value == 100
  auto tree3 = create_test_tree_3(); // root value == 1
  auto tree4 = create_test_tree_4(); // root value == 33
  auto tree5 = create_test_tree_5(); // root value == 1


  auto trees = std::vector<HForest::tree_ptr_t>{tree1}; // not initalizing well, no matching constructor for initialization of...
  //HForest::tree_vector_t trees = HForest::tree_vector_t{tree1};

  auto forest = std::make_shared<HForest>(trees); // contains roots: 17
  assert(forest->size() == 1);

  forest->add_tree(tree2); // contains roots: 17, 100
  assert(forest->size() == 2);

  forest->add_tree(tree3); // contains roots: 17, 100, 1
  assert(forest->size() == 3);


  auto lowest = forest->pop_tree(); // contains roots: 17, 100
  assert(lowest->get_value() == tree3->get_value());
  assert(forest->size() == 2);

  forest->add_tree(tree4); // contains roots: 17, 100, 33
  assert(forest->size() == 3);

  forest->add_tree(tree5); // contains roots: 17, 100, 33, 1
  assert(forest->size() == 4);

  forest->add_tree(tree3); // contains roots: 17, 100, 33, 1, 1
  assert(forest->size() == 5);

  auto newLowest = forest->pop_tree(); // contains roots: 17, 100, 33, 1
  assert(newLowest->get_value() == tree3->get_value()); // could also be tree5->get_value()
  assert(forest->size() == 4);

  auto secLowest = forest->pop_tree(); // contains roots: 17, 100, 33
  assert(secLowest->get_value() == tree5->get_value()); // could also be tree3->get_value()
  assert(forest->size() == 3);

  auto middle = forest->pop_tree(); // contains roots: 100, 33
  assert(middle->get_value() == tree1->get_value());
  assert(forest->size() == 2);

  auto secHighest = forest->pop_tree(); // contains roots: 100
  assert(secHighest->get_value() == tree4->get_value());
  assert(forest->size() == 1);

  auto highest = forest->pop_tree(); // empty
  assert(highest->get_value() == tree2->get_value());
  assert(forest->size() == 0);
}

int main(){
  test_hforest();
  return 0;
}
