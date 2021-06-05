
SRC_ROOT = src/
BUILD_ROOT = build/

all:	$(BUILD_ROOT)test-hll $(BUILD_ROOT)hyperloglog.a $(BUILD_ROOT)hyperloglog.so 

$(BUILD_ROOT)test-hll: $(BUILD_ROOT)test-hll.o $(BUILD_ROOT)hyperloglog.o
	$(CXX) -fPIC -o $(BUILD_ROOT)test-hll $(BUILD_ROOT)test-hll.o $(BUILD_ROOT)hyperloglog.o 

$(BUILD_ROOT)test-hll.o: $(SRC_ROOT)test-hll.cpp
	$(CXX) -fPIC -c -o $(BUILD_ROOT)test-hll.o $(SRC_ROOT)test-hll.cpp 


#$(BUILD_ROOT)MurmurHash3.o: $(SRC_ROOT)MurmurHash3.cpp
#	$(CXX) -fPIC -c -o $(BUILD_ROOT)MurmurHash3.o $(SRC_ROOT)MurmurHash3.cpp


$(BUILD_ROOT)hyperloglog.o: $(SRC_ROOT)hyperloglog.cpp
	$(CXX) -fPIC -c -o $(BUILD_ROOT)hyperloglog.o $(SRC_ROOT)hyperloglog.cpp

$(BUILD_ROOT)hyperloglog.so: $(SRC_ROOT)hyperloglog.o
	$(CXX) -shared -o $(BUILD_ROOT)hyperloglog.so $(SRC_ROOT)hyperloglog.o

$(BUILD_ROOT)hyperloglog.a: $(SRC_ROOT)hyperloglog.o
	ar rcs $(BUILD_ROOT)hyperloglog.a $(BUILD_ROOT)hyperloglog.o
	
clean:
	rm -fr build/*.o
	rm -fr build/test-hll
	rm -fr build/*.a
	rm -fr build/*.so


#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
#
#OBJS = hyperloglog.o MurmurHash3.o

#ifeq ($(BUILD_MODE),debug)
#	CFLAGS += -g
#else ifeq ($(BUILD_MODE),run)
#	CFLAGS += -O2
#else
#	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
#endif

#%.o:	$(SRC_ROOT)%.cpp
#	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<
	
	



#hyperloglog:	$(OBJS)
#	$(CXX) -o $@ $^

#%.o:	$(PROJECT_ROOT)%.cpp
#	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

#%.o:	$(PROJECT_ROOT)%.c
#	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<


	
	
