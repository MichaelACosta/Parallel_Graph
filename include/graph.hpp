#ifndef GRAPH_HPP
#define GRAPH_HPP

using namespace std;

//Define tamanho do grafo

const int size=50;
const int infinito=	99999999;
				  //10000000;

class Graph{
protected:
	int vetor[size][size];
	int flag[size]; //bool

public:
	Graph();
	virtual void insertNode(int node);
	virtual void deletNode(int node);
	virtual bool testNode(int node) const;

	virtual void changeEdge(int l, int c);
	virtual void increaseEdge(int l, int c);
	virtual void decreaseEdge(int l, int c);
	virtual int getVal(int l, int c)const;

	int Dijkstra(int inicio, int fim) const;
	~Graph();
};

#endif