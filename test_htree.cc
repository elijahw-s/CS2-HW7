/*
 * test_tree: A simple unit test for the Tree data structure.
 */

#include "htree.hh"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// Creates a tree that only consists of a root with no children
HTree::tree_ptr_t 
create_test_tree_single()
{
  return                                //          126
      make_shared<HTree>(126, 1);       //         /   |
}                                       //

// Creates a tree with paths to both the left and the right of the root
HTree::tree_ptr_t 
create_test_tree_balanced()           //                      126
{                                     //                     /  |
  return                              //                   -5   12
      make_shared<HTree>(126, 1,      //                 /  |   /
      make_shared<HTree>(-5, 2,       //               12   6  3
      make_shared<HTree>(12, 3),      //                   /
      make_shared<HTree>(6, 4,        //                  9
      make_shared<HTree>(9, 5))),     //
      make_shared<HTree>(12, 6,       //
      make_shared<HTree>(3, 7)));     //
}

// Creates a tree that only contains paths to the left.
HTree::tree_ptr_t 
create_test_tree_left()               //                      126
{                                     //                     /  |
  return                              //                   -5
      make_shared<HTree>(126, 1,      //                   /
      make_shared<HTree>(-5, 2,       //                 12
      make_shared<HTree>(12, 3,       //                 / 
      make_shared<HTree>(6, 4,        //                6
      make_shared<HTree>(9, 5,        //               /
      make_shared<HTree>(3, 6))))));  //              9
}                                     //             /
                                      //            3

// Creates a tree that only contains paths to the right
HTree::tree_ptr_t 
create_test_tree_right()                    //                126
{                                           //               /  |  
  return                                    //                  -5
      make_shared<HTree>(126, 1, nullptr ,  //                   |
      make_shared<HTree>(-5, 2, nullptr ,   //                   12
      make_shared<HTree>(12, 3, nullptr ,   //                    |
      make_shared<HTree>(6, 4, nullptr ,    //                     6
      make_shared<HTree>(9, 5, nullptr ,    //                     |
      make_shared<HTree>(3, 6))))));        //                      9
}                                           //                      |
                                            //                       3

/*
This function allows for the list of directions stored as a path 
to be converted into a string containing 'L' and 'R'
*/
std::string
path_decode(HTree::possible_path_t &path)
{
  std::string str;
  for (std::list<HTree::Direction>::iterator it = path->begin(); it != path->end(); ++it){
    if (*it == HTree::Direction(0)){ // Checks if HTree::Direction == LEFT
      str.append("L");
    } else if (*it == HTree::Direction(1)){ // or if HTree::Direction == RIGHT
      str.append("R");
    } 
  }
  return str; // Returns a string of of the path
}

/*
All of the testing functions feature basically identical tests just modified for the different sample trees
so I'm going to only comment one of them because I really dont feel like commenting ~300 lines of code
*/

// Test functions for the balanced tree
void test_htree_balanced(const HTree::tree_ptr_t root)
{
  std::unique_ptr<HTree::path_t> noPath(new HTree::path_t({ }));  // Creates a unique pointer pointing to an empty list
  std::string str_out; // Initializes the str_out string
  auto testNoPath = root->path_to(126); // Uses the path to function to generate a list of directions to the node with key=126
  assert(*testNoPath == *noPath);   // Asserts that the returned path from root->path_to(126) is the same as the known path

  std::unique_ptr<HTree::path_t> rlPath(new HTree::path_t({HTree::Direction(1), HTree::Direction(0)})); // Unique pointer to list {'RIGHT', 'LEFT'}
  auto testRLPath = root->path_to(3);   // Returns list of directions to node with key=3
  assert(*testRLPath == *rlPath); //Asserts returned path and known path are equal

  std::unique_ptr<HTree::path_t> llPath(new HTree::path_t({HTree::Direction(0), HTree::Direction(0)}));
  auto testLLPath = root->path_to(12);
  assert(*testLLPath == *llPath);

  std::unique_ptr<HTree::path_t> lrlPath(new HTree::path_t({HTree::Direction(0), HTree::Direction(1), HTree::Direction(0)}));
  auto testLRLPath = root->path_to(9);
  assert(*testLRLPath == *lrlPath);

  auto rPath = nullptr;
  auto testRPath = root->path_to(7); // Tests a random key to make sure that it returns nullptr because the key isn't in the tree
  assert(testRPath == rPath); // Asserts that the returned key is the same as the key of known value

  HTree::key_t key_test = -5; // Creates a type key_t that is equal to the known key
  HTree::value_t value_test = 2;  // Creates a type value_t that is equal to the known value
  HTree::tree_ptr_t test_1 = root->get_child(HTree::Direction(0));  // Returns a tree note at position 'L'
  HTree::key_t test_1_key = test_1->get_key();  // Uses get_key() to return the key of the returned tree node
  HTree::value_t test_1_value = test_1->get_value();  // Uses get_value() to return the value of the returned tree node
  assert(key_test == test_1_key); // Asserts the the returned key is the same as the known key
  assert(value_test == test_1_value); // Asserts that the returned value is the same as the known value
  
  key_test = 9;
  value_test = 5;
  HTree::tree_ptr_t test_2 = root->get_child(HTree::Direction(0))->get_child(HTree::Direction(1))->get_child(HTree::Direction(0));
  HTree::key_t test_2_key = test_2->get_key();
  HTree::value_t test_2_value = test_2->get_value();
  assert(key_test == test_2_key);
  assert(value_test == test_2_value);

  key_test = 3;
  value_test = 7;
  HTree::tree_ptr_t test_3 = root->get_child(HTree::Direction(1))->get_child(HTree::Direction(0));
  HTree::key_t test_3_key = test_3->get_key();
  HTree::value_t test_3_value = test_3->get_value();
  assert(key_test == test_3_key);
  assert(value_test == test_3_value);
}

