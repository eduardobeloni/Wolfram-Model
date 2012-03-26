# variable CXXFLAGS and LDLIB will be the compiler to use

CXXFLAGS += `pkg-config --cflags gtkmm-2.4`
LDLIBS += `pkg-config --libs gtkmm-2.4`

all: wolfram_model
	
wolfram_model: wolfram_model.o automatawindow.o growtharea.o
	g++ wolfram_model.o automatawindow.o growtharea.o -o wolfram_model $(CXXFLAGS) $(LDLIBS)

wolfram_model.o: wolfram_model.cpp automatawindow.h
	g++ -c $(CXXFLAGS) wolfram_model.cpp

automatawindow.o: automatawindow.cpp automatawindow.h growtharea.h
	g++ -c $(CXXFLAGS) automatawindow.cpp

growtharea.o: growtharea.cpp growtharea.h
	g++ -c $(CXXFLAGS) growtharea.cpp

clean:
	rm -rf *o wolfram_model
