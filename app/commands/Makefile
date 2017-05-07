CXX=g++
CXXFLAGS+=-g -O -fPIC -std=gnu++11
TARGET=$(PLUGIN).so
OBJ=../devc.o ../binarymap.o ../../device/devc_device.o
LDLIBS=-lci

$(TARGET): $(PLUGIN).cpp $(OBJ) 
	$(CXX) $(CXXFLAGS) -shared $^ -o $@ $(LDLIBS) $(OPTLIBS)

clean:
	rm -rf $(TARGET) *~ 
