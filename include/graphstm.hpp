#ifndef GRAPHSTM_HPP
#define GRAPHSTM_HPP

#define RO	1
#define RW	0

#include <stm.h>
#include <graph.hpp>

//# define TM_COMPILER

using namespace std;

#define TM_START(tid, ro)               { stm_tx_attr_t _a = {{.id = tid, .read_only = ro}}; sigjmp_buf *_e = stm_start(_a); if (_e != NULL) sigsetjmp(*_e, 0)
#define TM_LOAD(addr)                   stm_load((stm_word_t *)addr)
#define TM_STORE(addr, value)           stm_store((stm_word_t *)addr, (stm_word_t)value)
#define TM_COMMIT                       stm_commit(); }


/*--------*/
#define TM_INIT                         stm_init(); mod_stats_init()
#define TM_EXIT                         stm_exit()
#define TM_INIT_THREAD                  stm_init_thread()
#define TM_EXIT_THREAD                  stm_exit_thread()
#define TM_NUM_COMMITS(val)				stm_get_global_stats("global_nb_commits", (void*)val)
#define TM_NUM_ABORTS(val)				stm_get_global_stats("global_nb_aborts", (void*)val)
/*--------*/

//As definições do grafo são herdadas da classe Graph

class GraphStm : public Graph {
protected:
	int *vetor[size][size];
	int *flag[size]; //bool
public:
	GraphStm();

	virtual void insertNode(int node);
	virtual void deletNode(int node);
	virtual bool testNode(int node) const;

	virtual void changeEdge(int l, int c);
	virtual void increaseEdge(int l, int c);
	virtual void decreaseEdge(int l, int c);
	virtual int getVal(int l, int c) const;

};

#endif