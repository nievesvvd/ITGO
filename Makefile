SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CXXFLAGS = -Wall -g  -I$(INC) -c
TIPOTRANS_H = transformacion2.h
TIPOTRANS_CPP = transformacion2.cpp

all: $(BIN)/ocultar $(BIN)/revelar $(BIN)/transformar $(BIN)/generar $(BIN)/componer

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************

# ************ Compilación de programas ************
$(BIN)/ocultar: $(OBJ)/ocultar.o $(LIB)/libimagen.a
	@echo Creando archivo $@...
	$(CXX) -o $@ $^ -L$(LIB)/ -limagen

$(BIN)/revelar: $(OBJ)/revelar.o $(LIB)/libimagen.a
	@echo Creando archivo $@...
	$(CXX) -o $@ $^ -L$(LIB)/ -limagen

$(BIN)/transformar: $(OBJ)/transformar.o $(OBJ)/transformacion.o $(LIB)/libimagen.a
	@echo Creando archivo $@...
	$(CXX) -o $@ $^ -L$(LIB)/ -limagen

$(BIN)/generar: $(OBJ)/generar.o $(OBJ)/generadores.o $(OBJ)/transformacion.o 
	@echo Creando archivo $@...
	$(CXX) -o $@ $^ -L$(LIB)/ 

$(BIN)/componer: $(OBJ)/componer.o $(OBJ)/transformacion.o 
	@echo Creando archivo $@...
	$(CXX) -o $@ $^ -L$(LIB)/ 

# ************ Compilación de objetos ************
$(OBJ)/ocultar.o: $(SRC)/ocultar.cpp $(INC)/imagen.h  $(INC)/procesar.h  
	@echo Creando archivo $@...
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(OBJ)/revelar.o: $(SRC)/revelar.cpp $(INC)/imagen.h $(INC)/procesar.h 
	@echo Creando archivo $@...
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC) 

$(OBJ)/transformar.o:$(SRC)/transformar.cpp $(INC)/imagen.h  $(INC)/procesar.h $(SRC)/$(TIPOTRANS_CPP) $(INC)/$(TIPOTRANS_H) 
	@echo Creando archivo $@...
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(OBJ)/generar.o: $(SRC)/generar.cpp $(INC)/generadores.h $(INC)/transformacion.h $(SRC)/transformacion.cpp 
	@echo Creando archivo $@...
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(OBJ)/transformacion.o: $(SRC)/transformacion.cpp $(INC)/transformacion.h $(SRC)/$(TIPOTRANS_CPP) $(INC)/$(TIPOTRANS_H) 
	@echo Creando archivo $@...
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(OBJ)/procesar.o: $(SRC)/procesar.cpp $(INC)/procesar.h
	@echo Creando archivo $@...
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(OBJ)/generadores.o: $(SRC)/generadores.cpp $(INC)/generadores.h $(INC)/transformacion.h
	@echo Creando archivo $@...
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(OBJ)/componer.o: $(SRC)/componer.cpp $(INC)/transformacion.h
	@echo Creando archivo $@...
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INC)/imagen.h
	@echo Creando archivo $@...
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)

$(OBJ)/imagenES.o: $(SRC)/imagenES.cpp $(INC)/imagenES.h
	@echo Creando archivo $@...
	$(CXX) $(CXXFLAGS) $< -o $@ -I$(INC)


# ************ Compilación de librerias ************
$(LIB)/libimagen.a: $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/procesar.o
	@echo Creando libreria $@...
	$(AR) rvs $(LIB)/libimagen.a $(OBJ)/imagenES.o $(OBJ)/imagen.o $(OBJ)/procesar.o


# ************ Limpieza ************
clean:
	-rm $(OBJ)/* $(BIN)/* $(LIB)/* 

mrproper: clean
	-rm $(BIN)/* doc/html/*
