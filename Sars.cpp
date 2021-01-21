//
// Created by lior on 03/04/2020.
//

#include "Sars.h"



Sars::Sars(char c, const string& gen, int l) : Virus(c, gen) {
	pM = 0.37;
}

Sars::~Sars() {

}

void Sars::update() {
	int n = this->getGenome().length();
	for (int i = 0; i < n ; ++i) {
		float r = ((float)rand() / RAND_MAX);
		char c = this->getGenome()[i];
		if(c == 'A'){
			if(r < pM) {
				this->setChar(i, 'T');
			}
		}
		if(c == 'T'){
			if(r < pM){
				this->setChar(i,'A');
			}
		}
	}
}

void Sars::print() const {
	cout << this->getKind() << " " << this->getGenome();
}

