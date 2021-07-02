EXEC=$(patsubst %.cpp, %, $(wildcard *.cpp))

all: $(EXEC)

%: %.cpp
	g++ -fopenmp $< -o $@

clean:
	rm $(EXEC)
