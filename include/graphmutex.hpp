#ifndef GRAPHMUTEX_HPP
#define GRAPHMUTEX_HPP

#include <graph.hpp>
using namespace std;

//As definições do grafo são herdadas da classe Graph
class GraphMutex : public Graph {
protected:
	int vetor[size][size];
	int flag[size];

public:
	GraphMutex();
	virtual void insertNode(int node);
	virtual void deletNode(int node);
	virtual bool testNode(int node) const;
	virtual void changeEdge(int l, int c);
	virtual void increaseEdge(int l, int c);
	virtual void decreaseEdge(int l, int c);
	virtual int getVal(int l, int c) const;
	~GraphMutex();
};

#endif
