/**
*   shared memroy demo
*   client write to shm
*/

#include <iostream>
#include <sys/shm.h>
#include <cstring>
#include <string>

using namespace std;

const unsigned int MAX_SHM_MEM_SIZE = 32;

int main(int argc, char** argv)
{
    std::string arg = "abcd";
    if (argc >= 2) arg = argv[1];
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
    memcpy(buff, arg.c_str(), arg.length());
    cout << "written: " << arg << endl;
    // divide from shm
    if (shmdt(shm) == -1)
    {
        cout << "shmdt failed!!!" << endl;
        return -1;
    }
    return 0;
}