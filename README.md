# CS2-HW7
Current issues:

- Compare function for heap structure in HForest is not the right type of function. Maybe override operator < instead?
- path_to has issues responding to being passed nullptr (segmentation fault errors). Tt also might not be returning a correct path, it's difficult to tell. I have print statements that'll hopefully help debug.
- Destructor functions aren't written, they may need to be made.
- HForest size function doesn't exist yet.
- HForest functions sometimes don't recognize tree_ptr_t when it seems like they should.
- pop_tree is struggling to convert what it thinks is an int to a pointer.
- pop_heap (standard library function) isn't recognized in HForest.
- test_hforest.cc doesn't exist yet.
- test_htree.cc isn't very robust. I have a decent test function from the last homework if we want to try to adapt that.

Information about heap structure:

https://en.cppreference.com/w/cpp/algorithm/make_heap

https://en.cppreference.com/w/cpp/algorithm/pop_heap

I put the pointers to the different trees into a vector, then tried to use make_heap with the correct compare function. That should make a min-heap if we can get the compare function to work.
