#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

const int forestDimension = 64;                             //Dimension of forest
const int repetitions = 100;                                //repetitions of each size
const int precision = 10000;                                //of the RNG
const int cornerSize = 51;                                  //corner in which it checks if there is percolation
const int clusters = 5;                                     //times it tries to percolate in different clusters
const int threadsPerProbability = 1;                         //times it splits the repetitions for each probability

const double initialProbability = 0.6;                      //the probability it starts from
const double finalProbability = 0.605;                      //the probability it ends in
const double increment = 0.001;                             //the increment between probabilities
mt19937 mt{};

int fillForest(double probability) {                       //unused function to fill the forest with other RNG generation, increasing but better RNG generation
    double random;
    random = mt()%precision;
    if (random < precision * probability) {
        return 1;
    } else {
        return 0;
    }
}

void singlePercolation(double prob, double *result) {       //percolation function that each thread calls
    int r1;                                                 //coordinates on the forest
    int r2;
    int cornersNumber = 4;                                  //number of corners it tries to percolate in
    double generatedTrees;
    double burnedTrees;
    bool burnedCorners[cornersNumber];
    bool doesItPercolate;                                   //bool to check for percolation
    bool doesItPropagate;                                   //bool to check for propagation
    double totalPercolations;
    double burnedPercentage;
    double randomNumber;                                    //random number used to create the forest

    int forest[forestDimension][forestDimension];           //matrix

    totalPercolations = 0;
    for (int l = 0; l < repetitions; l++) {
        generatedTrees = 0;
        doesItPercolate = false;
        for (int i = 0; i < forestDimension; i++) {
            for (int j = 0; j < forestDimension; j++) {
                randomNumber = (rand() % precision);
                if (randomNumber <= precision * prob) {
                    forest[i][j] = 1;
                    generatedTrees++;
                } else {
                    forest[i][j] = 0;
                }
            }
        }
        //randomised burning
        burnedTrees = 0;
        for (int m = 0; m < clusters; m++) {
            r1 = (rand() % forestDimension);              //election of first burned tree
            r2 = (rand() % forestDimension);
            while ((forest[r1][r2] == 0) && (prob != 0)) {//check is there is a tree on that location
                r1 = (rand() % forestDimension);
                r2 = (rand() % forestDimension);
            }
            burnedTrees++;
            forest[r1][r2] = 2;                           //setting the initial tree on fire
            doesItPropagate = true;
            while (doesItPropagate) {
                doesItPropagate = false;
                for (int i = 0; i < forestDimension; i++) { //fire propagation
                    for (int j = 0; j < forestDimension; j++) {
                        if (forest[i][j] == 2) {
                            doesItPropagate = true;
                            forest[i][j]++;
                            if ((i > 0)&&(forest[i - 1][j] == 1)) {
                                forest[i - 1][j] = 2;
                                burnedTrees++;
                            } //vertical down propagation
                            if ((i < forestDimension - 1)&&(forest[i + 1][j] == 1)) {
                                forest[i + 1][j] = 2;
                                burnedTrees++;
                            } //vertical up propagation
                            if ((j > 0)&&(forest[i][j - 1] == 1)) {
                                forest[i][j - 1] = 2;
                                burnedTrees++;
                            } //horizontal left propagation
                            if ((j < forestDimension - 1)&&(forest[i][j + 1] == 1)) {
                                forest[i][j + 1] = 2;
                                burnedTrees++;
                            } //horizontal right propagation
                        }
                    }
                }
            }

            //percolation checking
            for (int i = 0; i < cornersNumber; i++) burnedCorners[i] = false;
            for (int i = 0; i < cornerSize; i++) {
                for (int j = 0; j < cornerSize; j++) {
                    if (forest[i][j] == 3) burnedCorners[0] = true;
                    if (forest[i][forestDimension - cornerSize + j] == 3) burnedCorners[1] = true;
                    if (forest[forestDimension - cornerSize + i][j] == 3) burnedCorners[2] = true;
                    if (forest[forestDimension - cornerSize + i][forestDimension - cornerSize + j] == 3) burnedCorners[3] = true;
                }
            }
            if (((burnedCorners[0] == 1) && (burnedCorners[3] == 1)) ||
                ((burnedCorners[1] == 1) && (burnedCorners[2] == 1))) {
                doesItPercolate = true;
                totalPercolations++;
            }

            if(doesItPercolate) break ;
            else if(burnedTrees / generatedTrees >= 0.75)  break;
            else if(m != clusters - 1){ //if it hasnt reached the cluster limit, try again
                for (auto & i : forest) {
                    for (int & j : i) {
                        if(j == 3) j = 0;
                    }
                }
            }
        }
    }

    burnedPercentage = 100 * totalPercolations / repetitions;
    *result = burnedPercentage;
}

int percolate() {
    ofstream outputResults;
    cout.flush();
    cout << "\n\n--------- Start of Program ---------\n\n";
    int cycles;
    double finalResult;
    double prob;

    cycles = static_cast<int>((finalProbability - initialProbability) / increment + 1);
    cout << "times: " << cycles << endl;
    cout << "repetitions per probability " << repetitions << endl;
    prob = initialProbability - increment;

    double results[cycles * threadsPerProbability + 1];
    std::vector<thread> threads;
    for (int p = 0; p < cycles; p++) {
        prob = prob + increment;
        for(int m = 0; m < threadsPerProbability; m++) {
            threads.emplace_back(singlePercolation, prob, &results[threadsPerProbability * p + m]);  //multi-thread
            //singlePercolation(prob, &results[p]); // sequential thread, disabled
        }
    }

    for (auto &thread: threads) {
        thread.join();
    }

    // Write out results
    prob = initialProbability - increment;
    outputResults.open("Data.txt");
    outputResults << "# Tree Probability vs percolation percentage. Dimension: " << forestDimension << ". Cycles: " << repetitions * threadsPerProbability << endl;
    outputResults << "# Corner Size: " << cornerSize << ". Number of clusters " << clusters << ". Iteration from " << initialProbability << " to " << finalProbability << endl;

    for (int p = 0;
         p < cycles; p++) {
        finalResult = 0;
        prob = prob + increment;
        for (int m = 0; m < threadsPerProbability; m++)
            finalResult += results[threadsPerProbability * p + m];

        outputResults << prob << "   " << finalResult / threadsPerProbability << endl;
    }
    outputResults.close();

    cout << "\n\n-------- End of Program ---------\n\n";
    return 0;
}

int main() {
    srand((unsigned) time(nullptr));
    // Get the start time
    auto start = std::chrono::high_resolution_clock::now();
    percolate();

    // Get the end time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Elapsed time: " << elapsed.count() << " milliseconds" << std::endl;
    return 0;
}