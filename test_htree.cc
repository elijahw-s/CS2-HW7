/*
 * test_tree: A simple unit test for the Tree data structure.
 */

#include "htree.hh"
#include <cassert>
#include <iostream>

using namespace std;

// Create an elaborate example test tree:
HTree::tree_ptr_t create_test_tree()
{
  return
    make_shared<HTree>(126, 1, make_shared<HTree>(-5, 2,
      make_shared<HTree>(12, 3),
      make_shared<HTree>(6, 4,
        make_shared<HTree>(9, 5))),
    make_shared<HTree>(12, 6,
      make_shared<HTree>(3, 7)));
}

void test_htree(const HTree::tree_ptr_t root)
{
  std::unique_ptr<HTree::path_t> noPath(new HTree::path_t());
  auto testNoPath = root->path_to(126);
  assert(*testNoPath == *noPath); //HTree::path_t({ }));
  std::cout << "passed no path test" << '\n';

  std::unique_ptr<HTree::path_t> lrPath(new HTree::path_t({HTree::Direction(0), HTree::Direction(1)}));
  std::cout << "made lr path sample" << '\n';
  //lrPath->push_back(HTree::Direction(0));
  //lrPath->push_back(HTree::Direction(1));
  auto testLRPath = root->path_to(3);
  std::cout << "found path to 3" << '\n';
  if (testLRPath->empty()){
    std::cout << "empty\n"; // returns empty, then segmentation fault coming from somewhere
  } else {
    for (auto const &i: *testLRPath) {
      if (i == HTree::Direction(0)){
        std::cout << "0" << std::endl;
      } else{
        std::cout << "1" << std::endl;
      }
    }
  }
  //assert(*testLRPath == *lrPath); //HTree::path_t({0,1}));
  //std::cout << "passed lr path test" << '\n';

  std::unique_ptr<HTree::path_t> llPath(new HTree::path_t());
  llPath->push_back(HTree::Direction(0));
  llPath->push_back(HTree::Direction(0));
  auto testLLPath = root->path_to(12);
  for (auto const &i: *testLLPath) {
    if (i == HTree::Direction(0)){
      std::cout << "0" << std::endl;
    } else{
      std::cout << "1" << std::endl;
    }
  }
  //assert(*testLLPath == *llPath); //HTree::path_t({0,0}));
  //std::cout << "passed ll path test" << '\n';
  //assert(root->path_to(54) == nullptr);

  //assert(node_at(root, "")->key_ == 126);
  //assert(node_at(root, "L")->key_ == -5);
  //assert(node_at(root, "LL")->key_ == 12);
  //assert(node_at(root, "LLL") == nullptr);
  //assert(node_at(root, "LLR") == nullptr);
  //assert(node_at(root, "LR")->key_ == 6);
  //assert(node_at(root, "LRL")->key_ == 9);
  //assert(node_at(root, "LLRL") == nullptr);
  //assert(node_at(root, "LLRR") == nullptr);
  //assert(node_at(root, "LRR") == nullptr);
  //assert(node_at(root, "RR") == nullptr);
  //assert(node_at(root, "x") == nullptr);
  // should I have some sort of node_at???
}

int main()
{
  auto root = create_test_tree();
  test_htree(root);

  return 0;
}
