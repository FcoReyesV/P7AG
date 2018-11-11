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
    void PMX(int,int);
    void PbX();
    void ObX();
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
}

void Cruza::OX(int TamSub){
    int subc[poblacion][TamSub],sc,banH1,banH2,paux,inicio=2;
    int padreaux[poblacion][alelos-TamSub];
    bool isInH1, isInH2;

        //Primero se genera la subcadena de los hijos
    for(int i=0;i<poblacion-1;i++){
        sc=0;
        for(int j=0;j<alelos;j++){
            if(j>inicio && j<=inicio+TamSub){ 
                individuosEC[i][j]=individuosE[i][j];
                individuosEC[i+1][j]=individuosE[i+1][j];
                subc[i][sc]=individuosE[i][j];
                subc[i+1][sc++]=individuosE[i+1][j];
            }
            else{
                individuosEC[i][j]=0;
            }
        }
        i++;    
    }
    //Se busca la subcadena dentro del padre 2 y copiar en una nueva variable
    for (int i=0;i<poblacion-1;i++){
        banH1=0;
        banH2=0;
        isInH1=false;
        isInH2=false;
        for (int j=0;j<alelos;j++){ //recorrer alelo por alelo del P2 para ver si coincide con la subcadena
            for (int k=0;k<TamSub;k++){
                if (subc[i][k]==individuosE[i+1][j])
                    isInH1=true;
                if (subc[i+1][k]==individuosE[i][j])
                    isInH2=true;
            }
            if (!isInH1) //no hay repetido h1
                padreaux[i][banH1++]=individuosE[i+1][j];
           
            if (!isInH2) //no hay repetido h2
                padreaux[i+1][banH2++]=individuosE[i][j];

            isInH1=false;
            isInH2=false;      
       }
       i++;
       
    }
    //Una vez obtenidos los padres auxiliares sin las subcadenas, solo resta copiar al hijo individuosEC
    for (int i=0;i<poblacion-1;i++){
        paux=0;
        for (int j=0;j<alelos;j++){
            if (j<=inicio || j>inicio+TamSub){
                individuosEC[i][j]=padreaux[i][paux]; 
                individuosEC[i+1][j]=padreaux[i+1][paux++];     
            }
        }
        i++;
    } 

    //subcadena(2,TamSub,individuosEC,individuosE);

    //Imprimir padre aux
    /*cout<<endl<<"Padre aux"<<endl;
    for(int i=0;i<poblacion;i++){
        for(int j=0;j<alelos-TamSub;j++)
            cout<<" "<<padreaux[i][j];
        
        cout<<endl;
    }*/
    ImprimirRes(individuosE,individuosEC);
}


void Cruza::PMX(int pto1,int pto2){//Se eligen aleatoriamente dos puntos de cruza
    pto1--;
    pto2--;
    int TamSub=pto2-pto1;
    int subc[poblacion][TamSub],sc;
    bool isInH1, isInH2;

        //Primero se genera la subcadena de los hijos
    for(int i=0;i<poblacion-1;i++){
        sc=0;
        
        for(int j=0;j<alelos;j++){
            if(j>pto1 && j<=pto2){ 
                individuosEC[i][j]=individuosE[i+1][j];
                individuosEC[i+1][j]=individuosE[i][j];
                subc[i][sc]=individuosE[i+1][j];
                subc[i+1][sc++]=individuosE[i][j];
            }
            else{
                individuosEC[i][j]=0;
            }
        }
        i++;    
    }
    
    //Antes del primer punto copiamos, si ya existe entonces no lo pones, dejas el espacio vacio
    for (int i=0;i<poblacion-1;i++){
        isInH1=false;
        isInH2=false;
        for (int j=0;j<alelos;j++){
            for(int k=0;k<TamSub;k++){ //Comparamos alelo por alelo, si es que ya existe la subc
                    if (subc[i][k]==individuosE[i][j])
                        isInH1=true;
                    if (subc[i+1][k]==individuosE[i+1][j])
                        isInH2=true;
            }
            if(j<=pto1 || j>pto2){
                if (!isInH1) //no hay repetido h1 del p1
                    individuosEC[i][j]=individuosE[i][j];
                else
                    individuosEC[i][j]=0;
                 
                if (!isInH2) //no hay repetido h2
                   individuosEC[i+1][j]=individuosE[i+1][j];
                else
                    individuosEC[i+1][j]=0;   
            }
            isInH1=false;
            isInH2=false;
        } //llave de alelos
        i++;
    }

    for (int i=0;i<poblacion-1;i++){
        for (int j=0;j<alelos;j++){
            for(int k=0;k<TamSub;k++){ //Verificamos si el alelo de la subc existe en individuosEC
                for(int l=0;l<alelos;l++){
                    
                    if(subc[i+1][k]==individuosEC[i][l]){
                        subc[i+1][k]=-1;
                    }
                    if(subc[i][k]==individuosEC[i+1][l]){
                        subc[i][k]=-1;
                    }
                }
            }
            if(j<=pto1 || j>pto2){ //Por ultimo rellenamos con los numeros 
                if(individuosEC[i][j]==0){
                    for(int m=0;m<TamSub;m++){
                        if(subc[i+1][m]!=-1){
                            individuosEC[i][j]=subc[i+1][m];
                            subc[i+1][m]=-1;
                            break;
                        }
                    }
                }
                if(individuosEC[i+1][j]==0){
                    for(int m=0;m<TamSub;m++){
                        if(subc[i][m]!=-1){
                            individuosEC[i+1][j]=subc[i][m];
                            subc[i][m]=-1;
                            break;
                        }
                        
                    }
                }
            }
        } //llave de alelos
        i++;
    }

    //Imprimir padre aux
    /*cout<<endl<<"Padre aux"<<endl;
    for(int i=0;i<poblacion;i++){
        for(int j=0;j<alelos-TamSub;j++)
            cout<<" "<<padreaux[i][j];
        
        cout<<endl;
    }*/

    
    ImprimirRes(individuosE,individuosEC);
}

