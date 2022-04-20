ifdef USE_INT
MACRO = -DUSE_INT
endif

#compiler setup
CXX = g++
MPICXX = mpic++
CXXFLAGS = -std=c++14 -march=native -pthread -O3 
LDFLAGS = -Llib -lalloc431 -lpthread

COMMON= core/utils.h core/cxxopts.h core/get_time.h core/graph.h core/quick_sort.h common/utils.h common/cxxopts.h common/get_time.h common/quick_sort.h common/allocator.h common/non_blocking_queue.h
SERIAL= SSSP_serial
NON_BLOCKING_QUEUE = common/non_blocking_queue.h
PARALLEL= SSSP_parallel SSSP_MPI
ALL= $(SERIAL) $(PARALLEL)


all : $(ALL)

$(SERIAL): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(PARALLEL): %: %.cpp
	$(MPICXX) $(CXXFLAGS) -o $@ $<

SSSP_parallel : SSSP_parallel.cpp $(COMMON) $(NON_BLOCKING_QUEUE)
	$(CXX) $(CXXFLAGS) -DNON_BLOCKING_QUEUE $< $(LDFLAGS) -o $@

.PHONY : clean

clean :
	rm -f *.o *.obj $(ALL)
