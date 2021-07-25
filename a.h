

// DATA STRUCTURES NEEDED FOR BANKERS ALGO
// *** All data structures currently hard-coded size to match input file for testing ***

int *available[4];     // represents the number of available resources of each type
int *max[5][4];        // m x n matrix representing max number of instances of each resource that a process can request
int *allocation[5][4]; // m x n matrix representing the num of resources of each type currently allocated to each process
int *need[5][4];       // m x n matrix representing the remaining resource needs of each process. Need[i][j] = max[i][j] - allocation[i][j]

int readFileCustomers(char *fileName);
void *readFileSequences(char *fileName);
int safety();
int sum_arr(int arr[], int n);
// testing functions
