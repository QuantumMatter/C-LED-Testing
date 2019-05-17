CFLAGS=-Wall -O3 -g -Wextra -Wno-unused-parameter
CXXFLAGS=$(CFLAGS)

RGB_LIB_DISTRIBUTION=/home/pi/libraries/rpi-rgb-led-matrix/
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

# (FYI: Make sure, there is a TAB-character in front of the $(MAKE))
$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)

simple_cpp : simple_cpp.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) simple_cpp.o -o $@ $(LDFLAGS)

github_simple : github_simple.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) github_simple.o -o $@ $(LDFLAGS)

clean:
	rm -rf *.o

% : %.o $(RGB_LIBRARY)
	$(CXX) $< -o $@ $(LDFLAGS)

%.o : %.cpp
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

%.o : %.c
	$(CC) -I$(RGB_INCDIR) $(CFLAGS) -c -o $@ $<