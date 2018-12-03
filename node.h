//
// Created by Hus on 11/26/2018.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

typedef int bool;
#define true 1
#define false 0

struct Node{
    int id;
    int T;
    int last_send;
    int PICS[5][21];    //Where 0 is the Avg T, 1-21 Are the last 20 normal recordings
    char state;
};

//int generate_message(struct Node node);
void send_message(struct Node sendingNode, int now){
    sendingNode.last_send = now;
};

bool evaluateReading(int newPeriod, int currentPeriod){

    if( newPeriod <= currentPeriod/2){
        return true;
    }else{
        return false;
    }

};

struct Node receive_message(struct Node sendingNode, struct Node receivingNode, int now){

    int newT     = (now - sendingNode.last_send)/1000; //Newest T for the sending node
    int currentT = receivingNode.PICS[sendingNode.id][0];

    bool DOS = 0;

    if(currentT != 0){
        DOS = evaluateReading(newT, currentT);

        if(DOS == true){
            receivingNode.state = 'B';
            return receivingNode;
        }
    }

    int i;

    for (i = 1; i < 21; ++i) {
        if(receivingNode.PICS[sendingNode.id][i] == 0){
            receivingNode.PICS[sendingNode.id][i] = newT;
            break;
        }
    }

    if(i == 21){

        int sum = 0;
        for (int j = 1; j <= 21 ; ++j) {
            sum += receivingNode.PICS[sendingNode.id][j];
        }

        int new_avg  = sum /20;
        receivingNode.PICS[sendingNode.id][0] = new_avg;

//      Empty the array
        for (int j = 1; j < 21 ; ++j) {
            receivingNode.PICS[sendingNode.id][j] = 0;
        }
    }

    return receivingNode;

};





#endif //UNTITLED_NODE_H
