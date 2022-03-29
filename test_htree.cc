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
  std::unique_ptr<HTree::path_t> noPath(new HTree::path_t({ }));
  auto testNoPath = root->path_to(126);
  assert(*testNoPath == *noPath); //HTree::path_t({ }));
  std::cout << "passed no path test" << '\n';

  std::unique_ptr<HTree::path_t> rlPath(new HTree::path_t({HTree::Direction(1), HTree::Direction(0)}));
  auto testRLPath = root->path_to(3);
  std::cout << "found path to 3" << '\n';
  if (!testRLPath){
    std::cout << "RL path is empty \n";
  }
  assert(*testRLPath == *rlPath);
  std::cout << "passed lr path test" << '\n';

  //HTree::possible_path_t llPath;
  //*llPath = new HTree::path_t();
  //std::unique_ptr<HTree::path_t> llPath(new HTree::path_t());
  //llPath->push_back(HTree::Direction(0));
  //llPath->push_back(HTree::Direction(0));// should remove extra direction 0
  auto testLLPath = root->path_to(12);
  //assert(*testLLPath == *llPath); //HTree::path_t({0,0}));
  //std::cout << "passed ll path test" << '\n';
  //assert(root->path_to(54) == nullptr);
}

int main()
{
  auto root = create_test_tree();
  test_htree(root);

  return 0;
}
