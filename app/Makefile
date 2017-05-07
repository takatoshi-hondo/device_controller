CC=g++
CXXFLAGS+=-g -O -fPIC -std=gnu++11
OBJS=devc.o devc_main.o binarymap.o
EXTOBJ=../device/devc_device.o
EXE=devc_main
LDLIBS=-lci -ldl -lpthread

.cpp.o:
	$(CC) -c $(CXXFLAGS) $^ -o $@ $(LDLIBS)

all: $(OBJS) $(EXE)

$(EXE): $(OBJS) $(EXTOBJ)
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -rf $(OBJS) $(EXE) *.so *~
