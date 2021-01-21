//
// Created by lior on 10/04/2020.
//


#include <string>
#include <sstream>
#include <algorithm>
#include "SimVirus.h"
using namespace std;

const int MAX_SIM_TIME = 1000000;

/**
 *	this function init the virus classes and the simVirus class with the data from the input files
 *	and also checking the input data validation(thros exception if somthing is wrong with data)
 *
 *
 * @param configDat fileName data for the length,sim_time,and target string
 * @param firstGenDat fileName data for the virus number and virus char kind and genome string
 */
SimVirus::SimVirus(string configDat, string firstGenDat) :len(0),max_time(0), target(""){
	
	try{
		configInit(configDat);
	} catch (xWrongLen) {
		cerr << "bad config input : length" << endl;
		exit(1);
	} catch (xBadTime) {
		cerr << "bad config input : sim time" << endl;
		exit(1);
	} catch (xBadGenome) {
		cerr << "bad config input : target name" << endl;
		exit(1);
	}
	try {
		firstGenInit(firstGenDat);
	} catch (xBadPopulation) {
		cerr << "bad first_generation input : population error" << endl;
		exit(1);
	}  catch (xBadVirusName) {
		cerr << "bad first_generation input : wrong virus char name" << endl;
		clear();
		exit(1);
	}
	try{
		checkFirstInput();
	} catch (xBadGenome) {
		cerr << "bad first_generation input : wrong virus genome format" << endl;
		clear();
		exit(1);
	}
	removeSpaces();
    newGenInit();
	
}

SimVirus::~SimVirus() {

}

/**
 * starting the simulation and stops if got a match of 1.0 to string target or reached maximum sim time
 * after finished adding spaces to the strings and prints results
 */
void SimVirus::start() {
	int time = 0;
	while(time < max_time && !isMatch()){
		run();
		time++;
	}
	space();
	print();
}

/**
 *  doing private update and group update to the viruses
 */
void SimVirus::run() {
	privateUpdate();
	groupUpdate();
}

/**
 * reading the data from file using fstream and puts the input data into variables
 * also checks for input validation and if bad input throws exception
 * @param configData file name to read the data from
 */
void SimVirus::configInit(string configData) {
	ifstream in;
	in.open(configData);
	string l;
	string gen;
	string max;
	getline(in,l,'\n');
	getline(in,gen,'\n');
	getline(in,max,'\n');
	len = atoi(l.c_str());
	checkLen(len);
	target += gen;
	checkGenome(target);
	target.erase(remove(target.begin(), target.end(), ' '), target.end());
	max_time = atoi(max.c_str());
	checkTime(max_time);
	in.close();
}


/**
 * reading the data from file using fstream and popultates the Virus* vectors of firstGen and newGen
 * also checks the validation of the virus number and the virus names if bad input throws exception
 * @param firstGenData file name to read the data from
 */
void SimVirus::firstGenInit(string firstGenData) {
    ifstream in;
    in.open(firstGenData);
    string line;
    string line2;
    getline(in,line,'\n');
    virus_number = atoi(line.c_str());
    checkPopulation(virus_number);
    char c;
    while(getline(in,line)){
        c = line[0];
        size_t start = line.find_first_of(" ");
        size_t end = line.size();
        line2 = line.substr(start+1,end - start);
        switch(c){
            case 's':{
                firstGen.push_back(new Sars(c, line2,len));
                newGen.push_back(new Sars(c, line2,len));
                break;
            }
            case 'm':{
                firstGen.push_back(new Mers(c,line2,len));
                newGen.push_back(new Mers(c,line2,len));
                break;
            }
            case 'c':{
                firstGen.push_back(new Covid(c,line2,len));
                newGen.push_back(new Covid(c,line2,len));
                break;
            }
	        default:{
	        	checkVname(c);
	        }
        }
    }
    in.close();
}


/**
 * printing the results
 * if the sim time is 0 then gets the strongest virus and printing results
 */
