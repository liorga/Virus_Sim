//
// Created by lior on 03/04/2020.
//

#include "Covid.h"



Covid::Covid(char c, const string& gen, int l) : Virus(c, gen) {
	pM = 2/(float)l;
}

Covid::~Covid() {

}

void Covid::update() {
	int n = this->getGenome().length();
	for (int i = 0; i < n ; ++i) {
		float r = ((float)rand() / RAND_MAX);
		char c = this->getGenome()[i];
		if(c == 'T'){
			if(r < pM){
				this->setChar(i,'A');
			}
		}
		if(c == 'C'){
			if(r < pM){
				this->setChar(i,'G');
			}
		}
		if(c == 'G'){
			if(r < pM){
				this->setChar(i,'C');
			}
		}
	}
}

void Covid::print() const {
	cout << this->getKind() << " " << this->getGenome();
}
