/*
 * test_tree: A simple unit test for the Tree data structure.
 */

#include "htree.hh"
#include <cassert>

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
  HTree::path_t noPath;
  //auto pointNoPath(std::make_unique<HTree::possible_path_t>(noPath));
  assert(*(root->path_to(126)) == noPath); //HTree::path_t({ }));

  HTree::path_t lrPath;
  //auto pointLRPath(std::make_unique<HTree::possible_path_t>(lrPath));
  lrPath.push_back(HTree::Direction(0));
  lrPath.push_back(HTree::Direction(1));
  assert(*(root->path_to(3)) == lrPath); //HTree::path_t({0,1}));

  HTree::path_t llPath;
  //auto pointLLPath(std::make_unique<HTree::possible_path_t>(llPath));
  llPath.push_back(HTree::Direction(0));
  llPath.push_back(HTree::Direction(0));
  assert(*(root->path_to(12)) == llPath); //HTree::path_t({0,0}));
  assert(root->path_to(54) == nullptr);

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