void SimVirus::print() {
	if(max_time == 0){
		strongest = newGen[0];
		for(auto i : newGen){
			if(strongest->getPower() < i->getPower()){
				strongest = i;
			}
		}
		for(auto const& i : newGen){
			i->print();
			cout << endl;
		}
		cout << endl;
		for(auto const& i : firstGen){
			i->print();
			cout << i->getRefCount() << endl;
		}
		cout << endl;
		cout << strongest->getKind() << " " << strongest->getGenome() << endl;
		return;
	}
	for(auto const& i : newGen){
		i->print();
		cout << endl;
	}
	cout << endl;
	for(auto const& i : firstGen){
	    i->print();
	    cout << i->getRefCount() << endl;
    }
	cout << endl;
	cout << strongest->getKind() << " " << strongest->getGenome() << endl;
}

/**
 * check for match between virus to the target
 * @return if match is 1.0 return true and end the sim else false
 */
bool SimVirus::isMatch() const {
	for(auto const& i : newGen){
		if(i->getPower() == 1.0){
			return true;
		}
	}
	return false;
}

/**
 * gets a string and send it to hits func whice returns the nuber of index counter of chars that matching to the target
 * string and returns the result divide by the len of string
 */
float SimVirus::match_strength(const string& h) const {
	return hits(h)/len;
}

/**
 * counts the chars of the h string that match the target string return counter
 */
float SimVirus::hits(const string& h) const {
	float cnt = 0;
	for (unsigned int i = 0; i < h.length() ; ++i) {
		if(h[i] == target[i]) {
			cnt++;
		}
	}
	return cnt;
}

/**
 * setting the virus match power to the target string
 */
void SimVirus::newGenStrength() {
	for(auto i : newGen){
		i->setPower(match_strength(i->getGenome()));
	}
}

/**
 * init the rc count and pointers to the beginning state of the sim
 * also sets the first power of newGen viruses for the first time
 */
void SimVirus::newGenInit() {
	for (int i = 0; i < virus_number ; ++i) {
		newGen[i]->setAnccestor(firstGen[i]);
		firstGen[i]->addCount();
	}
	strongest = newGen[0];
	newGenStrength();
}

/**
 * using the polymorphic func update which will act diffrently for each class the derived from base class virus
 */
void SimVirus::privateUpdate() {
	for(auto i : newGen){
		i->update();
	}
}

/**
 * choosing 2 random viruses indexes from the firstGen and swapping parts of their string with each other
 * also with 2 random string indexes that has been chosen.
 * without changing the first index and the last index chars of their string so that the original
 * genome of the virus will stay his.
 * then updating the match power of the viruses to target string
 * then after that sorting the virus* vector of newGen using lambda which compare the virus match strangth
 * after sorting taking the 2 of the most week viruses and then changing the reference count
 */
void SimVirus::groupUpdate() {
	//random virus indexes
	int i1 = rand()%virus_number;
	int i2 = rand()%virus_number;
	
	//random indexes for the string swaping
	int s = ((rand())%(len-3))+1;
	int t = ((rand())%(len-3))+2;
	
	//if the index equal to each other then swap only the s index between strings
	if(s == t){
		char c1 = newGen[i1]->getGenome()[s];
		char c2 = newGen[i2]->getGenome()[s];
		newGen[i1]->setChar(s,c2);
		newGen[i2]->setChar(s,c1);
		sort(newGen.begin(),newGen.end(),[](Virus* a, Virus* b )->bool{ return a->getPower() < b->getPower() ;});
		if(strongest->getPower() < newGen.back()->getPower()){
			strongest = newGen.back();
		}
		newGen[0]->getAnccestor()->removeCount();
		newGen[0]->setAnccestor(firstGen[i1]);
		newGen[0]->getAnccestor()->addCount();
		newGen[1]->getAnccestor()->removeCount();
		newGen[1]->setAnccestor(firstGen[i2]);
		newGen[1]->getAnccestor()->addCount();
		return;
	}
	
	//if the index t bigger then swap between s and t then continue calc
	if(s > t){
		int temp = s;
		s = t;
		t = temp;
	}
	size_t subSlen = (t-s)+1;
	string sub1 = newGen[i1]->getGenome().substr(s,subSlen);
	string sub2 = newGen[i2]->getGenome().substr(s,subSlen);
	const_cast<string&>(newGen[i1]->getGenome()).replace(s,subSlen,sub2);
	const_cast<string&>(newGen[i2]->getGenome()).replace(s,subSlen,sub1);
	
	newGenStrength(); // updates virus match power
	
	//sorting the vector from week to strong viruses
	sort(newGen.begin(),newGen.end(),[](Virus* a, Virus* b )->bool{ return a->getPower() < b->getPower() ;});
	
	// updates the strongest virus
	if(strongest->getPower() < newGen.back()->getPower()){
		strongest = newGen.back();
	}
	
	// updating the references count from most week virus to the 2 random anccestor indexes
	newGen[0]->getAnccestor()->removeCount();
	newGen[0]->setAnccestor(firstGen[i1]);
	newGen[0]->getAnccestor()->addCount();
	newGen[1]->getAnccestor()->removeCount();
	newGen[1]->setAnccestor(firstGen[i2]);
	newGen[1]->getAnccestor()->addCount();
	
}

