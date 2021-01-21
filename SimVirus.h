//
// Created by lior on 10/04/2020.
//

#ifndef EX1_SIMVIRUS_SIMVIRUS_H
#define EX1_SIMVIRUS_SIMVIRUS_H
#include <vector>
#include <fstream>
#include <regex>
#include "Virus.h"
#include "Sars.h"
#include "Mers.h"
#include "Covid.h"

/**
 * simVirus class is in charge of the simulation and calculation of the virus world
 */
class SimVirus {
public:
	
	SimVirus(string configDat, string firstGenDat);
	virtual ~SimVirus();
	void configInit(string configData);
	void firstGenInit(string firstGenData);
	void print() ;
	void start();
	bool isMatch() const;
	float hits(const string& h) const;
	float match_strength(const string& h) const;
	void newGenStrength();
	void newGenInit();
	void privateUpdate();
	void groupUpdate();
	void run();
	void clear();
	void space();
	void removeSpaces();

	//input check functions
	void checkLen(int len) const; //string length dim
	void checkTime(int time) const; //check sim time passes validation
	void checkPopulation(int p) const; // check population fron input validation
	void checkGenome(const string& genome) const; //check Virus genome validation
	void checkVname(char vName) const; //check virus chars validation
	void checkFirstInput();
	
	//exception classes
	class xWrongLen {};
	class xBadTime{};
	class xBadPopulation{};
	class xBadVirusName{};
	class xBadGenome{};


private:
	int len;
	int virus_number;
	int max_time;
	string target;
	vector<Virus *> firstGen;
	vector<Virus *> newGen;
	Virus *strongest;
};

#endif //EX1_SIMVIRUS_SIMVIRUS_H