// Test functions for the single node tree
void test_htree_single(const HTree::tree_ptr_t root)
{
  std::unique_ptr<HTree::path_t> noPath(new HTree::path_t({ }));
  std::string str_out;
  auto testNoPath = root->path_to(126);
  assert(*testNoPath == *noPath);

  auto lPath = nullptr; // Creates a nullptr to compare against because both children of the single node are nullptrs
  auto testLPath = root->path_to(-5); // Returns the path_to(-5) which should be nullptr because the path doesn't exist
  assert(testLPath == lPath); // Asserts that the returned path is in fact a nullptr

  auto rPath = nullptr; // Same as above check except
  auto testRPath = root->path_to(12);
  assert(testRPath == rPath);

  HTree::key_t key_test = 126;  // Tests the get_key() and get_value() functions on the root because it is the only node in the tree
  HTree::value_t value_test = 1;
  HTree::tree_ptr_t test_1 = root;
  HTree::key_t test_1_key = test_1->get_key();
  HTree::value_t test_1_value = test_1->get_value();
  assert(key_test == test_1_key); // Asserts the returned key is the same as the known key
  assert(value_test == test_1_value); // Asserts the returned value is the same as the known value
  
  HTree::tree_ptr_t test_2 = root->get_child(HTree::Direction(0));  // Returns the 'tree' to the left of the single node
  assert(test_2 == nullptr); // Asserts that the returned tree is a nullptr because the tree doesn't exist
  

  HTree::tree_ptr_t test_3 = root->get_child(HTree::Direction(1)); // Same as above
  assert(test_3 == nullptr);
}

// Test functions for the all left tree
void test_htree_left(const HTree::tree_ptr_t root)
{
  std::unique_ptr<HTree::path_t> noPath(new HTree::path_t({ }));
  std::string str_out;
  auto testNoPath = root->path_to(126);
  assert(*testNoPath == *noPath); 

  std::unique_ptr<HTree::path_t> lPath(new HTree::path_t({HTree::Direction(0)}));
  auto testLPath = root->path_to(-5);
  assert(*testLPath == *lPath); 

  std::unique_ptr<HTree::path_t> llPath(new HTree::path_t({HTree::Direction(0), HTree::Direction(0)}));
  auto testLLPath = root->path_to(12);
  assert(*testLLPath == *llPath);

  std::unique_ptr<HTree::path_t> lllPath(new HTree::path_t({HTree::Direction(0), HTree::Direction(0), HTree::Direction(0)}));
  auto testLLLPath = root->path_to(6);
  assert(*testLLLPath == *lllPath);

  std::unique_ptr<HTree::path_t> lllllPath(new HTree::path_t({HTree::Direction(0), HTree::Direction(0), HTree::Direction(0), HTree::Direction(0), HTree::Direction(0)}));
  auto testLLLLLPath = root->path_to(3);
  assert(*testLLLLLPath == *lllllPath);

  auto rPath = nullptr;
  auto testRPath = root->path_to(7); // Tests a random key to make sure that it returns nullptr because the key isn't in the tree
  assert(testRPath == rPath); // Asserts that the returned key is the same as the key of known value

  HTree::key_t key_test = -5;
  HTree::value_t value_test = 2;
  HTree::tree_ptr_t test_1 = root->get_child(HTree::Direction(0));
  HTree::key_t test_1_key = test_1->get_key();
  HTree::value_t test_1_value = test_1->get_value();
  assert(key_test == test_1_key);
  assert(value_test == test_1_value);
  
  key_test = 12;
  value_test = 3;
  HTree::tree_ptr_t test_2 = root->get_child(HTree::Direction(0))->get_child(HTree::Direction(0));
  HTree::key_t test_2_key = test_2->get_key();
  HTree::value_t test_2_value = test_2->get_value();
  assert(key_test == test_2_key);
  assert(value_test == test_2_value);

  key_test = 9;
  value_test = 5;
  HTree::tree_ptr_t test_3 = root->get_child(HTree::Direction(0))->get_child(HTree::Direction(0))->get_child(HTree::Direction(0))->get_child(HTree::Direction(0));
  HTree::key_t test_3_key = test_3->get_key();
  HTree::value_t test_3_value = test_3->get_value();
  assert(key_test == test_3_key);
  assert(value_test == test_3_value);

  HTree::tree_ptr_t test_4 = root->get_child(HTree::Direction(1));
  assert(test_4 == nullptr); // Asserts that returning a tree to the right returns a nullptr because all the trees are to the left
}

