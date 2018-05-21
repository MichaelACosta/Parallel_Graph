#include <iostream>
#include <queue>
#include <mutex>
#include <graph.hpp>
#include <graphmutex.hpp>

mutex mgraph[size][size], mflag[size], mset;


GraphMutex::GraphMutex(){
	int i, c;
	mset.lock();
	for (i = 0; i < size; ++i){
		flag[i]=0;
	}
	for (i = 0; i < size; ++i){
		for (c = 0; c < size; ++c){
			vetor[i][c]=0;
		}
	}
	mset.unlock();
//	cout << "Grafo criado.\n";
}

void GraphMutex::insertNode(int node){
	mflag[node].lock();
	if(!flag[node]){
		//mflag.lock();
		flag[node]=1;
		//mflag.unlock();
	}
	mflag[node].unlock();
}

void GraphMutex::deletNode(int node){
	mflag[node].lock();
	if(flag[node]){
		//mflag.lock();
		flag[node]=0;
		//mflag.unlock();
	}
	mflag[node].unlock();
}

bool GraphMutex::testNode(int node)const{
	bool ret;
	mflag[node].lock();
	if(flag[node]){
		ret= true;
	}
	else{
		ret= false;
	}
	mflag[node].unlock();
	return ret;
}


void GraphMutex::changeEdge(int l, int c){
	if (l!=c){


		this->insertNode(l);
		this->insertNode(c);

		//medge.lock();
		mgraph[l][c].lock();
		vetor[l][c]=1;
		mgraph[l][c].unlock();
		//medge.unlock();
	}
}

void GraphMutex::increaseEdge(int l, int c){
	if (l!=c){
		mgraph[l][c].lock();
		if(vetor[l][c]){
			//mset.lock();
			//mgraph.lock();
			vetor[l][c]++;
			//mset.unlock();
			//mgraph.unlock();
		}
		else{
			this->insertNode(l);
			this->insertNode(c);

			vetor[l][c]=1;
		}
		mgraph[l][c].unlock();
	}
}

void GraphMutex::decreaseEdge(int l, int c){
	if (l!=c){
		mgraph[l][c].lock();
		if(vetor[l][c]){
			//mgraph.lock();
			vetor[l][c]--;
			//mgraph.unlock();
		}

		if(!vetor[l][c]){
			if(this->testNode(l) && this->testNode(c)){
				int i, flagl=0, flagc=0;
				for(i=0; i<size; i++){
					if(i!=l && i!=c){
						mgraph[l][i].lock();
						mgraph[i][l].lock();
						mgraph[c][i].lock();
						mgraph[i][c].lock();
						if(vetor[l][i] || vetor[i][l]){
							flagl=1;
						}

						if(vetor[c][i] || vetor[i][c]){
							flagc=1;
						}
						mgraph[i][c].unlock();
						mgraph[c][i].unlock();
						mgraph[i][l].unlock();
						mgraph[l][i].unlock();
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
		mgraph[l][c].unlock();
	}
}

int GraphMutex::getVal(int l, int c) const{
	int val=0;
	//mget.lock();
	mgraph[l][c].lock();
	
	val=vetor[l][c];
	
	//mget.unlock();
	mgraph[l][c].unlock();
	return val;
}


GraphMutex::~GraphMutex(){
//	delete []vetor;
//	delete []flag;
//	cout << "Destrutor executado.\n";
}