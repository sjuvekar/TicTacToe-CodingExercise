CXX=clang++

CFLAGS=-std=c++14 -stdlib=libc++

tic_tac_toe.o: tic_tac_toe.h tic_tac_toe.cc strategy.o
	$(CXX) $(CFLAGS) -c strategy.o tic_tac_toe.cc

strategy.o: strategy.h strategy.cc
	$(CXX) $(CFLAGS) -c strategy.cc

main: tic_tac_toe.o strategy.o
	$(CXX) $(CFLAGS) -o main tic_tac_toe.o strategy.o main.cc
	
clean:
	$(RM) *.o *.gch a.out