void Cruza::PbX(){
    int indices[]={1,4,6,9},iban,banH1,banH2;
    int subc[poblacion][4],padreaux[poblacion][alelos-4];
    bool isInH1,isInH2;
           
    //Primero producimos un hijo tomando las posiciones indicadas
    for(int i=0;i<poblacion-1;i++){
        iban=0;
        banH1=0;
        banH2=0;
        isInH1=false;
        isInH2=false; 
        for(int j=0;j<alelos;j++){
            if(indices[iban]==j){
                individuosEC[i][j]=individuosE[i][j];
                individuosEC[i+1][j]=individuosE[i+1][j];
                subc[i][iban]=individuosE[i][j];
                subc[i+1][iban++]=individuosE[i+1][j];
            }else{
                individuosEC[i][j]=0;
                individuosEC[i+1][j]=0;
            }
        }
        //Buscamos las subcadenas en el padre 2 y quitamos los valores 
        for(int j=0;j<alelos;j++){
             for (int k=0;k<4;k++){
                if (subc[i][k]==individuosE[i+1][j])
                    isInH1=true;
                if (subc[i+1][k]==individuosE[i][j])
                    isInH2=true;
            }
            if (!isInH1) //no hay repetido h1
                padreaux[i][banH1++]=individuosE[i+1][j];
           
            if (!isInH2) //no hay repetido h2
                padreaux[i+1][banH2++]=individuosE[i][j];

            isInH1=false;
            isInH2=false;      
            
        }

        i++;
    }

    //Al final solo copiamos lo del P2' en hijo 1 y de igual manera con P1' en hijo 2

    for(int i=0;i<poblacion-1;i++){
        banH1=0;
        banH2=0;
        for(int j=0;j<alelos;j++){
            if(individuosEC[i][j]==0){
                individuosEC[i][j]=padreaux[i][banH1++];
            }
            if(individuosEC[i+1][j]==0){
                individuosEC[i+1][j]=padreaux[i+1][banH2++];
            }
        }
        i++;
    }

    ImprimirRes(individuosE,individuosEC);
}

void Cruza::ObX(){
    int indices[]={1,4,6,9},iban,banH1,banH2;
    int subc[poblacion][4],padreaux[poblacion][alelos-4];
    bool isInH1,isInH2;
           
    //Primero producimos un hijo tomando las posiciones indicadas
    for(int i=0;i<poblacion-1;i++){
        iban=0;
        banH1=0;
        banH2=0;
        isInH1=false;
        isInH2=false; 
        for(int j=0;j<alelos;j++){
            if(indices[iban]==j){
                //individuosEC[i][j]=individuosE[i][j];
                //individuosEC[i+1][j]=individuosE[i+1][j];
                subc[i][iban]=individuosE[i][j];
                subc[i+1][iban++]=individuosE[i+1][j];
            }
        }
        //Buscamos las subcadenas en el padre 2 y quitamos los valores 
        for(int j=0;j<alelos;j++){
             for (int k=0;k<4;k++){
                if (subc[i][k]==individuosE[i+1][j])
                    isInH1=true;
                if (subc[i+1][k]==individuosE[i][j])
                    isInH2=true;
            }
            if (!isInH1){ //no hay repetido h1
                individuosEC[i][j]=individuosE[i+1][j];
            }else{
                individuosEC[i][j]=0;
            }
           
            if (!isInH2){ //no hay repetido h2

                 individuosEC[i+1][j]=individuosE[i][j];
            }else{
                individuosEC[i+1][j]=0;
            }

            isInH1=false;
            isInH2=false;      
            
        }

        i++;
    }
    

    //Al final solo copiamos lo del P2' en hijo 1 y de igual manera con P1' en hijo 2

    for(int i=0;i<poblacion-1;i++){
        banH1=0;
        banH2=0;
        for(int j=0;j<alelos;j++){
            if(individuosEC[i][j]==0){
                individuosEC[i][j]=subc[i][banH1++];
            }
            if(individuosEC[i+1][j]==0){
                individuosEC[i+1][j]=subc[i+1][banH2++];
            }
        }
        i++;
    }
    ImprimirRes(individuosE,individuosEC);

    
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
        cout<<"1.- Order Crossover"<<endl<<"2.- Partially Mapped Crossover"<<endl<<"3.- Position-based Crossover"<<endl<<"4.- Order-based Crossover"<<endl<<"5.- Salir"<<endl;
        
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
                int pto1, pto2;
                cout<<"Partially Mapped Crossover"<<endl;
                cout<<"Escribe el punto de cruza 1: ";
                cin>>pto1;
                cout<<"Escribe el punto de cruza 2: ";
                cin>>pto2;
                c.PMX(pto1,pto2);
                break;
            case 3:
                system("cls");
                cout<<"Position-based Crossover"<<endl;
                cout<<"Los indices tomados son: 1,4,6,9"<<endl;
                c.PbX();
                break;
            case 4:
                system("cls");
                cout<<"Order-based Crossover"<<endl;
                cout<<"Los indices tomados son: 1,4,6,9"<<endl;
                c.ObX();
                break;
            case 5:
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


