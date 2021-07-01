COMP=g++
NO_OPTIMIZE=-O0
MULTITHREAD=-pthread
C++11=-std=c++11

# Single-threaded prime finder
prime_finder: prime_finder_bm.cpp
	$(COMP) $(NO_OPTIMIZE) prime_finder_bm.cpp -o prime_finder_exe

# Independently-operating multi-threaded prime finder
prime_finder_mt: prime_finder_mt_bm.cpp
	$(COMP) $(C++11) $(MULTITHREAD) $(NO_OPTIMIZE) prime_finder_mt_bm.cpp -o prime_finder_mt_exe
