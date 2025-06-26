CC = mpicc
CFLAGS = -Wall -g
LDFLAGS = -lm

TARGET = mpi_matrix_mult
SRC = mpi_matrix_mult.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

run: all
	mpirun -np 4 ./$(TARGET) 8 4 6
	# Example: M=8, K=4, N=6 with 4 processes

run2: all
	# Another example with different dimensions and 2 processes
	mpirun -np 2 ./$(TARGET) 10 5 5

run_default: all
	# Runs with default dimensions M=6, K=4, N=5, adjust np as needed
	mpirun -np 2 ./$(TARGET)

.PHONY: all clean run run2 run_default
