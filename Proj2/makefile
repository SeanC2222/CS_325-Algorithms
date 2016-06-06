####Variables####
#Compiler
CXX = g++

#Language version
CXXFLAGS = -std=c++0x

#Enforces standard
CXXFLAGS += -pedantic-errors

#Debug information
CXXFLAGS += -g


####Files####
#Source Files
SRC1 = proj2.cpp
SRC2 = changeSlow.cpp
SRC3 = changeDP.cpp


#Executable files
PROG1 = proj2
PROG2 = proj2Slow
PROG3 = proj2CDP
PROGS = ${PROG1} ${PROG2} ${PROG3}


####Build####
all: ${PROG1} ${PROG2} ${PROG3}

example: all
	./proj2Slow amountSlow.txt
	./proj2CDP amountCDP.txt amountCDPchange.txt
	./proj2 amountGreedy.txt
	
${PROG1}: ${SRC1}
	${CXX} ${CXXFLAGS} ${SRC1} -o ${PROG1}
	
${PROG2}: ${SRC2}
	${CXX} ${CXXFLAGS} ${SRC2} -o ${PROG2}

${PROG3}: ${SRC3}
	${CXX} ${CXXFLAGS} ${SRC3} -o ${PROG3}
	
clean:
	rm ${PROGS} amountGreedychange.txt amountCDPchange.txt amountSlowchange.txt 
