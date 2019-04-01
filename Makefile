
CC = g++
CFLAGS = -pg -Wall -std=c++11
#SRCS = main.cpp
SRCS = ${wildcard *.cpp}
OBJS = ${SRCS:.cpp=.o}
INCLS = ${SRCS:.cpp=.h}

p2: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o p1

$(OBJS):
	$(CC) $(CFLAGS) -c $*.cpp

depend: Makefile.dep
	$(CC) -MM $(SRCS) > Makefile.dep

Makefile.dep:
	touch Makefile.dep

.PHONY: submit clean

submit:
	rm -f submit.zip
	zip submit.zip $(SRCS) $(INCLS) Makefile Makefile.dep BST.h AVL.h Splay.h BSTNode.h AVLNode.h SplayNode.h

clean:
	rm -f *.o a.out core

include Makefile.dep