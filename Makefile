CXX=g++-8
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -O0 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  test_hforest test_htree

test_htree: test_htree.o htree.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_tree: test_tree.o tree.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_hforest: test_hforest.o hforest.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o test_htree test_tree test_hforest

test: all
	./test_hforest
	./test_huffman
	./test_bitio
CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -g

#all: test_hforest test_htree

#test_htree: test_htree.o htree.o
#	$(CXX) $(CXXFLAGS) -o test_htree test_htree.o htree.o

#test_tree.o: test_htree.cc htree.hh
#	$(CXX) $(CXXFLAGS) -c test_htree.cc

#tree.o: htree.cc htree.hh
#	$(CXX) $(CXXFLAGS) -c htree.cc

# Use copy to move directory into patty. Replace 'treeHW' with desired destination folder.
#You'll probably need to use clean and recompile before running.
#copy:
#	scp * patty:hw7

#clean:
#	rm -rf *.o test_htree
