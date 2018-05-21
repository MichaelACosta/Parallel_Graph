#include <iostream>
#include <queue>
#include <mutex>
#include <graph.hpp>
#include <graphmutexgg.hpp>

mutex mggraph, mgflag, mgset;


GraphMutexGG::GraphMutexGG(){
	int i, c;
	mgset.lock();
	for (i = 0; i < size; ++i){
		flag[i]=0;
	}
	for (i = 0; i < size; ++i){
		for (c = 0; c < size; ++c){
			vetor[i][c]=0;
		}
	}
	mgset.unlock();
//	cout << "Grafo criado.\n";
}

void GraphMutexGG::insertNode(int node){
	mgflag.lock();
	if(!flag[node]){
		//mflag.lock();
		flag[node]=1;
		//mflag.unlock();
	}
	mgflag.unlock();
}

void GraphMutexGG::deletNode(int node){
	mgflag.lock();
	if(flag[node]){
		//mflag.lock();
		flag[node]=0;
		//mflag.unlock();
	}
	mgflag.unlock();
}

bool GraphMutexGG::testNode(int node)const{
	bool ret;
	mgflag.lock();
	if(flag[node]){
		ret= true;
	}
	else{
		ret= false;
	}
	mgflag.unlock();
	return ret;
}


void GraphMutexGG::changeEdge(int l, int c){
	if (l!=c){


		this->insertNode(l);
		this->insertNode(c);

		//medge.lock();
		mggraph.lock();
		vetor[l][c]=1;
		mggraph.unlock();
		//medge.unlock();
	}
}

void GraphMutexGG::increaseEdge(int l, int c){
	if (l!=c){
		mggraph.lock();
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
		mggraph.unlock();
	}
}

void GraphMutexGG::decreaseEdge(int l, int c){
	if (l!=c){
		mggraph.lock();
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
						
						if(vetor[l][i] || vetor[i][l]){
							flagl=1;
						}

						if(vetor[c][i] || vetor[i][c]){
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
		mggraph.unlock();
	}
}

int GraphMutexGG::getVal(int l, int c) const{
	int val=0;
	//mget.lock();
	mggraph.lock();
	
	val=vetor[l][c];
	
	//mget.unlock();
	mggraph.unlock();
	return val;
}


GraphMutexGG::~GraphMutexGG(){
//	delete []vetor;
//	delete []flag;
//	cout << "Destrutor executado.\n";
}