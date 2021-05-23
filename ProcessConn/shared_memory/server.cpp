/**
*   shared memroy demo
*   server read from shm
*/

#include <iostream>
#include <sys/shm.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const unsigned int MAX_SHM_MEM_SIZE = 32;

int main()
{
    // create shared memory
    void* shm = nullptr;
    int shmid = shmget((key_t)1234, MAX_SHM_MEM_SIZE, 0666|IPC_CREAT);
    if (shmid == -1)
    {
        cout << "shmget failed!!!" << endl;
        return -1;
    }
    // the current process connects to this shm
    shm = shmat(shmid, 0, 0);
    if (shm == (void*)-1)
    {
        cout << "connect shm failed!!!" <<endl;
        return -1;
    }
    // read from shm
    char *buff = (char*)shm;
    while(true)
    {
        sleep(1);
        for (size_t i = 0; i < MAX_SHM_MEM_SIZE; i++)
        {
            cout << buff[i];
        }
        cout << endl;
    }
    // divide from shm
    if (shmdt(shm) == -1)
    {
        cout << "shmdt failed!!!" << endl;
        return -1;
    }
    // remove ths shm
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        cout << "shmctl rm failed!!!" << endl;
        return -1;
    }
    return 0;
}