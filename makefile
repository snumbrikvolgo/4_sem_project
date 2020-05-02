OBJ=player.o main.o 
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS += -std=c++11
PROG=project
CXX:=g++

all:${PROG}

%.o: %.cpp
	$(CXX) ${CXXFLAGS} -c $< -o $@

#%.o: %.h
	#$(CXX) ${CXXFLAGS}-c $< -o $@

#main.o:main.cpp
#	g++ -c main.cpp -o main.o

${PROG}:${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -o ${PROG} ${LIBS}


clean:
	$(RM) $(PROG)
