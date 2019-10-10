#include <iostream>
#include "Demo.h"

using namespace std;

void xxx()
{
    Demo *pDemo = new Demo();
}

int main(int argc, char *argv[])
{
    xxx();
    cout << "Hello World!" << endl;
    return 0;
}
