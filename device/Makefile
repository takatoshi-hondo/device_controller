CXX=g++
CXXFLAGS+=-g -O -fPIC
OBJS=devc_device.o usbserial_linux.o
USL=usbserial_linux

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $^ -o $@

all: $(OBJS) $(USL).so

$(USL).so: $(USL).o devc_device.o
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

clean:
	rm -rf $(OBJS) *.so *~
