#include<iostream>
#include<string>
#include<cmath>
#include <fstream>
using namespace std;
int dices = 3; //number of dices up to 24
int minResult = 1; //min result the dice can get
int maxResult = 6;  //max result the dice can get
int range = 3;      //range of values that will be showed around the middle value
bool skip = false; // to skip certain values after obtaining the middle value entropy, improves efficiency
int main(void)
{
    int i;
    int  sum, sump; //sum and partial sum
    double macro;
    cout << "Number of dices is " << dices << endl;
    macro = ((maxResult + minResult)*dices + dices%2)/2;
    double counter[dices*maxResult+2];

    //Inicialize
    int* in = new int[25];

    for (i = 0; i < dices*maxResult + 1; i++) {
        counter[i] = 0;
    }

    if(dices == 2){
    for (in[1] = minResult; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            counter[in[1] + in[2]] +=1;
        }
    }
    }

    if(dices == 3){
    for (in[1] = minResult; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                counter[in[1] + in[2] + in[3]] += 1;    
            }
        }
    }
    }
    
    if(dices == 4){
    for (in[1] = minResult; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                 counter[in[1] + in[2] + in[3] + in[4] ] += 1;    
                }
            }
        }
    }
    }
    
    if(dices == 5){
    for (in[1] = minResult; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                        for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                            counter[in[1] + in[2] + in[3] + in[4] + in[5] ] += 1;
                    }
                }
            }
        }
    }
    }

    if(dices == 6){
    for (in[1] = minResult; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                        for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                            for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                                counter[in[1] + in[2] + in[3] + in[4] + in[5] + in[6]] += 1;
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 7){
    for (in[1] = minResult; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        sump = in[1] + in[2] + in[3] + in[4] + in[5];
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                
                                        sum = sump;
                                        for(i = 6; i <= dices; i++){
                                            sum += in[i];
                                        }
                                        counter[sum] += 1;
                                        if ((sum >= macro)&&(skip)){
                                            in[dices] = maxResult;
                                        } 
                                
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 8){
    for (in[1] = minResult; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        sump = in[1] + in[2] + in[3] + in[4] + in[5];
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                        sum = sump;
                                        for(i = 6; i <= dices; i++){
                                            sum += in[i];
                                        }
                                        counter[sum] += 1;
                                        if ((sum >= macro)&&(skip)){
                                            in[dices] = maxResult;
                                        } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 9){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        sump = in[1] + in[2] + in[3] + in[4] + in[5];
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        sum = sump;
                                        for(i = 6; i <= dices; i++){
                                            sum += in[i];
                                        }
                                        counter[sum] += 1;
                                        if ((sum >= macro)&&(skip)){
                                            in[dices] = maxResult;
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 10){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        sump = in[1] + in[2] + in[3] + in[4] + in[5];
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                                sum = sump;
                                                for(i = 6; i <= dices; i++){
                                                    sum += in[i];
                                                }
                                                counter[sum] += 1;
                                                if ((sum >= macro)&&(skip)){
                                                    in[dices] = maxResult;
                                                
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 11){
    for (in[1] = minResult; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                sum = sump;
                                                for(i = 7; i <= dices; i++){
                                                    sum += in[i];
                                                }
                                                counter[sum] += 1;
                                                if ((sum >= macro)&&(skip)){
                                                    in[dices] = maxResult;
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 12){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    sum = sump;
                                                    for(i = 7; i <= dices; i++){
                                                        sum += in[i];
                                                    }
                                                    counter[sum] += 1;
                                                    if ((sum >= macro)&&(skip)){
                                                        in[dices] = maxResult;
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 13){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        sum = sump;
                                                        for(i = 7; i <= dices; i++){
                                                            sum += in[i];
                                                        }
                                                        counter[sum] += 1;
                                                        if ((sum >= macro)&&(skip)){
                                                            in[dices] = maxResult;
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 14){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                            sum = sump;
                                                            for(i = 7; i <= dices; i++){
                                                                sum += in[i];
                                                            }
                                                            counter[sum] += 1;
                                                            if ((sum >= macro)&&(skip)){
                                                                in[dices] = maxResult;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 15){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                            for (in[15] = in[14]; in[15] <= maxResult; in[15]++) {
                                                                sum = sump;
                                                                for(i = 7; i <= dices; i++){
                                                                    sum += in[i];
                                                                }
                                                                counter[sum] += 1;
                                                                if ((sum >= macro)&&(skip)){
                                                                    in[dices] = maxResult;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 16){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                            for (in[15] = in[14]; in[15] <= maxResult; in[15]++) {
                                                                for (in[16] = in[15]; in[16] <= maxResult; in[16]++) {
                                                                        sum = sump;
                                                                        for(i = 7; i <= dices; i++){
                                                                            sum += in[i];
                                                                        }
                                                                        counter[sum] += 1;
                                                                        if ((sum >= macro)&&(skip)){
                                                                            in[dices] = maxResult;
                                                                        }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 17){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                            for (in[15] = in[14]; in[15] <= maxResult; in[15]++) {
                                                                for (in[16] = in[15]; in[16] <= maxResult; in[16]++) {
                                                                    for (in[17] = in[16]; in[17] <= maxResult; in[17]++) {
                                                                            sum = sump;
                                                                            for(i = 7; i <= dices; i++){
                                                                                sum += in[i];
                                                                            }
                                                                            counter[sum] += 1;
                                                                            if ((sum >= macro)&&(skip)){
                                                                                in[dices] = maxResult;
                                                                            }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 18){
        for (in[1] = 1; in[1] <= maxResult; in[1]++) {
            for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
                for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                    for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                        for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                            for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                                sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                                for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                    for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                        for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                            for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                                for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                    for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                        for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                            for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                                for (in[15] = in[14]; in[15] <= maxResult; in[15]++) {
                                                                    for (in[16] = in[15]; in[16] <= maxResult; in[16]++) {
                                                                        for (in[17] = in[16]; in[17] <= maxResult; in[17]++) {
                                                                            for (in[18] = in[17]; in[18] <= maxResult; in[18]++) {
                                                                                sum = sump;
                                                                                for(i = 7; i <= dices; i++){
                                                                                    sum += in[i];
                                                                                }                                                                    
                                                                                counter[sum] += 1;
                                                                                if ((sum >= macro)&&(skip)){
                                                                                    in[dices] = maxResult;
                                                                                }   
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }                                
                                        } 
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        }
    }

    if(dices == 19){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                            for (in[15] = in[14]; in[15] <= maxResult; in[15]++) {
                                                                for (in[16] = in[15]; in[16] <= maxResult; in[16]++) {
                                                                    for (in[17] = in[16]; in[17] <= maxResult; in[17]++) {
                                                                        for (in[18] = in[17]; in[18] <= maxResult; in[18]++) {
                                                                            for (in[19] = in[18]; in[19] <= maxResult; in[19]++) {                                                       
                                                                                sum = sump;
                                                                                for(i = 7; i <= dices; i++){
                                                                                    sum += in[i];
                                                                                }
                                                                                counter[sum] += 1;
                                                                                if ((sum >= macro)&&(skip)){
                                                                                    in[dices] = maxResult;
                                                                                }    
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }
    
    if(dices == 20){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                            for (in[15] = in[14]; in[15] <= maxResult; in[15]++) {
                                                                for (in[16] = in[15]; in[16] <= maxResult; in[16]++) {
                                                                    for (in[17] = in[16]; in[17] <= maxResult; in[17]++) {
                                                                        for (in[18] = in[17]; in[18] <= maxResult; in[18]++) {
                                                                            for (in[19] = in[18]; in[19] <= maxResult; in[19]++) {
                                                                                for (in[20] = in[19]; in[20] <= maxResult; in[20]++) {                                
                                                                                    sum = sump;
                                                                                    for(i = 7; i <= dices; i++){
                                                                                        sum += in[i];
                                                                                    }
                                                                                    counter[sum] += 1;
                                                                                    if ((sum >= macro)&&(skip)){
                                                                                        in[dices] = maxResult;
                                                                                    }
                                                                                    
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }
    
    if(dices == 21){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                            for (in[15] = in[14]; in[15] <= maxResult; in[15]++) {
                                                                for (in[16] = in[15]; in[16] <= maxResult; in[16]++) {
                                                                    for (in[17] = in[16]; in[17] <= maxResult; in[17]++) {
                                                                        for (in[18] = in[17]; in[18] <= maxResult; in[18]++) {
                                                                            for (in[19] = in[18]; in[19] <= maxResult; in[19]++) {
                                                                                for (in[20] = in[19]; in[20] <= maxResult; in[20]++) {
                                                                                    for (in[21] = in[20]; in[21] <= maxResult; in[21]++) {
                                                                                        sum = sump;
                                                                                        for(i = 7; i <= dices; i++){
                                                                                            sum += in[i];
                                                                                        }
                                                                                        counter[sum] += 1;
                                                                                        if ((sum >= macro)&&(skip)){
                                                                                            in[dices] = maxResult;
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }
    
    if(dices == 22){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                            for (in[15] = in[14]; in[15] <= maxResult; in[15]++) {
                                                                for (in[16] = in[15]; in[16] <= maxResult; in[16]++) {
                                                                    for (in[17] = in[16]; in[17] <= maxResult; in[17]++) {
                                                                        for (in[18] = in[17]; in[18] <= maxResult; in[18]++) {
                                                                            for (in[19] = in[18]; in[19] <= maxResult; in[19]++) {
                                                                                for (in[20] = in[19]; in[20] <= maxResult; in[20]++) {
                                                                                    for (in[21] = in[20]; in[21] <= maxResult; in[21]++) {
                                                                                        for (in[22] = in[21]; in[22] <= maxResult; in[22]++) {
                                                                                            sum = sump;
                                                                                            for(i = 7; i <= dices; i++){
                                                                                                sum += in[i];
                                                                                            }
                                                                                            counter[sum] += 1;
                                                                                            if ((sum >= macro)&&(skip)){
                                                                                                in[dices] = maxResult;
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 23){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                            for (in[15] = in[14]; in[15] <= maxResult; in[15]++) {
                                                                for (in[16] = in[15]; in[16] <= maxResult; in[16]++) {
                                                                    for (in[17] = in[16]; in[17] <= maxResult; in[17]++) {
                                                                        for (in[18] = in[17]; in[18] <= maxResult; in[18]++) {
                                                                            for (in[19] = in[18]; in[19] <= maxResult; in[19]++) {
                                                                                for (in[20] = in[19]; in[20] <= maxResult; in[20]++) {
                                                                                    for (in[21] = in[20]; in[21] <= maxResult; in[21]++) {
                                                                                        for (in[22] = in[21]; in[22] <= maxResult; in[22]++) {
                                                                                            for (in[23] = in[22]; in[23] <= maxResult; in[23]++) {
                                                                                                sum = sump;
                                                                                                for(i = 7; i <= dices; i++){
                                                                                                    sum += in[i];
                                                                                                }
                                                                                                counter[sum] += 1;
                                                                                                if ((sum >= macro)&&(skip)){
                                                                                                    in[dices] = maxResult;
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    if(dices == 24){
    for (in[1] = 1; in[1] <= maxResult; in[1]++) {
        for (in[2] = in[1]; in[2] <= maxResult; in[2]++) {
            for (in[3] = in[2]; in[3] <= maxResult; in[3]++) {
                for (in[4] = in[3]; in[4] <= maxResult; in[4]++) {
                    for (in[5] = in[4]; in[5] <= maxResult; in[5]++) {
                        for (in[6] = in[5]; in[6] <= maxResult; in[6]++) {
                            sump = in[1] + in[2] + in[3] + in[4] + in[5] + in[6];
                            for (in[7] = in[6]; in[7] <= maxResult; in[7]++) {
                                for (in[8] = in[7]; in[8] <= maxResult; in[8]++) {
                                    for (in[9] = in[8]; in[9] <= maxResult; in[9]++) {
                                        for (in[10] = in[9]; in[10] <= maxResult; in[10]++) {
                                            for (in[11] = in[10]; in[11] <= maxResult; in[11]++) {
                                                for (in[12] = in[11]; in[12] <= maxResult; in[12]++) {
                                                    for (in[13] = in[12]; in[13] <= maxResult; in[13]++) {
                                                        for (in[14] = in[13]; in[14] <= maxResult; in[14]++) {
                                                            for (in[15] = in[14]; in[15] <= maxResult; in[15]++) {
                                                                for (in[16] = in[15]; in[16] <= maxResult; in[16]++) {
                                                                    for (in[17] = in[16]; in[17] <= maxResult; in[17]++) {
                                                                        for (in[18] = in[17]; in[18] <= maxResult; in[18]++) {
                                                                            for (in[19] = in[18]; in[19] <= maxResult; in[19]++) {
                                                                                for (in[20] = in[19]; in[20] <= maxResult; in[20]++) {
                                                                                    for (in[21] = in[20]; in[21] <= maxResult; in[21]++) {
                                                                                        for (in[22] = in[21]; in[22] <= maxResult; in[22]++) {
                                                                                            for (in[23] = in[22]; in[23] <= maxResult; in[23]++) {
                                                                                                for (in[24] = in[23]; in[24] <= maxResult; in[24]++) {
                                                                                                    sum = sump;
                                                                                                    for(i = 7; i <= dices; i++){
                                                                                                        sum += in[i];
                                                                                                    }
                                                                                                    counter[sum] += 1;
                                                                                                    if ((sum >= macro)&&(skip)){
                                                                                                        in[dices] = maxResult;
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }                                
                                    } 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }
    
    for(i = macro - range; i < macro + range; i++){
        cout << "Number of Microstates for the Macrostate" << i << " es " << counter[(i)] << endl;
    }

    cout << endl << "---------End of program---------" << endl;

    return 0;
}
