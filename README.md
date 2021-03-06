# CSCI 221-HW7

**Elijah Whitlam-Sandler and Mollie Boor**

To build the program, simply use the included Makefile. The Makefile also includes a copy command to move the files over to patty.

**HTree:**

In addition to the required public functions, we also included a private function to print something of possible_path_t type and a private helper function for the path_to function.

- **Constructor:** Initalizes key, value, left, and right with given parameters. If no left or right is passed, it uses nullptr by default.
- **Destructor:** Left as default. All of the pointers in HTree are either in the heap or manage their own deallocation.
- **Getters:** Functions are defined to get a tree element's key, value, and children. The get_key and get_value functions simply return the relevant integer. The get_children function takes a direction parameter and returns the left or right child accordingly. If the child does not exist or an invalid direction is passed, the function returns nullptr.
- **path_to:** Recurses through the tree to find a path to a node with the given key. If the key is not in the tree, it returns nullptr. The function first checks if the current node is has the same key as what it's looking for. If it's found the correct node, it will return an empty path. If not, it will first recurse down the left branch and return a path if the key is found. If the key isn't to the left, the function will recurse down the right branch and return a path if the key is found. If the function reaches the end of recursion without finding the key, it will return nullptr.


**HForest**

We decided to use a standard library vector of tree pointers to structure our forest. For the internal structure of the forest, we used the make_heap function with a less-than comparison passed as a parameter to sort the trees in a min-heap.

- **Constructor:** Initalizes the vec_ as a pointer to a vector of tree_ptr_t type entries, then calls make_heap with a less-than function to sort the vector for easier searches.
- **Destructor:** Left as default since shared pointers, vectors, and HTree pointers automatically deallocate memory.
- **size:** Calls the size fuction on the forest's vector and returns the result.
- **pop_tree:** This function uses pop_heap to push the tree with the lowest root value to the back of the vector. Then, it saves the tree in a seperate variable, removes the element, then returns the variable.
- **add_tree:** This function appends a tree pointer to the forest vector then uses make_heap to re-sort.
- **compare_trees:** Private static function used to sort heap into min-heap.

**test_htree**

We decided to use the structure of the basic tree testing file that Eitan provided on Slack, edited to work with the new encapsulation. We also added a single-element tree, a left-only tree, and a right-only tree. Each different kind of tree is individually tested with codes that ensure proper functioning of all required functions. For the single-element, left-only, and right-only trees, there are also codes that make sure a nullptr is returned when the paths do not exist.

**test_hforest**

We built five tree-constructor functions, three with unique root values and two with the same root value. The forest initalizes with one of the trees, two more are added. The lowest of the three trees gets popped off, then added back along with the two other trees. Then the trees are popped off one by one until the forest is empty. Then a new forest is initalized using the default empty vector. A tree is added, then the same tree is added again. Both versions of the tree are popped out.
