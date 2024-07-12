#include<iostream>
#include<string>
#include<cstdlib>
#include <fstream>
#include <time.h>
#include <fstream>
#include <random>
using namespace std;

const int dimension = 32;                         //Dimension of forest
const int repetitions = 1;                     //number of times it iterates
const int Dshow = 100;                             //Max Dimension it shows per screen, careful because it may collapse your screen
const int precision = 100000;                       //of the RNG
const int cornerPercentage = 10;                     //of the cornersize
const int clusters = 5;                             //it tries to percolate

const double initialProbability = 0.599;            //initial probabiity
const double finalProbability   = 0.675;            //final probability
const double increment  = 0.005;                    //between probabilites
const bool recorrido = false;                        //if false; only one probability. if true, from initial to end

const bool isofena_inicial = false;                  //show initial forest
const bool isofena_quemado = true;                  //show final forest

const bool showFinalData = false;                     //show data per cycle
const bool generateFile = false;                      //generate a file to visualise the forest, cost efficienty
const bool generateFileInitialGeneration = false;     //same but including the generation part
const bool randomFill = true;                         // if true, RND generation of forest for each cell. if false randomly generates until the probability

const bool octogonal = false;                         // octogonal matrix, 6 conexiones en vez de 4 por arbol
const bool hexagonal = false;                         //hexagonal matrix, 6 conexiones en vez de 4 por arbol
const bool triangular = false;                        //triangular matrix, 6 conexiones en vez de 4 por arbol

ofstream cad;                                       //output files
ofstream res;
ofstream heatm;
ofstream finalResult;
ofstream outhisto;
mt19937_64 mt;

int fillForest(double probability){      //unused function to fill the forest with other RNG generation, increasing but better RNG generation
    double random;
    random = mt()%precision;
    if(random < probability*precision){
        return 1;
    }
    else{
        return 0;
    }
}

