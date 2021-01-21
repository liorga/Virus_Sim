//
// Created by lior on 03/04/2020.
//

#ifndef EX1_SIMVIRUS_VIRUS_H
#define EX1_SIMVIRUS_VIRUS_H
#include <iostream>
using namespace std;

/**
 * Virus class is the base class that holds most of the virus data
 * has pure virtual func for polymorphism and diffrent behavior of the darived class sara mars and covid
 * and also has a Virus* field of anccestor and counter for the RC
 */
class Virus {
public:
    Virus(char c, const string& gen);
	Virus(const Virus& rhs);
	virtual ~Virus();
	//Virus& operator=(const Virus& rhs); didnt used it default was enough
	
	/**
	 * updates the string chars in each darived virus dinffrantly
	 * if the probabilty condition is true then changing the string
	 * sars : T to A and A to T
	 * mars : A to T ,C to G and G to C
	 * covid : T to A ,C to G and G to C
	 *
	 * each darived class has also diffrent PM for the update
	 */
	virtual void update() = 0;
	virtual void print() const = 0 ;

    char getKind() const;
    const string &getGenome() const;
    void setGenome(const string &genome);
	float getPower() const;
	void setPower(float power);
	void setChar(int i , char c);
	Virus *getAnccestor() const;
	void setAnccestor(Virus *anccestor);
	
	void addCount();
	void removeCount();
	int getRefCount() const;
	
private:
    char kind;
    string genome;
    float power;
	float l;
	Virus* anccestor;
	int refCount;

};


#endif //EX1_SIMVIRUS_VIRUS_H
