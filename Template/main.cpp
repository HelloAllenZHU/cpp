#include <iostream>
#include "TClass.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

    cout << add( 3, 1 ) << endl;
    cout << add( 3.2, 1.1 ) << endl;
    cout << add( '3', '1' ) << endl;

    cout << sub( 3, 1 )  << endl;
    cout << sub( 3.2, 1.1 ) << endl;
    cout << sub( '3', '1' ) << endl;

    TClass<int> it;
    cout << it.add( 1, 2 ) << endl;
    return 0;
}
