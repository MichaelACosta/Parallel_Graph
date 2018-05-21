#include <iostream>
#include <queue>
#include <graph.hpp>


Graph::Graph(){
	int i, c;
	for (i = 0; i < size; ++i){
		flag[i]=0;
	}
	for (i = 0; i < size; ++i){
		for (c = 0; c < size; ++c){
			vetor[i][c]=0;
		}
	}
//	cout << "Grafo criado.\n" << size << "\n";
}

void Graph::insertNode(int node){
	if(this->testNode(node)){
		flag[node]=1;
	}
}

void Graph::deletNode(int node){
	if(this->testNode(node)){
		flag[node]=0;
	}
}

bool Graph::testNode(int node)const{
	bool ret;
	if(flag[node]){
		ret= true;
	}
	else{
		ret= false;
	}
	return ret;
}

void Graph::changeEdge(int l, int c){
	if (l!=c){
		this->insertNode(l);
		this->insertNode(c);
		
		vetor[l][c]=1;
	}
}

void Graph::increaseEdge(int l, int c){
	if (l!=c){
		if(vetor[l][c]){
			vetor[l][c]++;
		}
		else{
			this->changeEdge(l, c);
		}
	}
}

void Graph::decreaseEdge(int l, int c){
	if (l!=c){
		if(this->getVal(l,c)){
			vetor[l][c]--;
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

//utilizar o mutex do increase
int Graph::getVal(int l, int c)const{
	int val=0;
	if(vetor[l][c]){
		val=vetor[l][c];
	}
	return val;
}


int Graph::Dijkstra(int inicio, int fim) const{
	int dist[size], adj[size], i, j;
	bool visitados[size];
	priority_queue < int > lista;

	if(testNode(inicio) && testNode(fim)){
		//inicializa valores e listas	
		for (i = 0; i < size; i++){
			adj[i]=infinito;
			dist[i]=infinito;
			visitados[i]=false;
		}
		dist[inicio]=0;
		lista.push(inicio);

		//busca caminhos na lista de prioridade
		while(!lista.empty()){
			int u=lista.top(); //pega topo da lista
			lista.pop(); //remove da lista

			//verifica se nodo não foi visitado
			if(visitados[u]==false){
				visitados[u]=true; //marca visitado

				//reinicia lista de adj e pega os vetores adjacentes a u
				j=0;
				for (i = 0; i < size; i++){
					adj[i]=infinito;
					if(this->getVal(u,i)!=0){ //vetor[u][i]
						adj[j]=i;
						j++;
					}
				}

				//percorre lista de adj
				i=0;
				while((adj[i]<infinito)&&(i<size)){
					int custo=this->getVal(u, adj[i]); //vetor[u][adj[i]];

					//relaxa (u,v)
					if(dist[adj[i]] > (dist[u]+custo)){
						dist[adj[i]]=dist[u]+custo;
						lista.push(adj[i]);
					}
					i++;
				}

			}

		}
		return dist[fim];
	}
	return 0;
}

Graph::~Graph(){
//	delete []vetor;
//	delete []flag;
//	cout << "Destrutor executado.\n";
}