// free all the allocated memory of the virus*
void SimVirus::clear() {
	for (auto i : firstGen){
		delete i;
	}
	for (auto i : newGen){
		delete i;
	}
}

//after the spaces has been removed for calculation conviniant then adding spaces to the srings of viruses for the result printing format
void SimVirus::space() {
	for (auto i : firstGen){
		string userString = i->getGenome();
		string newString = "";
		for (auto itr : userString)
		{
			newString += itr;
			if(itr != userString[userString.length()])
				newString += ' ';
		}
		i->setGenome(newString);
	}
	for (auto i : newGen){
		string userString = i->getGenome();
		string newString = "";
		for (auto itr : userString)
		{
			newString += itr;
			if(itr != userString[userString.length()])
				newString += ' ';
		}
		i->setGenome(newString);
	}

	
}

/**
 * removing the spaces chars from the virus strings after pupoltaion before the private and group updates
 * so it will be more conviniant to do the updates and string swapping
 */
void SimVirus::removeSpaces() {
	string str;
	for(auto i : firstGen){
		str = i->getGenome();
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		i->setGenome(str);
	}
	for(auto i : newGen){
		str = i->getGenome();
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		i->setGenome(str);
	}
}

/**
 *  all the functions below are for the validation checking of the input
 *  each one of them checking input data validation and throwing excepyions if input data inst valid
 */
void SimVirus::checkLen(int len) const{
	if(len < 3 || len > 10000){
		throw xWrongLen();
	}
}

void SimVirus::checkTime(int time) const{
	if(max_time > MAX_SIM_TIME || max_time < 0){
		throw xBadTime();
	}
}

void SimVirus::checkPopulation(int p) const{
	if(!isalpha(p)){
		if(virus_number < 2 || virus_number > 1000){
			throw xBadPopulation();
		}
	} else{
		throw xBadPopulation();
	}
}

void SimVirus::checkGenome(const string& genome) const{
	int char_num = 0;
	int spaces_num = 0;
	bool end = false;
	string res = "";
	for (int i = 0; i < (int)genome.length() ; ++i) {
		if(isalpha(genome[i])){
			if(genome[i] != 'T' && genome[i] != 'A' && genome[i] != 'C' && genome[i] != 'G'){
				throw xBadGenome();
			} else{
				if(end){
					if(isalpha(genome[i])){
						throw xBadGenome();
					} else
						continue;
				}
				char_num++;
				res += genome[i];
			}
		}
		else if(isspace(genome[i])){
			if(end){
				continue;
			}
			spaces_num++;
		} else{
			if(char_num == len){
				end = true;
			}
		}
	}
	if(char_num != len){
		throw xBadGenome();
	}

}

void SimVirus::checkVname(char vName) const {
	if(isalpha(vName)){
		if(vName != 's' && vName != 'm' && vName != 'c'){
			throw xBadVirusName();
		}
	} else{
		throw xBadVirusName();
	}
}

void SimVirus::checkFirstInput() {
	for(auto i : firstGen){
		checkGenome(i->getGenome());
	}
}








