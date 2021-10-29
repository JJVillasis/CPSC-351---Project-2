#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void* alpha(void*);
void* numeric(void*);

string phrase;

int main(int argc, char *argv[])
{
  phrase = argv[1];

  pthread_t threadA, threadN;
  pthread_create(&threadA, NULL, alpha, NULL);
  pthread_create(&threadN, NULL, numeric, NULL);

  pthread_join(threadA, NULL);
  pthread_join(threadN, NULL);

  return 0;
}

void* alpha(void* arg)
{
  int space = 0;

  while(phrase.size() != 0)
  {
    if(isalpha(phrase[0]))
    {
      if(phrase.find(" ") == string::npos)
      {
        cout << "Alpha: " << phrase << endl;
        phrase = "";
      }
      else
      {
        space = phrase.find(" ");
        cout << "Alpha: " << phrase.substr(0, space) << endl;
        phrase = phrase.substr(phrase.find(" ")+1);
      }
    }
  }

  pthread_exit(0);
}

void* numeric(void* arg)
{
  int space = 0;

  while(phrase.size() != 0)
  {
    if(isdigit(phrase[0]))
    {
      if(phrase.find(" ") == string::npos)
      {
        cout << "Numeric: " << phrase << endl;
        phrase = "";
      }
      else
      {
        space = phrase.find(" ");
        cout << "Numeric: " << phrase.substr(0, space) << endl;
        phrase = phrase.substr(phrase.find(" ")+1);
      }
    }
  }

  pthread_exit(0);
}
