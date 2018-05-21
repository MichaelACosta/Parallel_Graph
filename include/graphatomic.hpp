#ifndef GRAPHATOMIC_HPP
#define GRAPHATOMIC_HPP

#include <atomic>
#include <graph.hpp>
using namespace std;


//As definições do grafo são herdadas da classe Graph

class GraphAtomic : public Graph {
protected:
	atomic<int> vetor[size][size];
	atomic<int> flag[size]; //bool


public:
	GraphAtomic();

	virtual void insertNode(int node);
	virtual void deletNode(int node);
	virtual bool testNode(int node) const;

	virtual void changeEdge(int l, int c);
	virtual void increaseEdge(int l, int c);
	virtual void decreaseEdge(int l, int c);
	virtual int getVal(int l, int c) const;

};

#endif