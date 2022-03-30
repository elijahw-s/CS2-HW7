#include <iostream>
#include "tree.hh"
#include <cassert>
// testing on a single-element tree
int single_element(){
  tree_ptr_t single = create_tree(1, 55);

  // path_to
  std::cout << "\n Testing path_to():\n";
  std::string path1 = path_to(single,1);
  assert(path1 == "");
  std::cout << "The path to key 1 is: " << path1 << "\n"; // ""
  std::string path2 = path_to(single,2);
  assert(path2 == "-");
  std::cout << "The path to key 2 is:" << path2 << "\n"; // "-"

  // node_at
  std::cout << "\nTesting node_at()\n";
  tree_ptr_t testNode1 = node_at(single, "");
  assert(testNode1->key_ == 1);
  std::cout << "The key of the node when no path is given is: " << testNode1->key_ << "\n"; // key = 1
  std::cout << "Testing path LRLR gives the error: \n";
  node_at(single, "LRLR"); // path exceeds tree message
  std::cout << "Testing path left right gives the error: \n";
  node_at(single, "left right"); // invalid path message

  destroy_tree(single);
  return 0;
}

// testing on a left-only tree
int left_tree(){
  tree_ptr_t first = create_tree(1, 10);
  tree_ptr_t second = create_tree(2, 20);
  first->left_ = second;
  tree_ptr_t third = create_tree(3, 30);
  second->left_ = third;
  third->left_ = create_tree(4, 40);

  // path_to
  std::cout << "\n Testing path_to():\n";
  std::string path1 = path_to(first,1);
  assert(path1 == "");
  std::cout << "The path to key 1 is: " << path1 << "\n"; // ""
  std::string path2 = path_to(first,3);
  assert(path2 == "LL");
  std::cout << "The path to key 3 is: " << path2 << "\n"; // "LL"
  std::string path3 = path_to(first,5);
  assert(path3 == "-");
  std::cout << "The path to key 5 is: " << path3 << "\n"; // "-"

  // node_at
  std::cout << "\nTesting node_at()\n";
  tree_ptr_t testNode1 = node_at(first, "");
  assert(testNode1->key_ == 1);
  std::cout << "The key of the node when no path is given is: " << testNode1->key_ << "\n"; // key = 1
  tree_ptr_t testNode2 = node_at(first, "LL");
  assert(testNode2->key_ == 3);
  std::cout << "The key of the node when path is LL is: " << testNode2->key_ << "\n"; // key = 3
  std::cout << "Testing path LR gives the error: \n";
  node_at(first, "LR"); // path overshoots tree
  std::cout << "Testing path LLLLLL gives the error: \n";
  node_at(first, "LLLLLL"); // invalid path

  destroy_tree(first);
  return 0;
}

// testing on a right-only tree
int right_tree(){
  tree_ptr_t first = create_tree(1, 10, nullptr, nullptr);
  tree_ptr_t second = create_tree(2, 20, nullptr, nullptr);
  first->right_ = second;
  tree_ptr_t third = create_tree(3, 30, nullptr, nullptr);
  second->right_ = third;
  third->right_ = create_tree(4, 40, nullptr, nullptr);

  // path_to
  std::cout << "\n Testing path_to():\n";
  std::string path1 = path_to(first,1);
  assert(path1 == "");
  std::cout << "The path to key 1 is: " << path1 << "\n"; // ""
  std::string path2 = path_to(first,3);
  assert(path2 == "RR");
  std::cout << "The path to key 3 is: " << path2 << "\n"; // "RR"
  std::string path3 = path_to(first,5);
  assert(path3 == "-");
  std::cout << "The path to key 5 is: " << path3 << "\n"; // "-"
  // node_at
  std::cout << "\nTesting node_at()\n";
  tree_ptr_t testNode1 = node_at(first, "");
  assert(testNode1->key_ == 1);
  std::cout << "The key of the node when no path is given is: " << testNode1->key_ << "\n"; // key = 1
  tree_ptr_t testNode2 = node_at(first, "RR");
  assert(testNode2->key_ == 3);
  std::cout << "The key of the node at RR is: " << testNode2->key_ << "\n"; // key = 3
  std::cout << "Testing path RL gives the error: \n";
  node_at(first, "RL"); // path overshoots tree
  std::cout << "Testing on path RRRRR gives the error: \n";
  node_at(first, "RRRRR"); // path overshoots tree

  destroy_tree(first);
  return 0;
}

// testing on example tree in tree.hh
int hh_tree(){
  tree_ptr_t head = create_tree(126, 1);

  // first level of the tree:
  tree_ptr_t negFive1 = create_tree(-5, 1);
  head->left_ = negFive1;
  tree_ptr_t twelve1 = create_tree(12, 1);
  head->right_ = twelve1;

  // second level of the tree:
  negFive1->left_ = create_tree(12, 1);
  tree_ptr_t six2 = create_tree(6, 1);
  negFive1->right_ = six2;
  twelve1->left_ = create_tree(3, 1);

  //third level of the tree:
  six2->left_ = create_tree(9, 1);

  // path_to
  std::cout << "\nTesting path_to():\n";
  std::string path1 = path_to(head, 9);
  assert(path1 == "LRL");
  std::cout << "The path to key 9 is: " << path1 << "\n"; // "LRL"
  std::string path2 = path_to(head, 3);
  assert(path2 == "RL");
  std::cout << "The path to key 3 is: " << path2 << "\n"; // "RL"
  std::string path3 = path_to(head, 126);
  assert(path3 == "");
  std::cout << "The path to key 126 is: " << path3 << "\n"; // ""
  std::string path4 = path_to(head, 12);
  assert(path4 == "LL");
  std::cout << "The path to key 12 is: " << path4 << "\n"; // "LL"
  std::string path5 = path_to(negFive1, 9);
  assert(path5 == "RL");
  std::cout << "The path to key 9 from -5 is: " << path5 << "\n"; // "RL"
  std::string path6 = path_to(six2, 126);
  assert(path6 == "-");
  std::cout << "The path to key 126 from 6 is: " << path6 << "\n"; // "-"

  // node_at
  std::cout << "\nTesting node_at()\n";
  tree_ptr_t testNode1 = node_at(head, "");
  assert(testNode1->key_ == 126);
  std::cout << "The key of the node when no path is given is: " << testNode1->key_ << "\n"; // key = 126
  tree_ptr_t testNode2 = node_at(head, "RL");
  assert(testNode2->key_ == 3);
  std::cout << "The key of the node at RL is: " << testNode2->key_ << "\n"; // key = 3
  destroy_tree(head);
  return 0;
}

