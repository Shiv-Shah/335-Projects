
GXX49_VERSION := $(shell g++-4.9 --version 2>/dev/null)

ifdef GXX49_VERSION
	CXX_COMMAND := g++-4.9
else
	CXX_COMMAND := g++
endif

CXX = ${CXX_COMMAND} -std=c++11 -Wall

run_test: cuckoo
	./cuckoo

headers: rubrictest.hpp

cuckoo: headers cuckoo.cpp
	${CXX} cuckoo.cpp -o cuckoo

clean:
	rm -f cuckoo
