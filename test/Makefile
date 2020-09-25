# Define paths
CURRENT_PATH = $(PWD)/..
INCLUDE_PATH = ${CURRENT_PATH}
SOURCE_PATH  = ${CURRENT_PATH}
TEST_PATH    = ${CURRENT_PATH}/test

# Define compilers and compilation options
CPP_TOOL = clang++
CPP_FLAGS = -std=c++17 -O2 -g

# Define objects
HILBERT_OBJECT = $\
	hilbert_transform.o $\
	hilbert_mesh.o

TEST_MAIN_OBJECT = $\
	test.o

# Compile rules

all: $(HILBERT_OBJECT) $(TEST_MAIN_OBJECT)
	$(CPP_TOOL) $(HILBERT_OBJECT) $(TEST_MAIN_OBJECT) -o test

$(HILBERT_OBJECT): %.o: $(SOURCE_PATH)/%.cpp
	$(CPP_TOOL) -c $(CPP_FLAGS) -I${INCLUDE_PATH} $< -o $(TEST_PATH)/$@

$(TEST_MAIN_OBJECT): %.o: $(TEST_PATH)/%.cpp
	$(CPP_TOOL) -c $(CPP_FLAGS) -I${INCLUDE_PATH} $< -o $(TEST_PATH)/$@


.PHONY: clean

clean:
	rm *.o