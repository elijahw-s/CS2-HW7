CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -O0 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  test_hforest test_htree

test_htree: test_htree.o htree.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_tree: test_tree.o tree.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_hforest: test_hforest.o hforest.o htree.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o test_htree test_tree test_hforest

test: all
	./test_hforest
	./test_huffman
	./test_bitio

#Use copy to move directory into patty. Replace 'hw7' with desired destination folder.
#You'll probably need to use clean and recompile before running.
copy:
	scp * patty:hw7
