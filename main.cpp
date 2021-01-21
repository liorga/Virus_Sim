#include <iostream>
#include "SimVirus.h"

int main(int argc, char* argv[]) {
	if(argc < 3){
		cerr << "not enough arguments" << endl;
		exit(1);
	}
    srand(time(NULL));
    SimVirus a(argv[1],argv[2]);
    a.start();
    a.clear();
    return 0;
}
