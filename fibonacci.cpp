#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

void* generateFibonacci(void*);
void* displayFibonacci(void*);

vector<int> fibonacciSequence;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "usage: a.out <integer value>\n");
    return -1;
  }

  if (atoi(argv[1] ) <= 0)
  {
    fprintf(stderr, "%d must be > 0\n", atoi(argv[1]));
    return -1;
  }

  string num(argv[1]);

  pthread_t parent;
  pthread_create(&parent, NULL, displayFibonacci, argv[1]);

  pthread_join(parent, NULL);

  return 0;
}

void* generateFibonacci(void* arg)
{
  int number = stoi((char*) arg);

  for(int x = 2; x < number; ++x)
  {
    int num = fibonacciSequence[fibonacciSequence.size()-2] + fibonacciSequence[fibonacciSequence.size()-1];
    fibonacciSequence.push_back(num);
  }
  pthread_exit(0);
}

void* displayFibonacci(void* param)
{
  pthread_t child;

  fibonacciSequence.push_back(0);
  fibonacciSequence.push_back(1);

  pthread_create(&child, NULL, generateFibonacci, param);
  pthread_join(child, NULL);

  for(int x = 0; x < fibonacciSequence.size()-1; ++x)
  {
    cout << fibonacciSequence[x] << ", ";
  }
  cout << fibonacciSequence.back() << endl;

  pthread_exit(0);
}
