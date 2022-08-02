#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>


using namespace std;

class Grafo
{
	int vertices;
	list<int> * adj;
	
public:
	Grafo(int vertices); // construtor
	void adicionarArestaEContador(int vertice_1, int vertice_2); // função que adiciona aresta no grafo
	int grauDeSaida(int vertice);
	bool existeVizinho(int vertice_1, int vertice_2);
	bool grauPar();
	bool euler();
	void mostraGrafo();
};

Grafo::Grafo(int vertices){
	this->vertices = vertices;
	adj = new list<int>[vertices]; // cria as listas
}

void Grafo::adicionarArestaEContador(int vertice_1, int vertice_2){
	list<int>::iterator it;
	it = adj[vertice_1].end();
	adj[vertice_1].push_back(vertice_2); 
	adj[vertice_1].push_back(0);
    
	
}

// int Grafo ::grauDeSaida(int vertice){
// 
// 	bool Grafo::euler(){
// 	int *aresta_inicial = adj[0];
// 	return 0;
// }return adj[vertice].size(); // retornando o tamanho da lista que corresponde a quantidade de vizinhos
// }
// 
bool Grafo::existeVizinho(int vertice_1, int vertice_2){
	if(find(adj[vertice_1].begin(), adj[vertice_1].end(), vertice_2)!= adj[vertice_1].end())
		return true;
	return false;
}

bool Grafo::grauPar(){
 	int cont = 0;
 	for(int i = 0;i< 8;i++){
 		if((adj[i].size())%2 == 0){
			cont++;
	 	 }
 	 }
	 if(cont == 8)
		 return true;
	 return false;
 } // quando mudar para arquvi tem q modificar o for

void Grafo::mostraGrafo(){
	list<int>::iterator oi;
	cout << "   A-C-A-C\n";
	for(int i = 1; i < 8;i++){
		
		cout<<i<<": ";
		for(oi = adj[i].begin();oi != adj[i].end(); oi++ ){
			cout << *oi<<" ";
		}
	
		cout << "\n";
	}
	
	cout << "   -------\n";
	
}

	
int main(void){
	
	Grafo grafo(8);
	grafo.adicionarArestaEContador(1,4);
	grafo.adicionarArestaEContador(1,5);
	grafo.adicionarArestaEContador(2,5);
	grafo.adicionarArestaEContador(2,6);
	grafo.adicionarArestaEContador(3,6);
	grafo.adicionarArestaEContador(3,7);
	grafo.adicionarArestaEContador(4,1);
	grafo.adicionarArestaEContador(4,5);
	grafo.adicionarArestaEContador(5,2);
	grafo.adicionarArestaEContador(5,6);
	grafo.adicionarArestaEContador(6,3);
	grafo.adicionarArestaEContador(6,7);
	grafo.adicionarArestaEContador(7,6);
	grafo.adicionarArestaEContador(7,3);
	grafo.mostraGrafo();

	return 0;
}
	
	
	
	
	// ifstream arquivoE;
	// string linha;
	// float matriz[][];
	// arquivoE.open("C:/Users/mathe/OneDrive/Área de Trabalho/teg/entrada.txt");
	// if(arquivoE.is_open()){
	// 	while(getline(arquivoE,linha)){
	// 		cout << linha << endl;
	// 	}
	// }else{
	// 	cout << "Não foi possivel abrir o arquivo" << endl;
	// }
	// leitura em arquivo
	
	
	// int Matriz_Grafo[7][7] = {
	// 	
	// {0,0,0,1,1,0,0},
	// {0,0,0,0,1,1,0},
	// {0,0,0,0,0,1,1},
	// {1,0,0,1,0,0,0},
 //    {0,1,0,0,0,1,0},
 //    {0,0,1,0,0,0,1},
 //  	{0,0,1,0,0,0,1},
 //  		
	// };
	// 
