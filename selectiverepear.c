#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int ack(){
    return rand() % 2;  // Random 0 or 1
}

int main(){
    int n, ws, wt, i, flag;

    srand(time(0));

    printf("Packets to send: ");
    scanf("%d", &n);
    printf("Window size: ");
    scanf("%d", &ws);
    printf("Wait time: ");
    scanf("%d", &wt);

    i = 1;

    while(i <= n) {
        flag = 0;
        // Send window of ws packets
        for(int j=0; j<ws && i+j<=n; j++) {
            printf("Sending packet %d...\n", i+j);
            sleep(1);
        }

        // Check ACK for each packet
        for(int j=0; j<ws && i+j<=n; j++) {
            if(ack()) {
                printf("ACK received for packet %d\n", i+j);
            }
            else {
                printf("ACK lost for packet %d! Resending after %d sec...\n", i+j, wt);
                sleep(wt);
                flag = 1;
                break; // Resend this frame only
            }
        }

        if(flag == 0)
            i += ws; // Slide window if all ACK received
    }

    printf("All packets sent!\n");
    return 0;
}

