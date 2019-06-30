RM=rm -f
FLAGS=-O3 -std=c++11
EXEC=mandelbrot
NVCC=nvcc
all: $(EXEC)

$(EXEC):
	$(NVCC) $(FLAGS) $(EXEC).cu -c -o $(EXEC).o
	$(NVCC) $(FLAGS) $(EXEC).o -o $(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)