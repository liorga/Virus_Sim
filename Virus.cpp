//
// Created by lior on 03/04/2020.
//

#include "Virus.h"
#include "SimVirus.h"



Virus::Virus(char c, const string& gen) : kind(c), genome(gen),power(0) {
	refCount = 0;
	anccestor = nullptr;
}


Virus::~Virus() {

}

Virus::Virus(const Virus &rhs) {
	this->kind = rhs.kind;
	this->genome = rhs.genome;
	this->power = rhs.power;
	this->l = rhs.l;
}

char Virus::getKind() const {
    return kind;
}

const string& Virus::getGenome() const {
    return genome;
}

void Virus::setGenome(const string &genome) {
    Virus::genome = genome;
}

float Virus::getPower() const {
	return power;
}

void Virus::setPower(float power) {
	Virus::power = power;
}

void Virus::setChar(int i, char c) {
	this->genome[i] = c;
}

Virus *Virus::getAnccestor() const {
	return anccestor;
}

void Virus::setAnccestor(Virus *anccestor) {
	Virus::anccestor = anccestor;
}

void Virus::addCount() {
	refCount++;
}

void Virus::removeCount() {
	refCount--;
}

int Virus::getRefCount() const {
	return refCount;
}





