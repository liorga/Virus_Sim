//
// Created by lior on 03/04/2020.
//

#ifndef EX1_SIMVIRUS_COVID_H
#define EX1_SIMVIRUS_COVID_H

#include "Virus.h"
class Covid : public Virus{
public:
	Covid(char c, const string& gen, int l);
	virtual ~Covid();
    void update() ;
    void print() const;

private:
	float pM;
};


#endif //EX1_SIMVIRUS_COVID_H
