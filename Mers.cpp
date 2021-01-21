//
// Created by lior on 03/04/2020.
//

#include "Mers.h"



Mers::Mers(char c, const string& gen, int l) : Virus(c, gen) {
	pM = 1/(float)l;
}

Mers::~Mers() {

}

void Mers::update() {
	int n = this->getGenome().length();
	for (int i = 0; i < n ; ++i) {
		float r = ((float)rand() / RAND_MAX);
		char c = this->getGenome()[i];
		if(c == 'A'){
			if(r < pM){
				this->setChar(i,'T');
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

void Mers::print() const {
	cout << this->getKind() << " " << this->getGenome();
}
