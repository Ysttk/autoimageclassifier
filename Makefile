CC=g++
ARCH=-arch x86_64
 
OPENCV_DIR=/Users/sbj/Documents/workspace/Opencv/opencv-2.4.8/install
 
INCLUDE_FLAGS=-I$(OPENCV_DIR)/include
 
CFLAGS=-c -Wall $(INCLUDE_FLAGS) -DMACOS
LDFLAGS= -L$(OPENCV_DIR)/lib -lopencv_core -lopencv_highgui -lopencv_imgproc
    
SOURCES=OpenCVConsole.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=opencv_console
	 
all : $(SOURCES) $(EXECUTABLE)
	 
clean :
	   rm -f $(OBJECTS) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) Makefile
	   $(CC) $(ARCH) $(LDFLAGS) $(OBJECTS) -o $@
	    
.cpp.o:
	   $(CC) $(CFLAGS) $< -o $@
