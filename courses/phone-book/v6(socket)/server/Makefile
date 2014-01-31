BASE_DIR = .
BUILD_DIR = $(BASE_DIR)/build
SRC_DIR = $(BASE_DIR)/src

OBJS = $(BUILD_DIR)/book.o $(BUILD_DIR)/client.o $(BUILD_DIR)/main.o $(BUILD_DIR)/input.o $(BUILD_DIR)/fileio.o $(BUILD_DIR)/md5.o $(BUILD_DIR)/auth.o


CXX = g++
CXXFLAGS = -g

server : $(OBJS)
	$(CXX) $(OBJS) -o server -lpthread  

$(BUILD_DIR)/client.o : $(SRC_DIR)/client_process.cpp $(SRC_DIR)/client_process.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/client_process.cpp -o $(BUILD_DIR)/client.o

$(BUILD_DIR)/book.o : $(SRC_DIR)/book.cpp $(SRC_DIR)/book.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/book.cpp -o $(BUILD_DIR)/book.o

$(BUILD_DIR)/input.o : $(SRC_DIR)/input_control.cpp $(SRC_DIR)/input_control.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/input_control.cpp -o $(BUILD_DIR)/input.o

$(BUILD_DIR)/fileio.o : $(SRC_DIR)/fileio.cpp $(SRC_DIR)/fileio.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/fileio.cpp -o $(BUILD_DIR)/fileio.o

$(BUILD_DIR)/md5.o : $(SRC_DIR)/md5.cpp $(SRC_DIR)/md5.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/md5.cpp -o $(BUILD_DIR)/md5.o

$(BUILD_DIR)/auth.o : $(SRC_DIR)/auth.cpp $(SRC_DIR)/auth.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/auth.cpp -o $(BUILD_DIR)/auth.o

$(BUILD_DIR)/main.o : $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o
	

