CXX = gcc
CXX_FLAGS = -g -Wall -pthread # Adding -pthread for pthread usage

server: main.o codec.o server.o
	$(CXX) $(CXX_FLAGS) -o $@ $^

%.o: %.c
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

clean:
	rm -rf *.o server
