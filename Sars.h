//
// Created by lior on 03/04/2020.
//

#ifndef EX1_SIMVIRUS_SARS_H
#define EX1_SIMVIRUS_SARS_H
#include "Virus.h"

class Sars : public Virus{
public:
	Sars(char c, const string& gen, int l);
	virtual ~Sars();
    void update() ;
    void print() const;
	

private:
	float pM;
};


#endif //EX1_SIMVIRUS_SARS_H
