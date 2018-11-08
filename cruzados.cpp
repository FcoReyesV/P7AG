#include <iostream>
#include <stdio.h>     
#include <stdlib.h>    
#include <time.h>   
#include <math.h>

class Cruza{
private:
    int poblacion;
    int alelos;
    int **individuosE;
    int **individuosB;
    int **individuosEC; //Binario cruza
public:
    Cruza(int, int);
    void CreaIndividuos();
    bool CheckRep(int, int , int**);
    void ImprimirRes(int **,int**);
    void LiberarMemoria();
    void OX(int);
    void subcadena(int ,int ,int **, int **);
};
using namespace std;

Cruza::Cruza(int ipoblacion,int ialelos){
    poblacion = ipoblacion;
    alelos = ialelos;
    individuosE = new int*[poblacion]; // se debe liber la memoria dinamica delete [] cadena_dinamica;  cadena_dinamica = NULL;
    individuosB = new int*[poblacion];
    individuosEC = new int*[poblacion];

    for(int i=0;i<poblacion;i++){
        individuosE[i] = new int[alelos];
        individuosB[i] = new int[alelos];
        individuosEC[i] = new int[alelos];
    }
}

void Cruza::CreaIndividuos(){
    int random;
    for(int i=0;i<poblacion;i++){
        for(int j=0;j<alelos;j++){
            do
                random =  rand() % alelos + 1;
            while(CheckRep(random,i,individuosE));
            individuosE[i][j] = random;
            individuosEC[i][j] = 0;
        }
       
        //cout<<"Individuo: "<<individuosE[i]<<endl;
        
    }
  ImprimirRes(individuosE,individuosEC);
}

void Cruza::OX(int TamSub){
    int subc[poblacion][TamSub],ban=0,ban2;
    int padreaux[poblacion][alelos];


    subcadena(2,TamSub,individuosEC,individuosE);

    /*Imprimir padre aux
    cout<<endl<<"Padre aux"<<endl;
    for(int i=0;i<poblacion;i++){
        for(int j=0;j<alelos-TamSub;j++)
            cout<<" "<<padreaux[i][j];
        
        cout<<endl;
    }*/
    ImprimirRes(individuosE,individuosEC);
}

void Cruza::BorrarSubCadena(int **ArrCruza,int **ArrOrig){
    for(int i=0;i<poblacion-1;i++){
        for(int j=0;j<alelos;j++){
            
        }
        i++;    
    }

}

void Cruza::SubCadena(int inicio,int tam,int **ArrCruza, int **ArrOrig){
    for(int i=0;i<poblacion-1;i++){
        for(int j=0;j<alelos;j++){
            if(j>inicio && j<=inicio+tam){ //Copiamos la subcadena al hijo 1
                ArrCruza[i][j]=ArrOrig[i][j];
                ArrCruza[i+1][j]=ArrOrig[i+1][j];
            }
            else{
                ArrCruza[i][j]=0;
            }
        }
        i++;    
    }
}



void Cruza::ImprimirRes(int **arr, int **arr2){
    for(int i=0;i<poblacion;i++){
        cout<<i+1<<" | ";
        for(int j=0;j<alelos;j++)
            cout<<" "<<arr[i][j];
        cout<<" | ";
        for(int j=0;j<alelos;j++)
            cout<<" "<<arr2[i][j];
        cout<<endl;
    }
}

void Cruza::LiberarMemoria(){
    for(int i=0;i<poblacion;i++){
        delete []individuosE[i];
        delete []individuosB[i];
        delete []individuosEC[i];
    }
    
    delete []individuosE;
    delete []individuosB;
    delete []individuosEC;
}

bool Cruza::CheckRep(int n, int fila, int **num)
{
    for(int i=0; i<alelos; i++){
        if(n == num[fila][i])
                return true;
    }
    return false;
}


int main(int argc, char const *argv[])
{
    char opc;
    
    int indiv, alel,opc1;
    srand(time(NULL));
    do{
    
        cout<<"Metodos de cruza para permutaciones"<<endl;
        cout<<"1.- Order Crossover"<<endl<<"2.- Partially Mapped Crossover"<<endl<<"3.- Position-based Crossover"<<endl<<"4.- Order-based Crossover"<<endl<<"5.- Cycle Crossover"<<"6.- Salir"<<endl;
        
        cout<<"Escribe el numero de individuos: ";
        cin>>indiv;
        cout<<endl<<"Escribe el numero de alelos: ";
        cin>>alel;
        
        Cruza c(indiv, alel);
        c.CreaIndividuos();
        cout<<endl<<"Escribe una opcion de cruza: ";
        cin>>opc1;
        switch(opc1){
            case 1:
                system("cls");
                int tamsub;
                cout<<"Order Crossover"<<endl;
                cout<<"Escribe el tamanio de la subcadena: ";
                cin>>tamsub;
                c.OX(tamsub);
                
                break;
            case 2:
                system("cls");
                cout<<"Partially Mapped Crossover"<<endl;
                break;
            case 3:
                system("cls");
                cout<<"Position-based Crossover"<<endl;
                break;
            case 4:
                system("cls");
                cout<<"Order-based Crossover"<<endl;
                break;
            case 5:
                system("cls");
                cout<<"Cycle Crossover"<<endl;
                break;
            case 6:
                exit(0);
                break;
        }
        c.LiberarMemoria();
        cout<<"Deseas volver al menu?(s/n): "<<endl;
        cin>>opc;
        
        system("cls");
    }while(opc=='s');   
    cout<<endl;
   

    
    return 0;
}


