# CS2-HW7

To build the program, simply use the included Makefile. The Makefile also includes a copy command to move the files over to patty.

**HTree:**

In addition to the required public functions, we also included a private function to print something of possible_path_t type and a private helper function for the path_to function.

- **Constructor:** Initalizes key, value, left, and right with given parameters. If no left or right is passed, it uses nullptr by default.
- **Destructor:** Left as default. Since no functions exist to set the left and right values, trees must be constructed using nested constructors. Only a tree's root is in the stack, so only the root must be deleted.
- **Getters:** Functions are defined to get a tree element's key, value, and children. The get_key and get_value functions simply return the relevant integer. The get_children function takes a direction parameter and returns the left or right child accordingly. If the child does not exist or an invalid direction is passed, the function returns nullptr.
- **print_path:** If the path passed to the function is not empty, the function will iterate over the path and print the directions in order. If the path is empty, the function will simply print "empty". This function was used for debugging, but is also useful for test_htree.
- **path_to:** Recurses through the tree to find a path to a node with the given key. If the key is not in the tree, it returns nullptr. The function first checks if the root of the tree matches the key it's searching for. If it does, it will return an empty path. If not, it will call path_help.
- **path_help:** Takes a key and a path as inputs. First, it checks if the current node has the key it's searching for and returns the path if it does. If not, it calls itself down the left child, provided the child exists. If the correct node is somewhere in the left path, it will add the left direction indicator to the front of the path and return. If it isn't down the left path, the program does the same process on the right path. If it isn't down the right, the program returns an empty list, which is converted to nullptr by path_to.

**HForest**

We decided to use a standard library vector of tree pointers to structure our forest. For the internal structure of the forest, we used the make_heap function with a less-than comparison passed as a parameter to sort the trees in a min-heap.

- **Constructor:** Initalizes the vec_ as a pointer to a vector of tree_ptr_t type entries, then calls make_heap with a less-than function to sort the vector for easier searches.
- **Destructor:** Left as default since shared_ptr and std::vector automatically deallocate memory.
- **size:** Calls the size fuction on the forest's vector and returns the result.
- **pop_tree:** This function uses pop_heap to push the tree with the lowest root value to the back of the vector. Then, it saves the tree in a seperate variable, removes the element, then returns the variable.
- **add_tree:** This function appends a tree pointer to the forest vector then uses make_heap to re-sort.
- **compare_trees:** Private static function used to sort heap into min-heap.

**test_htree**

We decided to use the structure of the basic tree testing file that Eitan provided on Slack, edited to work with the new encapsulation. We also added a single-element tree, a left-only tree, and a right-only tree.

**test_hforest**
We built three tree-constructor functions, each with a different value at the root. The forest initalizes with one of the trees, then the other two are added, with size checked after each addition. Then the trees are popped off one-by-one, with the forest's size checked each time.