// testing on two trees, combining trees, testing again
int append_trees(){
  tree_ptr_t head1 = create_tree(5,1);
  tree_ptr_t left1 = create_tree(10,1);
  tree_ptr_t right1 = create_tree(15,1);
  head1->left_ = left1;
  head1->right_ = right1;

  // path_to
  std::cout <<"\nTesting path_to() on first tree:\n";
  std::string path1 = path_to(head1,10);
  assert(path1 == "L");
  std::cout << "The path to key 10 is: " << path1 << "\n"; // "L"
  std::string path2 = path_to(head1,15);
  assert(path2 == "R");
  std::cout << "The path to key 15 is: " << path2 << "\n"; // "R"

  // node_at
  std::cout << "\nTesting node_at() on first tree:\n";
  tree_ptr_t testNode1 = node_at(head1,"");
  assert(testNode1->key_ == 5);
  std::cout << "The node when no path is given is: " << testNode1->key_ << "\n"; // key = 5
  tree_ptr_t testNode2 = node_at(head1, "L");
  assert(testNode2->key_ == 10);
  std::cout << "The node at path L is: " << testNode2->key_ << "\n"; // key = 10

  tree_ptr_t head2 = create_tree(2,1);
  tree_ptr_t left2 = create_tree(4,1,head1);
  tree_ptr_t right2 = create_tree(6,1);
  head2->left_ = left2;
  head2->right_ = right2;

  // path_to
  std::cout <<"\nTesting path_to() on new tree:\n";
  std::string path3 = path_to(head2,6);
  assert(path3 == "R");
  std::cout << "The path to key 6 is: " << path3 << "\n"; // "R"
  std::string path4 = path_to(head2,10);
  assert(path4 == "LLL");
  std::cout << "The path to key 10 is: " << path4 << "\n"; // "LLL"

  // node_at
  std::cout << "\nTesting node_at() on new tree:\n";
  tree_ptr_t testNode3 = node_at(head2,"");
  assert(testNode3->key_ == 2);
  std::cout << "The node when no path is given is: " << testNode3->key_ << "\n"; // key = 2
  tree_ptr_t testNode4 = node_at(head1, "L");
  assert(testNode4->key_ == 10);
  std::cout << "The node at path L from old head is: " << testNode4->key_ << "\n"; // key = 10
  tree_ptr_t testNode5 = node_at(head2,"R");
  assert(testNode5->key_ == 6);
  std::cout << "The node at path R from new head is: " << testNode5->key_ << "\n"; // key = 6
  tree_ptr_t testNode6 = node_at(head2, "LLR");
  assert(testNode6->key_ == 15);
  std::cout << "The node at path LLR from new head is: " << testNode6->key_ << "\n"; // key = 15

  destroy_tree(head1);
  left2->left_=nullptr;

  // path_to
  std::cout << "\nTesting path_to() after partial deletion:\n";
  std::string path5 = path_to(head2,6);
  assert(path5 == "R");
  std::cout << "The path to key 6 is: " << path5 << "\n"; // "R"
  std::string path6 = path_to(head2,10);
  assert(path6 == "-");
  std::cout << "The path to key 10 is: " << path6 << "\n"; // "-"

  // node_at
  std::cout << "\nTesting node_at() after partial deletion:\n";
  std::cout << "Testing path LLR gives the error: \n";
  node_at(head2, "LLR"); // path overshoots tree
  tree_ptr_t testNode7 = node_at(head2,"R");
  assert(testNode7->key_ == 6);
  std::cout << "The node at path R is: " << testNode7->key_ << "\n"; // key = 6

  left2->left_ = create_tree(8,1);

  //path_to
  std::cout << "\nTesting path_to() after adding new node:\n";
  std::string path7 = path_to(head2,8);
  assert(path7 == "LL");
  std::cout << "The path to key 8 is: " << path7 << "\n"; // "LL"

  // node_at
  std::cout << "\nTesting node_at() after adding new node:\n";
  tree_ptr_t testNode8 = node_at(head2,"LL");
  assert(testNode8->key_ == 8);
  std::cout << "The node at path LL is: " << testNode8->key_ << "\n"; // key = 8

  destroy_tree(head2);
  return 0;
}

int main(){
  std::cout << "\nTesting on a single element tree.\n";
  single_element();

  std::cout << "\nTesting on a left-only tree.\n";
  left_tree();

  std::cout << "\nTesting on a right-only tree.\n";
  right_tree();

  std::cout << "\nTesting on the tree from tree.hh.\n";
  hh_tree();

  std::cout << "\nTesting on appended and partially deleted trees.\n";
  append_trees();

}
