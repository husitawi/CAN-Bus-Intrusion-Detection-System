#include <stdio.h>
#include "node.h"
#include <windows.h>

struct Node nodes[5];

void broadcast(struct Node sendingNode, int now){
    struct Node modifiedNode;

    for (int j = 0; j < 5; ++j) {
        if(nodes[j].id == sendingNode.id){
            continue;
        }

        modifiedNode = receive_message(sendingNode, nodes[j], now);
        nodes[j] = modifiedNode;

    }

}


void outputNodeZero(){
    printf("%s\n","Node 0 data:");
    printf("%s%i\n","1 has T = ",nodes[0].PICS[1][0]);
    printf("%s%i\n","2 has T = ",nodes[0].PICS[2][0]);
    printf("%s%i\n","3 has T = ",nodes[0].PICS[3][0]);
    printf("%s%i\n","4 has T = ",nodes[0].PICS[4][0]);

}


void ruinNode(){
    nodes[1].T = 2000;
}


int main( )
{

//  Init the nodes
    nodes[0].T  = 3000;
    nodes[0].id = 0;
    nodes[0].last_send = 0;
    nodes[0].state = 'A';

    nodes[1].T  = 5000;
    nodes[1].id = 1;
    nodes[1].last_send = 0;
    nodes[1].state = 'A';

    nodes[2].T  = 7000;
    nodes[2].id = 2;
    nodes[2].last_send = 0;
    nodes[2].state = 'A';

    nodes[3].T  = 9000;
    nodes[3].id = 3;
    nodes[3].last_send = 0;
    nodes[3].state = 'A';

    nodes[4].T  = 10000;
    nodes[4].id = 4;
    nodes[4].last_send = 0;
    nodes[4].state = 'A';

    int time = 0;
    int readingNumber = 0;

    while(1){
//        Sleep(1000);
        time += 1000;

        for (int i = 0; i < 5; ++i) {
            if( time % nodes[i].T  == 0 ){
                ++readingNumber;



                printf("%s %i\n","The sending node is",i);
                printf("%s %i%s\n", "Time passed:", time/1000,"s");
                printf("%s %i\n", "Reading Number:", readingNumber);
                printf("%s %c\n", "State of Node0:", nodes[0].state);
                printf("%s\n","--------------");

                broadcast(nodes[i],time);
                nodes[i].last_send = time;
                outputNodeZero();

                if(nodes[0].state == 'B'){

                    printf("\n%s\n","--------------");
                    printf("%s\n","--------------");
                    printf("%s\n\n","--------------");
                    printf("%s %i %s %i %s %i000, %s\n","Detected DOS from Node", nodes[i].id, "after sending at rate", nodes[i].T, "which is lower than", nodes[0].PICS[nodes[i].id][0], "the current average");
                    return 0;

                }

                printf("%s\n\n","");


            }
        }

        if( time % 550000  == 0 ) {
            ruinNode();
        }
    }


}
