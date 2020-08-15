// Development environment: Lubuntu 18.04.1 LTS
// To compile: g++ -pthread -std=c++11 hw2.cpp -o hw2
// To run: ./hw2 n m 
// Example: ./hw2 2 2
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <semaphore.h>
using namespace std;

int leaders = 0;
int followers = 0;
mutex mutexim;
sem_t leaderQueue;
sem_t followerQueue;
sem_t rendezvous ;
void *follower(void *f);
void *leader(void *l);

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    pthread_t threads[n+m];

    sem_init(&leaderQueue,0,0);
    sem_init(&followerQueue,0,0);
    sem_init(&rendezvous,0,0);
    for(int i=0; i<n;i++){
        int a = i+1;
        pthread_create(&threads[i],NULL,leader,(void *)(intptr_t)(a));
    }
    for(int j=0; j<m;j++){
        int a = j+1;
        pthread_create(&threads[j],NULL,follower,(void *)(intptr_t)(a));
    }
    pthread_exit(NULL);
    sem_destroy(&leaderQueue);
    sem_destroy(&followerQueue);
    sem_destroy(&rendezvous);
    return 0;
}

void *leader(void *l)
{
    int led = (intptr_t) l;
    int rt = rand() % 2000000 + 1;
    usleep(rt);
    mutexim.lock();
    if (followers > 0)
    {
        cout<<"Leader "<<led<<": "<<followers<<" followers are waiting, so I signal the next follower in the queue."<<endl;      
        followers--;
        sem_post(&followerQueue);
    }

    else
    {
      cout<<"Leader "<<led<<": No available follower, so I wait. There are other "<<leaders<<" leaders waiting."<<endl;
        leaders++;
        mutexim.unlock();
        sem_wait(&leaderQueue);
    }
    cout<<"Leader "<<led<<": We are dancing together now."<<endl;
    usleep(500000);
    sem_wait(&rendezvous);
    cout<<"Leader "<<led<<": I leave now."<<endl;
    mutexim.unlock();
}

void *follower(void *f)
{
    int fol = (intptr_t) f;
    int rt = rand() % 2000000 + 1;
    usleep(rt);
    mutexim.lock();
    if (leaders > 0)
    {
        cout<<"Follower "<<fol<<": "<<leaders<<" leaders are waiting, so I signal the next leader in the queue."<<endl;                
        leaders--;
        sem_post(&leaderQueue);
    }
    else
    {
        cout<<"Follower "<<fol<<": No available leader, so I wait. There are other "<<followers<<" followers waiting."<<endl;
        followers++;
        mutexim.unlock();
        sem_wait(&followerQueue);
    }
    cout<<"Follower "<<fol<<": We are dancing together now."<<endl;
    usleep(500000);
    sem_post(&rendezvous);
    cout<<"Follower "<<fol<<": I leave now."<<endl;
}
