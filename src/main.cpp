
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <mutex>
#include <atomic>
#include <graph.hpp>
#include <graphmutex.hpp>
#include <graphmutexgg.hpp>
#include <graphatomic.hpp>
#include <graphstm.hpp>

using namespace std;

//variavel de teste final
int executa=30000000;
int tam_thread;


//classes para teste:
GraphStm grid;
//GraphAtomic grid;
//GraphMutex grid;
//GraphMutexGG grid;
//Graph grid;

//mutex para vizualizar saida de teste
mutex musaida;

//executa as threads
void run(){
	int i, l, c;
	int saida=rand()%50;
	int chegada=rand()%50;

	//inicia teste da stm
	TM_INIT_THREAD;
	
	//escreve no grafo vertices iguais recebem valor 0
	for(i=0;i<executa/tam_thread;i++){
		l=rand()%50;
		c=rand()%50;
		grid.increaseEdge(l,c);
	}

	//retira no grafo vertices iguais recebem valor 0
	for(i=0;i<(executa/tam_thread)/2;i++){
		l=rand()%50;
		c=rand()%50;
		grid.decreaseEdge(l,c);
	}

	//efetua buscas no grafo
	for(i=0;i<executa/tam_thread;i++){
		l=rand()%50;
		c=rand()%50;
		grid.getVal(l,c);
	}
	

	//teste do dijkstra paralelo
	//long long int menor=grid.Dijkstra(saida, chegada);
	int dist=grid.getVal(saida, chegada);

	//saida para verificacao do teste
	//musaida.lock();
	//cout<<"Menor Caminho = " << menor << ".\n";
	//cout<<"Distancia dos " << saida << " e " << chegada << " e: "<< dist<<".\n-----\n";
	//musaida.unlock();

	//termina teste da stm
	TM_EXIT_THREAD;
}

int main(int argc, char *argv[]){
	int i;
	tam_thread=atoi(argv[1]);
	long long int tempo=(long long int)0;
	thread *td= new thread[tam_thread];

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();


	for(i=0;i<tam_thread;i++){
		td[i]= thread (run);
	}
	
	for(i=0;i<tam_thread;i++){
		td[i].join();
	}
	
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	cout<<"-------------\nTempo = "<<elapsed_seconds.count()<<"\n";

	return 0;
}