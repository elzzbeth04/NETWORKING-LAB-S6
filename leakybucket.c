#include<stdio.h>
void main()
{
    int n,in,out,bsize,bucket=0,possible;
    printf("enter no of inputs; ");
    scanf("%d",&n);
    printf("enter bucket size: ");
    scanf("%d",&bsize);
    printf("enter outgoing rate: ");
    scanf("%d",&out);
    while(n!=0)
    {
        printf("enter no of incomming packets: ");
        scanf("%d",&in);
        if(in<=(bsize-bucket))
        {
            bucket+=in;
            printf("bucket status: %d out of %d\n",bucket,bsize);
        }
        else
        {
            printf("dropped: %d\n",in-(bsize-bucket));
            printf("bucket status: %d out of %d\n",bucket,bsize);
            bucket=bsize;
        }
        bucket=bucket-out;
        printf("bucket status: %d out of %d\n",bucket,bsize);
        n--;
    }
}