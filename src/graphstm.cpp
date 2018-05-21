#include <iostream>
#include <queue>
#include <graph.hpp>
#include <graphstm.hpp>


GraphStm::GraphStm(){
	int i, c;
	for (i = 0; i < size; ++i){
//		cout<<"ta indo\n";
		TM_INIT_THREAD;
		TM_START(0,RW);
//		cout<<"dentro\n";
		TM_STORE(&flag[i], 0);
//		cout<<"quase\n";
		TM_COMMIT;
//		cout<<"foi\n";
		TM_EXIT_THREAD;
	}

	for (i = 0; i < size; ++i){
		for (c = 0; c < size; ++c){
			TM_INIT_THREAD;
			TM_START(0,RW);
			TM_STORE(&vetor[i][c], 0);
			TM_COMMIT;
			TM_EXIT_THREAD;
		}
	}
//	cout << "Grafo criado.\n";
}

void GraphStm::insertNode(int node){
	if(this->testNode(node)){
		TM_START(0,RW);
		TM_STORE(&flag[node], 1);
		TM_COMMIT;
	}
}

void GraphStm::deletNode(int node){
	if(this->testNode(node)){
		TM_START(0,RW);
		TM_STORE(&flag[node], 0);
		TM_COMMIT;
	}
}

bool GraphStm::testNode(int node)const{
	bool ret;
	TM_START(0,RW);
	int aux=TM_LOAD(&flag[node]);
	if(aux){
		ret= true;
	}
	else{
		ret= false;
	}
	TM_COMMIT;

	return ret;
}

void GraphStm::changeEdge(int l, int c){
	if (l!=c){
		this->insertNode(l);
		this->insertNode(c);
		
		TM_START(0,RW);
		TM_STORE(&vetor[l][c], 1);
		TM_COMMIT;
	}
}

void GraphStm::increaseEdge(int l, int c){
	if (l!=c){
		if(this->getVal(l,c)){
			int aux=0;
			TM_START(0,RW);
			aux= TM_LOAD(&vetor[l][c]);
			aux++;
			TM_STORE(&vetor[l][c], aux);
			TM_COMMIT;
		}
		else{
			this->changeEdge(l, c);
		}
	}
}

void GraphStm::decreaseEdge(int l, int c){
	if (l!=c){
		if(this->getVal(l,c)){
			int aux=0;
			TM_START(0,RW);
			aux= TM_LOAD(&vetor[l][c]);
			aux--;
			TM_STORE(&vetor[l][c], aux);
			TM_COMMIT;
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
//	cout<<"decreaseEdge executado.\n";
}

int GraphStm::getVal(int l, int c) const{
	int val=0;
	int aux=0;

	TM_START(0,RW);
	aux= TM_LOAD(&vetor[l][c]);
	if(aux){
		val=aux;
	}
	TM_COMMIT;

	return val;
}
