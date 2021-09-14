CC = clang++
CXX_FLAGS = -std=c++17 -Wall -Werror -O3 -c

SRC_DIR = src/ananke/

INCLUDE_FLAGS = -I$(SRC_DIR)

LIB_NAME = ananke

OUT_DIR = out/

HEADER_INSTALL_PATH = /usr/local/include/$(LIB_NAME)
LIB_INSTALL_PATH = /usr/local/lib/

all: bzip_build gzip_build
	ar -rv lib$(LIB_NAME).a bzip2.o gzip.o

bzip_build:
	$(CC) $(CXX_FLAGS) $(INLCUDE_FLAGS) $(SRC_DIR)bzip2.cpp

gzip_build:
	$(CC) $(CXX_FLAGS) $(INLCUDE_FLAGS) $(SRC_DIR)gzip.cpp

clean:
	rm *.o
	rm *.a

install:
	cp lib$(LIB_NAME).a $(LIB_INSTALL_PATH)
	mkdir -p $(HEADER_INSTALL_PATH)
	cp $(SRC_DIR)*.hpp $(HEADER_INSTALL_PATH)

uninstall:
	rm -r $(HEADER_INSTALL_PATH)
	rm $(LIB_INSTALL_PATH)lib$(LIB_NAME).a