// Test functions for the all right tree
void test_htree_right(const HTree::tree_ptr_t root)
{
  std::unique_ptr<HTree::path_t> noPath(new HTree::path_t({ }));
  std::string str_out;
  auto testNoPath = root->path_to(126);
  assert(*testNoPath == *noPath); 

  std::unique_ptr<HTree::path_t> rPath(new HTree::path_t({HTree::Direction(1)}));
  auto testRPath = root->path_to(-5);
  assert(*testRPath == *rPath); 

  std::unique_ptr<HTree::path_t> rrPath(new HTree::path_t({HTree::Direction(1), HTree::Direction(1)}));
  auto testRRPath = root->path_to(12);
  assert(*testRRPath == *rrPath);

  std::unique_ptr<HTree::path_t> rrrPath(new HTree::path_t({HTree::Direction(1), HTree::Direction(1), HTree::Direction(1)}));
  auto testRRRPath = root->path_to(6);
  assert(*testRRRPath == *rrrPath);

  std::unique_ptr<HTree::path_t> rrrrrPath(new HTree::path_t({HTree::Direction(1), HTree::Direction(1), HTree::Direction(1), HTree::Direction(1), HTree::Direction(1)}));
  auto testRRRRRPath = root->path_to(3);
  assert(*testRRRRRPath == *rrrrrPath);

  auto lPath = nullptr;
  auto testLPath = root->path_to(7);
  assert(testLPath == lPath);

  HTree::key_t key_test = -5;
  HTree::value_t value_test = 2;
  HTree::tree_ptr_t test_1 = root->get_child(HTree::Direction(1));
  HTree::key_t test_1_key = test_1->get_key();
  HTree::value_t test_1_value = test_1->get_value();
  assert(key_test == test_1_key);
  assert(value_test == test_1_value);
  
  key_test = 12;
  value_test = 3;
  HTree::tree_ptr_t test_2 = root->get_child(HTree::Direction(1))->get_child(HTree::Direction(1));
  HTree::key_t test_2_key = test_2->get_key();
  HTree::value_t test_2_value = test_2->get_value();
  assert(key_test == test_2_key);
  assert(value_test == test_2_value);

  key_test = 9;
  value_test = 5;
  HTree::tree_ptr_t test_3 = root->get_child(HTree::Direction(1))->get_child(HTree::Direction(1))->get_child(HTree::Direction(1))->get_child(HTree::Direction(1));
  HTree::key_t test_3_key = test_3->get_key();
  HTree::value_t test_3_value = test_3->get_value();
  assert(key_test == test_3_key);
  assert(value_test == test_3_value);

  HTree::tree_ptr_t test_4 = root->get_child(HTree::Direction(0));
  assert(test_4 == nullptr);
}

int main()
{
  auto root_balanced = create_test_tree_balanced();
  auto root_single = create_test_tree_single();
  auto root_left = create_test_tree_left();
  auto root_right = create_test_tree_right();
  test_htree_balanced(root_balanced);
  test_htree_single(root_single);
  test_htree_left(root_left);
  test_htree_right(root_right);
  std::cout << "All tests passed.";


  return 0;
}
