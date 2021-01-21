//
// Created by lior on 03/04/2020.
//

#ifndef EX1_SIMVIRUS_MERS_H
#define EX1_SIMVIRUS_MERS_H
#include "Virus.h"

class Mers : public Virus{
public:
	Mers(char c, const string& gen, int l);
	virtual ~Mers();
    void update() ;
    void print() const;
    
private:
	float pM;
};


#endif //EX1_SIMVIRUS_MERS_H
