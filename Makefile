CXX = g++
OBJ = obj
INC = include
BIN = bin
LIB = lib
SRC = src
CXXFLAGS =-Wall -g -std=c++11 -c -O1

main:$(OBJ)/main.o $(OBJ)/funciones.o $(OBJ)/ITGO.o $(OBJ)/random_ppio.o
	$(CXX) -o main $^

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/ITGO.h
	$(CXX) $(CXXFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC)
$(OBJ)/ITGO.o: $(SRC)/ITGO.cpp $(INC)/ITGO.h $(INC)/funciones.h
	$(CXX) $(CXXFLAGS) $(SRC)/ITGO.cpp -o $(OBJ)/ITGO.o -I$(INC)
$(OBJ)/funciones.o: $(SRC)/funciones.cpp $(INC)/funciones.h $(INC)/random_ppio.h
	$(CXX) $(CXXFLAGS) $(SRC)/funciones.cpp -o $(OBJ)/funciones.o -I$(INC)
$(OBJ)/random_ppio.o: $(SRC)/random_ppio.cpp $(INC)/random_ppio.h
	$(CXX) $(CXXFLAGS) $(SRC)/random_ppio.cpp -o $(OBJ)/random_ppio.o -I$(INC)

# ************ Limpieza ************
clean:
	 -rm $(OBJ)/* $(BIN)/*;

mrproper: clean
	-rm $(BIN)/* doc/html/*
