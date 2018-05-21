#include <iostream>
#include <queue>
#include <atomic>
#include <graph.hpp>
#include <graphatomic.hpp>


GraphAtomic::GraphAtomic(){
	int i, c;
	for (i = 0; i < size; ++i){
		flag[i].store(0, memory_order_relaxed);
	}
	for (i = 0; i < size; ++i){
		for (c = 0; c < size; ++c){
			vetor[i][c].store(0, memory_order_relaxed);
		}
	}
//	cout << "Grafo criado.\n";
}

void GraphAtomic::insertNode(int node){
	if(this->testNode(node)){
		flag[node].store(1,memory_order_relaxed);
	}
}

void GraphAtomic::deletNode(int node){
	if(this->testNode(node)){
		flag[node].store(0,memory_order_relaxed);
	}
}

bool GraphAtomic::testNode(int node)const{
	bool ret;
	if(flag[node].load(memory_order_relaxed)){
		ret= true;
	}
	else{
		ret= false;
	}
	return ret;
}

void GraphAtomic::changeEdge(int l, int c){
	if (l!=c){
		this->insertNode(l);
		this->insertNode(c);
		
		vetor[l][c].store(1, memory_order_relaxed);
	}
}

void GraphAtomic::increaseEdge(int l, int c){
	if (l!=c){
		if(this->getVal(l,c)){
			int i=vetor[l][c].load(memory_order_relaxed);
			i++;
			vetor[l][c].store(i, memory_order_relaxed);
		}
		else{
			this->changeEdge(l, c);
		}
	}
}

void GraphAtomic::decreaseEdge(int l, int c){
	if (l!=c){
		if(this->getVal(l,c)){
			int i=vetor[l][c].load(memory_order_relaxed);
			i--;
			vetor[l][c].store(i, memory_order_relaxed);
		}

		if(!this->getVal(l,c)){
			if(this->testNode(l) && this->testNode(c)){
				int i, flagl=0, flagc=0;
				for(i=0; i<size; i++){
					if(i!=l && i!=c){
						if(this->getVal(l,i) || this->getVal(i,l)){
							flagl=1;
						}

						if(this->getVal(c,i) || this->getVal(i,c)){
							flagc=1;
						}
					}
				}
				if(!flagl){
					this->deletNode(l);
				}
				if(!flagc){
					this->deletNode(c);
				}
			}
		}	

		
	}
}

int GraphAtomic::getVal(int l, int c) const{
	int val=0;
	if(vetor[l][c].load(memory_order_relaxed)){
		val=vetor[l][c].load(memory_order_relaxed);
	}
	return val;
}