int main(void){
    cout.flush();
    srand((unsigned) time(nullptr));
    cout  << "\n--------- Start of Program ---------\n";

    int i;
    int j;
    int r1;
    int r2;
    double trees;
    int size;  //used integers 
    int cornerSize;
    int cornerNumber;
    int resto;
    int limit;
    int oct;
    int add;
    double histograma[101];
    for(int i = 1; i < 101; i++){       //to generate the histogram
        histograma[i] = 0;
    }

    bool extraForm = false;
    if((hexagonal)||(octogonal)) extraForm = true;
    if(extraForm)size = 3 * dimension;
    else size = dimension;
    int emp = 1;
    int ter = size - 1;
    
    int posicion;
    int forest[size][size];
    int propagatedTrees[size][size];
    int cycles;
    int heatmap[size][size];
    double totalPercolations = 0;
    double prob;
    double burnedTrees;
    double numero;
    double randomNumber;
    double arbolesQuemados;
    double generatedPercentage = 0;
    double burnedPercentage = 0;
    double percolatedPercentage;
    double elapsedTime;
    double burnedPercolatedPercentage = 0;
    bool justPropagated;
    bool doesItPercolate;
    bool burnedCorners[8];

    if(octogonal) limit = 2 * dimension;
    else if(hexagonal) limit = dimension + 1;
    else limit = dimension;

    if(octogonal) cornerNumber = 8;
    else if(hexagonal) cornerNumber = 6;
    else if(triangular) cornerNumber = 3;
    else cornerNumber = 4;

    clock_t startloop = clock();
    res.open("Plot.txt");
    if(generateFile){cad.open("Fich.txt");}                  //fichero apertura
    finalResult.open("framefinal.txt");                     //to generate only the final frame of the forest
    res << "# Generation Probabilty vs Percolating Percentage. L: " << dimension << ". Cycles: " << repetitions << endl;
    outhisto.open("histogramdata.txt");


    if(!recorrido){
        cycles = 1;
        prob = initialProbability;
    }
    else{
        cycles = (finalProbability - initialProbability) / increment + 1;
        prob = initialProbability;
    }
    
    for(int p = 0; p < cycles; p++){
        totalPercolations = 0;
        burnedPercolatedPercentage = 0;
        for(int l = 0; l < repetitions; l++){
            doesItPercolate = false;
            for (i = 0; i < size ; i++) {    //initiate matrix
                for (j = 0; j < size; j++) {
                    propagatedTrees[i][j] = 0;
                    forest[i][j] = 0;
                }
            }

            trees = 0; //generate random forest
            if(randomFill){
                if(extraForm){ 
                    if(octogonal) resto = dimension - 1;
                    else resto = 0;
                    for (i = 1; i <= 3 * dimension - 2 ; i++) {
                        if(i <= dimension){
                            for (j = 1; j <= i + resto; j++) {
                                //randomNumber = mt()%precision;
                                randomNumber = (rand() % precision);
                                if(randomNumber <= precision * prob){
                                    forest[i][j] = 1;
                                    trees++;
                                }
                                else{
                                    forest[i][j] = 0;
                                }
                            }
                        }
                        else if(i <= 2 * dimension - 2 ){
                            for (j = 1; j <= dimension - (i + 1) % 2 + resto; j++) {
                                randomNumber = (rand() % precision);
                                if(randomNumber <= precision * prob){
                                    forest[i][j] = 1;
                                    trees++;
                                }
                                else{
                                    forest[i][j] = 0;
                                }
                            }
                        }
                        else{
                            for (j = 1; j <= 3 * dimension - i - 1 + resto  ; j++) {
                                randomNumber = (rand() % precision);
                                if(randomNumber <= precision * prob){
                                    forest[i][j] = 1;
                                    trees++;
                                }
                                else{
                                    forest[i][j] = 0;
                                }
                            }
                        }
                    }
                }
                else{ //randomFill square or triangular
                    for (i = 0; i < dimension ; i++) {
                        if(triangular) resto = i;
                        else resto = 0;
                        for (j = 0; j < dimension - resto; j++) {
                            randomNumber = (rand() % precision);
                            if (randomNumber <= precision * prob) {
                                forest[i][j] = 1;
                                trees++;
                            } else {
                                forest[i][j] = 0;
                            }

                            if((generateFile)&&(forest[i][j] != 0)&&(generateFileInitialGeneration)){
                                for (int i1 = 0; i1 <= 2 * dimension + 3 ; i1++) {
                                    cad << "4";
                                    if(i1 != 2 * dimension + 3){cad << ",";}
                                }
                                cad << endl;
                                for (int i1 = 0; i1 < dimension ; i1++) {
                                    cad << "4,4,";
                                    for (int j1 = 0; j1 < dimension; j1++) {
                                        cad << forest[i1][j1]<< ","<< forest[i1][j1]<< ",";
                                    }
                                    cad << "4,4\n";
                                }
                                for (int i1 = 0; i1 <= 2 * dimension + 3 ; i1++) {
                                    cad << "4";
                                    if(i1 != 2 * dimension + 3){cad << ",";}
                                }
                                cad << endl << endl;
                            }

                        }
                    }
                }
            }
            else{
                for (i = 0; i < dimension ; i++) {
                    for (j = 0; j < dimension; j++) {
                        forest[i][j] = 0;
                    }
                }
                while(trees/(dimension * dimension) < prob){
                    r1 = (rand() % dimension);
                    r2 = (rand() % dimension);
                    if(forest[r1][r2] != 1){
                        forest[r1][r2] = 1;
                        trees++;
                    }
                }
            }
    
            if((isofena_inicial)&&(dimension < Dshow)){  //show in screen the forest
                cout << "\n Initial forest \n";
                if(octogonal) {
                    add = dimension - 1;
                }
                else if(hexagonal) {
                    add = 0;
                }
                else if(!extraForm){
                    add = size/2 + 1;
                    emp = 0;
                    ter = size;
                }
                else add = 0;

                for (i = 0; i <= size + 2*add + 2; i++) {cout << "\033[1;100m \033[0m";}
                cout << endl;

                for (i = emp; i < ter; i++) {
                    cout << "\033[1;100m  \033[0m";
                    if((triangular)&&(!extraForm)){
                        for (j = 0; j < i; j++) {
                            cout << "\033[1;100m \033[0m";
                        }
                        resto = i;
                    }
                    else resto = 0;
                    if(extraForm){ //HEXAGONAL U OCTOGONAL
                        if(i <= dimension){ //triangulo inicial
                            for (j = 1; j <= size/2 - i; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                            for (j = 1; j <= i + add; j++) {
                                if(forest[i][j] == 0) cout << "\033[1;107m  \033[0m";
                                else cout << "\033[1;102m  \033[0m";
                            }
                            for (j = 1; j <= size/2 - i; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                        }
                        else if(i <= 2 * dimension - 2 ){         //parte central
                            for (j = 0; j <= dimension / 2 - i % 2; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                            for (j = 1; j <= dimension - (i + 1) % 2 + add; j++) {
                                if(forest[i][j] == 0) cout << "\033[1;107m  \033[0m";
                                else cout << "\033[1;102m  \033[0m";
                            }
                            for (j = 0; j <= dimension / 2 - i % 2 ; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                        }
                        else{       //triangulo final
                            for (j = 1; j <= i - dimension - (dimension - 1) / 2 ; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                            for (j = 1; j < 3 * dimension - i + add; j++) {
                                if(forest[i][j] == 0) cout << "\033[1;107m  \033[0m";
                                else cout << "\033[1;102m  \033[0m";
                            }
                            for (j = 1; j <= i - dimension - (dimension - 1) / 2 ; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                        }
                    }
                    else{ //triangular o cuadrada
                        for (j = 0; j < dimension - resto; j++) {
                            if(forest[i][j] == 0)                            cout << "\033[1;107m  \033[0m";
                            else cout << "\033[1;102m  \033[0m";
                        }
                    }
                    if((triangular)&&(!extraForm)){
                        for (j = 0; j < i; j++) {
                            cout << "\033[1;100m \033[0m";
                        }
                    }
                    cout << "\033[1;100m  \033[0m\n";
                }

                for (i = 0; i <= size + 2*add + 2; i++) {cout << "\033[1;100m \033[0m";}
            }
            //random burned tree
            burnedTrees = 1;
            for(int m = 0; m < clusters; m++){
                r1 = (rand()%size);
                r2 = (rand()%size);
                while((forest[r1][r2] == 0)&&(prob != 0)){ //elegir un hueco donde hay un arbol, aleatorio
                    r1 = (rand()%size);
                    r2 = (rand()%size);
                }
                forest[r1][r2] = 2;
                burnedTrees++;
                justPropagated = true;
                while (justPropagated) {
                    justPropagated = false;
                    if((l == 0)&&(generateFile)){//si se genera el archivo, para que sea más bonito al representarse. si es false, mejora la representación
                        if(!extraForm){
                            for (i = 0; i < 2 * dimension + 3 ; i++) {
                                cad << "4";
                                if(i != 2 * dimension + 2){cad << ",";}
                            }
                            cad << endl;
                            for (i = 0; i < dimension ; i++) {
                                if(triangular) resto = i;
                                else resto = 0;
                                cad << "4,4,";
                                if(triangular){
                                    for (j = 0; j < i; j++) {
                                        cad << "4,";
                                    }
                                }
                                for (j = 0; j < dimension - resto; j++) {
                                    cad << forest[i][j]<< ","<< forest[i][j]<< ",";
                                }
                                if(triangular){
                                    for (j = 0; j < i; j++) {
                                        cad << "4,";
                                    }
                                }
                                cad << "4\n";
                            }
                            for (i = 0; i < 2 * dimension + 3 ; i++) {
                                cad << "4";
                                if(i != 2 * dimension + 2){cad << ",";}
                            }
                        }

                        if(extraForm){
                            if(octogonal) oct = dimension - 1;
                            else oct = 0;
                            for (i = 0; i <= size + 2*oct; i++) {
                                cad << "4";
                                if(i != size + 2*oct) cad << ",";
                            }
                            cad << endl;
                            for (i = 1; i < size - 1 ; i++) {
                                cad << "4,"; //marron inicial
                                if(i <= dimension){ //primer triangulo
                                    for (j = 1; j <= size/2 - i; j++) {
                                        cad << "4,";
                                    }
                                    for (j = 1; j <= i + oct; j++) {
                                        cad << forest[i][j] << ","<< forest[i][j]<< ",";
                                    }
                                    for (j = 1; j <= size/2 - i; j++) {
                                        cad << "4,";
                                    }
                                }

                                else if(i <= 2 * dimension - 2 ){ //parte central
                                    for (j = 0; j <= dimension / 2 - i % 2 ; j++) {
                                        cad << "4,";
                                    }
                                    for (j = 1; j <= dimension - (i + 1) % 2 + oct; j++) {
                                        cad << forest[i][j]<< ","<< forest[i][j]<< ",";
                                    }
                                    for (j = 0; j <= dimension / 2 - i % 2 ; j++) {
                                        cad << "4,";
                                    }
                                }
                                else{//segundo triangulo
                                    for (j = 1; j <= i - dimension - (dimension - 1) / 2 ; j++) {
                                        cad << "4,";
                                    }
                                    for (j = 1; j < 3 * dimension - i + oct; j++) {
                                        cad << forest[i][j]<< ","<< forest[i][j] << ",";
                                    }
                                    for (j = 1; j <= i - dimension - (dimension - 1) / 2 ; j++) {
                                        cad << "4,";
                                    }
                                }
                                cad << "4\n"; //marron final
                            }

                            for (i = 0; i <= size + 2*oct; i++) {
                                cad << "4";
                                if(i != size +2*oct) cad << ",";
                            }
                        }
                        cad << endl<< endl;
                    }
                    for (i = 0; i < size ; i++) { //forest propagation
                        for (j = 0; j < limit; j++) {

                            if((forest[i][j] == 2) && (propagatedTrees[i][j] == 0) && (generateFile)){ //si genera archivo
                                justPropagated =  true;
                                forest[i][j]++;
                                if((forest[i-1][j] == 1)&&(i > 0)    ){forest[i-1][j] = 2; propagatedTrees[i - 1][j] = 1; burnedTrees++;}
                                if((forest[i][j-1] == 1)&&(j > 0)    ){forest[i][j-1] = 2; propagatedTrees[i][j - 1] = 1; burnedTrees++;}
                                if((forest[i+1][j] == 1)&&(i < size - 1)){forest[i+1][j] = 2; propagatedTrees[i + 1][j] = 1; burnedTrees++;}
                                if((forest[i][j+1] == 1)&&(j < size - 1)){forest[i][j+1] = 2; propagatedTrees[i][j + 1] = 1; burnedTrees++;}
                                if((triangular)&&(!extraForm)){ //triangular solo
                                    if((forest[i-1][j+1] == 1)&&(i > 0)){forest[i-1][j+1] = 2; propagatedTrees[i - 1][j + 1] = 1; burnedTrees++;} //diagonal superior
                                    if((forest[i+1][j-1] == 1)&&(j > 0)){forest[i+1][j-1] = 2; propagatedTrees[i + 1][j - 1] = 1; burnedTrees++;} //diagonal inferior
                                }
                                if((((i > dimension - 1) && (i < 2 * dimension) && (i % 2 == 0)) || (i > 2 * dimension - 1)) && (extraForm)){ //diagonal superior derecha
                                    if((forest[i-1][j+1] == 1)&&(i > 0)){forest[i-1][j+1] = 2; propagatedTrees[i - 1][j + 1] = 1;  burnedTrees++;}
                                }
                                if((((i > dimension - 1) && (i < 2 * dimension) && ((i + 1) % 2 == 0)) || (i < dimension)) && (extraForm)){//diagonal superior izquierda
                                    if((forest[i-1][j-1] == 1)&&(i > 0)&&(j > 0)){forest[i-1][j-1] = 2; propagatedTrees[i - 1][j - 1] = 1;  burnedTrees++;}
                                }
                                if(((i < dimension) || ((i > dimension - 1) && (i < 2 * dimension) && (i % 2 == 0))) && (extraForm)){ //diagonal inferior derecha
                                    if(forest[i+1][j+1] == 1){forest[i+1][j+1] = 2; propagatedTrees[i + 1][j + 1] = 1;  burnedTrees++;}
                                }
                                if(((i > 2 * dimension - 1) || ((i > dimension - 1) && (i < 2 * dimension) && ((i + 1) % 2 == 0))) && (extraForm)){  //diagonal inferior izquierda
                                    if((forest[i+1][j-1] == 1)&&(j > 0)){forest[i+1][j-1] = 2; propagatedTrees[i + 1][j - 1] = 1;  burnedTrees++;}
                                }

                            }

                            if((forest[i][j] == 2)&&(!generateFile)){ //si no genera archivo
                                justPropagated =  true;
                                forest[i][j]++;              
                                if((i > 0)&&forest[i-1][j] == 1)    {forest[i-1][j] = 2; burnedTrees++;} //vertical
                                if((i < size - 1)&&(forest[i+1][j]  == 1))              {forest[i+1][j] = 2; burnedTrees++;} //vertical
                                if((j > 0)&&(forest[i][j-1] == 1)    ){forest[i][j-1] = 2; burnedTrees++;} //horizontal
                                if((j < size - 1)&&(forest[i][j+1]  == 1))              {forest[i][j+1] = 2; burnedTrees++;} //horizontal                            
                                if((triangular)&&(!extraForm)){ //triangular solo
                                    if((i > 0)&&(forest[i-1][j+1] == 1)){forest[i-1][j+1] = 2;  burnedTrees++;} //diagonal superior
                                    if((j > 0)&&(forest[i+1][j-1] == 1)){forest[i+1][j-1] = 2;  burnedTrees++;} //diagonal inferior
                                }
                                if((i < dimension) && extraForm){ //Triangulo Superior
                                    if((i > 0)&&(j > 0)&&(forest[i-1][j-1] == 1)){forest[i-1][j-1] = 2;  burnedTrees++;} //diagonal superior
                                    if(forest[i+1][j+1] == 1)                    {forest[i+1][j+1] = 2;  burnedTrees++;} //diagonal inferio
                                }
                                if((i > 2 * dimension - 1) && extraForm){ //Triangulo Inferior
                                    if((i > 0)&&(forest[i-1][j+1] == 1)){forest[i-1][j+1] = 2;  burnedTrees++;} //diagonal superior
                                    if((j > 0)&&(forest[i+1][j-1] == 1)){forest[i+1][j-1] = 2;  burnedTrees++;} //diagonal inferio
                                }
                                if((i > dimension - 1) && (i < 2 * dimension) && (i % 2 == 0 ) && extraForm){ //Parte Par central
                                    if((i > 0)&&(forest[i-1][j+1] == 1)){forest[i-1][j+1] = 2;  burnedTrees++;} //diagonal superior
                                    if(forest[i+1][j+1] == 1)           {forest[i+1][j+1] = 2;  burnedTrees++;} //diagonal inferio
                                }
                                if((i > dimension - 1) && (i < 2 * dimension) && ((i + 1) % 2 == 0) & extraForm){ //Parte Impar central
                                    if((i > 0)&&(j > 0)&&(forest[i-1][j-1] == 1)){forest[i-1][j-1] = 2;  burnedTrees++;} //diagonal superior
                                    if((j > 0)&&(forest[i+1][j-1] == 1))         {forest[i+1][j-1] = 2;  burnedTrees++;} //diagonal inferio
                                }
                            }
                           
                        }
                    }
                    if((l == 0)&&(generateFile)){ // to check percolation generation better while in an output file
                        for (i = 0; i < size ; i++) {
                            for (j = 0; j < size; j++) {
                                propagatedTrees[i][j] = 0;
                            }
                        }
                    }
                }

                //percolación
                for(i = 0; i < cornerNumber; i++) burnedCorners[i] = false;
                if((!extraForm) && (!triangular)){
                    cornerSize = (size - size % cornerPercentage) / cornerPercentage;
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            
                            if(forest[i][j] == 3) burnedCorners[0] = true;
                            if(forest[i][size - cornerSize + j] == 3) burnedCorners[1] = true;
                            if(forest[size - cornerSize + i][j] == 3) burnedCorners[2] = true;
                            if(forest[size - cornerSize + i][size - cornerSize + j] == 3) burnedCorners[3] = true;
                        }
                    }
                    if((burnedCorners[0] == 1)&&(burnedCorners[3] == 1)) doesItPercolate = true;
                    if((burnedCorners[1] == 1)&&(burnedCorners[2] == 1)) doesItPercolate = true;

                }
                else if(octogonal){
                    cornerSize = (dimension - dimension % cornerPercentage) / cornerPercentage;
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[i][j] == 3) burnedCorners[0] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[i][dimension - cornerSize + j] == 3) burnedCorners[1] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[dimension - cornerSize / 2 + i][2 * dimension - cornerSize + j] == 3) burnedCorners[2] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[2 * dimension - cornerSize / 2 + i][2 * dimension - cornerSize + j] == 3) burnedCorners[3] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[size - cornerSize + i][dimension - cornerSize + j] == 3) burnedCorners[4] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[size - cornerSize + i][j] == 3) burnedCorners[5] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[2 * dimension - cornerSize / 2 + i - 2][j] == 3) burnedCorners[6] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[dimension - cornerSize / 2 + i][j] == 3) burnedCorners[7] = true;
                        }
                    }
                    for(i = 2; i < cornerNumber - 1; i++){
                        if((burnedCorners[0] == 1)&&(burnedCorners[i] == 1)) doesItPercolate = true;
                    }
                    for(i = 3; i < cornerNumber; i++){
                        if((burnedCorners[1] == 1)&&(burnedCorners[i] == 1)) doesItPercolate = true;
                    }
                    for(i = 4; i < cornerNumber; i++){
                        if((burnedCorners[2] == 1)&&(burnedCorners[i] == 1)) doesItPercolate = true;
                    }
                    for(i = 5; i < cornerNumber; i++){
                        if((burnedCorners[3] == 1)&&(burnedCorners[i] == 1)) doesItPercolate = true;
                    }
                    for(i = 6; i < cornerNumber; i++){
                        if((burnedCorners[4] == 1)&&(burnedCorners[i] == 1)) doesItPercolate = true;
                    }
                    if((burnedCorners[5] == 1)&&(burnedCorners[7] == 1)) doesItPercolate = true;
                }
                else if(hexagonal){
                    cornerSize = (dimension - dimension % cornerPercentage) / cornerPercentage;
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[i][j] == 3) burnedCorners[0] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[dimension - cornerSize / 2 + i][dimension - cornerSize + j] == 3) burnedCorners[1] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[2 * dimension - cornerSize / 2 + i][dimension - cornerSize + j] == 3) burnedCorners[2] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[size - cornerSize + i][j] == 3) burnedCorners[3] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[2 * dimension - cornerSize / 2 + i - 2][j] == 3) burnedCorners[4] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[dimension - cornerSize / 2 + i][j] == 3) burnedCorners[5] = true;
                        }
                    }
                    for(i = 2; i < cornerNumber - 1; i++){ //primera esquina
                        if((burnedCorners[0] == 1)&&(burnedCorners[i] == 1)) doesItPercolate = true;
                    }
                    for(i = 3; i < cornerNumber; i++){ //primera esquina
                        if((burnedCorners[1] == 1)&&(burnedCorners[i] == 1)) doesItPercolate = true;
                    }
                    for(i = 4; i < cornerNumber; i++){ //primera esquina
                        if((burnedCorners[2] == 1)&&(burnedCorners[i] == 1)) doesItPercolate = true;
                    }
                    if((burnedCorners[3] == 1)&&(burnedCorners[5] == 1)) doesItPercolate = true;
                }
                else if(triangular){
                    cornerSize = (size - size % cornerPercentage) / cornerPercentage;
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[i][j] == 3) burnedCorners[0] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[size - cornerSize + i][j] == 3)burnedCorners[2] = true;
                        }
                    }
                    for(i = 0; i < cornerSize; i++){
                        for(j = 0; j < cornerSize; j++){
                            if(forest[i][size - cornerSize + j] == 3) burnedCorners[1] = true;
                        }
                    }
                    if((burnedCorners[0] == 1)&&(burnedCorners[1] == 1)) doesItPercolate = true;
                    if((burnedCorners[1] == 1)&&(burnedCorners[2] == 1)) doesItPercolate = true;
                    if((burnedCorners[2] == 1)&&(burnedCorners[0] == 1)) doesItPercolate = true;
                }
                if(doesItPercolate){
                    totalPercolations++;
                    m = clusters;
                }
                else if(m != clusters -1){
                    for (i = 0; i < size ; i++) { //reset del bosque
                        for (j = 0; j < limit; j++) {
                            if(forest[i][j] == 3) forest[i][j] = 0;
                        }
                    }
                }
            }
                
            if(repetitions == 1){
                if((isofena_quemado) && (dimension < Dshow) && (!extraForm)){ //forest per screen
                    for (i = 0; i < dimension + 2 ; i++) {cout << "\033[1;100m  \033[0m";}
                    cout << endl;
                    for (i = 0; i < dimension ; i++) {
                        cout << "\033[1;100m  \033[0m";
                        if(triangular){
                            for (j = 0; j <  i; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                            resto = i;
                        }
                        else resto = 0;
                        for (j = 0; j < dimension - resto; j++) {
                            if((i == r1)&&(j == r2)){ //donde se origina
                                cout << "\033[1;104m  \033[0m";
                            }
                            else if(forest[i][j] == 0){ //donde no hay nada
                                cout << "\033[1;107m  \033[0m";
                            }
                            else if(forest[i][j] == 3){ //quemado
                                cout << "\033[1;101m  \033[0m";
                            }
                            else{ //forest sin quemar
                                cout << "\033[1;102m  \033[0m";
                            }
                        }
                        if(triangular){
                            for (j = 0; j < i ; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                        }
                        cout << "\033[1;100m  \033[0m\n";

                    }
                    for (i = 0; i < dimension + 2 ; i++) {cout << "\033[1;100m  \033[0m";}
                    cout << endl;
                }

                if((isofena_quemado) && (dimension < Dshow) && (extraForm)){ //representación final del forest hexagonal o octogonal
                    cout << endl << "Final forest  \n";
                    if(octogonal) oct = dimension - 1;
                    else oct = 0;

                    for (i = 0; i <= size + 2*oct + 1; i++) {cout << "\033[1;100m \033[0m";}
                    cout << endl;
                    for (i = 1; i < size - 1 ; i++) {
                        cout << "\033[1;100m  \033[0m"; //marron inicial
                        if(i <= dimension){ //primer triangulo
                            for (j = 1; j <= size/2 - i; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                            for (j = 1; j <= i + oct; j++) {
                                if((i == r1)&&(j == r2)){ //donde se origina
                                    cout << "\033[1;104m  \033[0m";
                                }
                                else if(forest[i][j] == 0){ //donde no hay nada
                                    cout << "\033[1;107m  \033[0m";
                                }
                                else if(forest[i][j] == 3){ //quemado
                                    cout << "\033[1;101m  \033[0m";
                                }
                                else{
                                    cout << "\033[1;102m  \033[0m";
                                }
                            }
                            for (j = 1; j <= size/2 - i; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                        }
                        else if(i <= 2 * dimension - 2 ){ //parte central
                            for (j = 0; j <= dimension / 2 - i % 2 ; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                            for (j = 1; j <= dimension - (i + 1) % 2 + oct; j++) {
                                if((i == r1)&&(j == r2)){ //donde se origina
                                    cout << "\033[1;104m  \033[0m";
                                }
                                else if(forest[i][j] == 0){ //donde no hay nada
                                    cout << "\033[1;107m  \033[0m";
                                }
                                else if(forest[i][j] == 3){ //quemado
                                    cout << "\033[1;101m  \033[0m";
                                }
                                else{
                                    cout << "\033[1;102m  \033[0m";
                                }
                            }
                            for (j = 0; j <= dimension / 2 - i % 2 ; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                        }
                        else{//segundo triangulo
                            for (j = 1; j <= i - dimension - (dimension - 1) / 2 ; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                            for (j = 1; j < 3 * dimension - i + oct; j++) {
                                if((i == r1)&&(j == r2)){ //donde se origina
                                    cout << "\033[1;104m  \033[0m";
                                }
                                else if(forest[i][j] == 0){ //donde no hay nada
                                    cout << "\033[1;107m  \033[0m";
                                }
                                else if(forest[i][j] == 3){ //quemado
                                    cout << "\033[1;101m  \033[0m";
                                }
                                else{//arbol vivo
                                    cout << "\033[1;102m  \033[0m";
                                }
                            }
                            for (j = 1; j <= i - dimension - (dimension - 1) / 2 ; j++) {
                                cout << "\033[1;100m \033[0m";
                            }
                        }
                        cout << "\033[1;100m \033[0m\n"; //marron final
                    }

                    for (i = 0; i <= size + 1 + 2*oct; i++) {cout << "\033[1;100m \033[0m";}
                    cout << endl;
                }
            
                for (i = 0; i < 2 * dimension + 3 ; i++) {
                    finalResult << "4";
                    if(i != 2 * dimension + 2){finalResult << ",";}
                }
                    finalResult << endl;
                    for (i = 0; i < dimension ; i++) {
                        if(triangular) resto = i;        
                        else resto = 0;
                        finalResult << "4,4,";
                        if(triangular){
                            for (j = 0; j < i; j++) {
                                finalResult << "4,";
                            }
                        }
                        for (j = 0; j < dimension - resto; j++) {
                            finalResult << forest[i][j]<< ","<< forest[i][j]<< ",";
                        }
                        if(triangular){
                            for (j = 0; j < i; j++) {
                                finalResult << "4,";
                            }
                        }
                        finalResult << "4,4\n";
                    }
                    for (i = 0; i < 2 * dimension + 3 ; i++) {
                        finalResult << "4";
                        if(i != 2 * dimension + 2){finalResult << ",";}
                    }
            }// end of repetitions == 1s
            if(showFinalData && (cycles == 1) && (repetitions <= 10)){
                //cout << "\n\nCiclo Nº: " << l;
                if(triangular) trees = 2*trees;
                cout << "\n   % %Generated trees: " << 100*trees/(dimension * dimension) << " %";
                cout << "       % Burned trees : " << 100 * burnedTrees / trees << " %\n";
                if(doesItPercolate) cout << "\nThere has been percolation!\n";
            }
            //cout << "       % Árboles quemados: " << 100 * burnedTrees / trees << " %\n";
            generatedPercentage += trees;
            arbolesQuemados = burnedTrees / trees;
            burnedPercentage += burnedTrees / trees;
            if(doesItPercolate){
                burnedPercolatedPercentage += burnedTrees/trees;
                posicion = 100*burnedTrees / trees;
                histograma[posicion]++;
            }

            
        }//end of repetitions cycle
        clock_t endloop = clock();
        elapsedTime = double(endloop - startloop) / CLOCKS_PER_SEC;
        percolatedPercentage = 100 * totalPercolations / repetitions;

        res << prob << "   " << burnedPercolatedPercentage/totalPercolations << endl;
        if((cycles > 5 ) && (repetitions > 1000)) cout << "Probability: " << prob << "  done. Timestamp: " << elapsedTime << " Secs\n";

        numero = 0;
        for (int i = 0; i < 100; ++i) {
            numero++;
            outhisto << numero/100 << "   " << prob << "  "  << histograma[i]/totalPercolations << endl;
        }
        for(int i = 1; i < 101; i++){
            histograma[i] = 0;
        }
        if(recorrido) prob = prob + increment;
}
    outhisto.close();

    if((repetitions != 1) && (cycles == 1)){
        cout << "\nCorner size is " << cornerSize << " units  ";
        cout << "Percolation percentage is" << percolatedPercentage << "%\n";
        cout << "\nGeneration probability is " << prob;
        cout << " Forest Dimension: " << dimension << "*" << dimension;
    }

    res.close();
    finalResult.close();
    if(generateFile) cad.close();

    printf("\nTotal time: %.3f seconds.", elapsedTime);
    cout  << "\n-------- End of Program ---------\n";
    return 0;
}