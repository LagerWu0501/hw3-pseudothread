#include "threadutils.h"

/*
0. You should state the signal you received by:
   printf('TSTP signal!\n') or printf('ALRM signal!\n')
1. If you receive SIGALRM, you should reset alarm() by timeslice argument passed in ./main
2. You should longjmp(SCHEDULER,1) once you're done
*/
void sighandler(int signo)
{
   if (signo == SIGALRM)
   {
      printf("ALRM signal!\n");
      sigaddset(&base_mask, SIGALRM);
      alarm(timeslice);
   }
   else
   {
      printf("TSTP signal!\n");
      sigaddset(&base_mask, SIGTSTP);
   }
   Current = Current->Next;
      sigaddset(&base_mask, SIGALRM);
      sigaddset(&base_mask, SIGTSTP);
   sigprocmask(SIG_SETMASK, &base_mask, NULL);
   longjmp(Current->Environment, 1);
}

/*
0. You are stronly adviced to make setjmp(SCHEDULER) = 1 for ThreadYield() case
                                   setjmp(SCHEDULER) = 2 for ThreadExit() case
1. Please point the Current TCB_ptr to correct TCB_NODE
2. Please maintain the circular linked-list here
*/
void scheduler()
{
   int E_Y = setjmp(SCHEDULER);
   if (E_Y == 0)
   {
      Current = Head;
      longjmp(Head->Environment, 1);
   }
   else if (E_Y == 1) // Yield
   {
      if (switchmode == 0)
      {
         Current = Current->Next;
      }
      else if(switchmode == 1)
      {
         sigpending(&base_mask);
         if (sigismember(&base_mask, SIGTSTP))
         {
            sigprocmask(SIG_SETMASK, &alrm_mask, NULL);
         }
         else if (sigismember(&base_mask, SIGALRM))
         {
            sigprocmask(SIG_SETMASK, &tstp_mask, NULL);
         } 
      }
      longjmp(Current->Environment, 1);
   }
   else if (E_Y == 2) // Exit
   {
      if (Current != Current->Next)
      {
         Work = Current->Next;
         Work->Prev = Current->Prev;
         Current->Prev->Next = Work;
         Current = Work;
      }
      else
      {
         Current = NULL;
      }
      if (Current != NULL)
      {
         longjmp(Current->Environment, 1);
      }
   }
}