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
    std::make_shared<HTree>(2,90, std::make_shared<HTree>(3,6),
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


  auto trees = std::vector<HForest::tree_ptr_t>{tree1};


  auto forest = std::make_shared<HForest>(trees); // contains roots: 17
  assert(forest->size() == 1);
  std::cout << "Initalized forest with 1 tree.\n";

  forest->add_tree(tree2); // contains roots: 17, 100
  assert(forest->size() == 2);

  forest->add_tree(tree3); // contains roots: 17, 100, 1
  assert(forest->size() == 3);
  std::cout << "Added two more trees.\n";

  auto lowest = forest->pop_tree(); // contains roots: 17, 100
  assert(lowest->get_value() == tree3->get_value());
  assert(forest->size() == 2);
  std::cout << "Removed lowest-value tree. Value was: " << lowest->get_value() << '\n';

  forest->add_tree(tree4); // contains roots: 17, 100, 33
  assert(forest->size() == 3);

  forest->add_tree(tree5); // contains roots: 17, 100, 33, 1
  assert(forest->size() == 4);

  forest->add_tree(tree3); // contains roots: 17, 100, 33, 1, 1
  assert(forest->size() == 5);
  std::cout << "Added three more trees.\n";

  auto newLowest = forest->pop_tree(); // contains roots: 17, 100, 33, 1
  assert(newLowest->get_value() == tree3->get_value()); // could also be tree5->get_value()
  assert(forest->size() == 4);
  std::cout << "Removed lowest-value tree. Value was: " << newLowest->get_value() << '\n';

  auto secLowest = forest->pop_tree(); // contains roots: 17, 100, 33
  assert(secLowest->get_value() == tree5->get_value()); // could also be tree3->get_value()
  assert(forest->size() == 3);
  std::cout << "Removed lowest-value tree. Value was: " << secLowest->get_value() << '\n';

  auto middle = forest->pop_tree(); // contains roots: 100, 33
  assert(middle->get_value() == tree1->get_value());
  assert(forest->size() == 2);
  std::cout << "Removed lowest-value tree. Value was: " << middle->get_value() << '\n';

  auto secHighest = forest->pop_tree(); // contains roots: 100
  assert(secHighest->get_value() == tree4->get_value());
  assert(forest->size() == 1);
  std::cout << "Removed lowest-value tree. Value was: " << secHighest->get_value() << '\n';

  auto highest = forest->pop_tree(); // empty
  assert(highest->get_value() == tree2->get_value());
  assert(forest->size() == 0);
  std::cout << "Removed lowest-value tree. Value was: " << highest->get_value() << '\n';
  std::cout << "Forest is empty.\n\n";

  /////////////////////////////////////////////////////////

  auto forest2 = std::make_shared<HForest>();
  assert(forest2->size() == 0);
  std::cout << "Initalized empty forest.\n";

  forest2->add_tree(tree3);
  forest2->add_tree(tree3);
  assert(forest2->size() == 2);
  std::cout << "Added two trees to second forest.\n";

  auto lowest2 = forest2->pop_tree();
  assert(lowest2->get_value() == tree3->get_value());
  assert(forest2->size() == 1);
  std::cout << "Removed lowest-value tree. Value was: " << lowest2->get_value() << '\n';

  auto highest2 = forest2->pop_tree();
  assert(highest2->get_value() == tree3->get_value());
  assert(forest2->size() == 0);
  std::cout << "Removed lowest-value tree. Value was: " << highest2->get_value() << '\n';
  std::cout << "Forest is empty.\n\n";

}

int main(){
  test_hforest();
  std::cout << "\nPassed all tests.\n";
  return 0;
}
