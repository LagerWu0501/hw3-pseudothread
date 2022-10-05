#include "threadutils.h"

void BinarySearch(int thread_id, int init, int maxiter)
{
    ThreadInit(thread_id, init, maxiter);
    Current->y = 0;       
    Current->z = 100;                
    /*
    Some initilization if needed.
    */
    for (Current->i = 0; Current->i < Current->N; ++Current->i)
    {
        if(setjmp(Current->Environment) == 0)
        {
            longjmp(MAIN, 1);
        }
        sleep(1);
        
        printf("BinarySearch: %d\n", (Current->y + Current->z) / 2);
        if ((Current->y + Current->z) / 2 < Current->x)
        {
            Current->y = (Current->y + Current->z) / 2 + 1;
        }
        else if((Current->y + Current->z) / 2 > Current->x)
        {
            Current->z = (Current->y + Current->z) / 2 - 1;
        }
        else
        {
            ThreadExit();
        }
        Current->i++;
        if (Current->i >= Current->N)
        {
            ThreadExit();
        }
        ThreadYield();
    }
    ThreadExit();
}

void BlackholeNumber(int thread_id, int init, int maxiter)
{

    ThreadInit(thread_id, init, maxiter);
    Current->x = init;
    /*
    Some initilization if needed.
    */
    for (Current->i = 0; Current->i < Current->N; ++Current->i)
    {
        if(setjmp(Current->Environment) == 0)
        {
            longjmp(MAIN, 1);
        }
        
        sleep(1);
        int a[3];
        int temp;
        a[0] = (Current->x / 100);
        a[1] = (Current->x % 100) / 10;
        a[2] = (Current->x % 10);
        if (a[0] < a[1])
        {
            temp = a[0];
            a[0] = a[1];
            a[1] = temp;
        } 
        if (a[0] < a[2])
        {
            temp = a[0];
            a[0] = a[2];
            a[2] = temp;
        }
        
        if (a[1] < a[2])
        {
            temp = a[1];
            a[1] = a[2];
            a[2] = temp;
        }
        Current->x = (a[0] * 100 + a[1] * 10 + a[2]) - (a[2] * 100 + a[1] * 10 + a[0]);
        printf("BlackholeNumber: %d\n", Current->x);
        if (Current->x == 495)
        {
            ThreadExit();    
        } 
        Current->i++;
        if (Current->i >= Current->N)
        {
            ThreadExit();
        }
        ThreadYield();
    }
    ThreadExit();
}

void FibonacciSequence(int thread_id, int init, int maxiter)
{
    ThreadInit(thread_id, init, maxiter);
    Current->x = 0;
    Current->y = 1;
    Current->z = 0;
    /*
    Some initilization if needed.
    */
    for (Current->i = 0; Current->i < Current->N; ++Current->i)
    {
        if(setjmp(Current->Environment) == 0)
        {
            longjmp(MAIN, 1);
        }
        sleep(1);
        Current->z = Current->x + Current->y;
        printf("FibonacciSequence: %d\n", Current->z);
        Current->x = Current->y;
        Current->y = Current->z;
        Current->i++;
        if (Current->i >= Current->N)
        {
            ThreadExit();
        }
        ThreadYield();
    }
    ThreadExit();
}
