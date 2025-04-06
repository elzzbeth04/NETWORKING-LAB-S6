#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#define TIMEOUT 3
#define TOTALPACKETS 5
int simulate_ack()
{
    return rand()%10 <7 ;
}
int main()
{
    srand(time(0));
    int packet=1;
    int ack_recv;
    while(packet<= TOTALPACKETS)
    {
        printf("Sending %d",packet);
        sleep(1);
        ack_recv=simulate_ack();
        if(ack_recv)
        {
            printf("acknowledged %d",packet);
            packet++;
        }
        else
        {
            printf("lost %d retransmitting",packet);
            sleep(TIMEOUT);
        }
    }
    printf("all the packets send");
    return 0;
}