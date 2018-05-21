# Parallel Graph

Algoritmo que realiza inserções, remoções e buscas de forma paralela em um grafo.
Tem o objetivo de avaliar o desempenho de diferentes métodos de sincronização.

## Testes

Antes de compilar deve-se ajustar o size no `include/graph.hpp`.

Defina na função main dentro de `src/main.cpp` qual classe será usada para o teste.

**make** compila com tamanho da  matriz definida no `graph.hpp`, size indica tamanho
da matriz e a quantidade de nós.

Deve usar **make all** para compilar e **make clean** para desfazer.

### Para executar:

`./graph <-numero_de_thread>`

<-numero_de_thread> deverá  ser substituído pelo número de threads que deseja executar o código.

UFPel - IPPD 2015/2.
