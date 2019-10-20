#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

int main(int argc, char const *argv[])
{
	int size=atoi(argv[3]);
	int compMiss=0,capMiss=0,totAccess=0;
	ifstream fptr;
	fptr.open(argv[2]);
	fstream fout;
	char fname[150]="CS17BTECH11010_";
	strcat(fname,argv[1]);
	strcat(fname,"_");
	strncat(fname,argv[2],strlen(argv[2])-4);
	strcat(fname,"_");
	strcat(fname,argv[3]);
	strcat(fname,".out");
	fout.open(fname,ios::trunc|ios::out);
	vector <string> Address;
	vector <string> SetOfAddress;
	vector <string> Answers;
	string newAdd;
	if(strcmp(argv[1],"LRU")==0){
		fptr>>newAdd;
		while(!fptr.eof()){
			if(find(Address.begin(), Address.end(), newAdd)==Address.end()){
				Answers.push_back("MISS");
				if(Address.size()==size)
					Address.erase(Address.begin());
				Address.push_back(newAdd);
				if(find(SetOfAddress.begin(), SetOfAddress.end(), newAdd)==SetOfAddress.end()){
					SetOfAddress.push_back(newAdd);
					compMiss++;
				}
				else
					capMiss++;
			}
			else{
				Answers.push_back("HIT");
				Address.erase(find(Address.begin(), Address.end(), newAdd));
				Address.push_back(newAdd);
			}
			totAccess++;
			fptr>>newAdd;
		}
	}
	else if(strcmp(argv[1],"FIFO")==0){
		fptr>>newAdd;
		while(!fptr.eof()){
			if(find(Address.begin(), Address.end(), newAdd)==Address.end()){
				Answers.push_back("MISS");
				if(Address.size()==size)
					Address.erase(Address.begin());
				Address.push_back(newAdd);
				if(find(SetOfAddress.begin(), SetOfAddress.end(), newAdd)==SetOfAddress.end()){
					SetOfAddress.push_back(newAdd);
					compMiss++;
				}
				else
					capMiss++;
			}
			else
				Answers.push_back("HIT");
			totAccess++;
			fptr>>newAdd;
		}
	}
	else if(strcmp(argv[1],"OPTIMAL")==0){
		int pos,value,iteration;
		vector <int> nextAccess;
		string checkAdd;
		fptr>>newAdd;
		while(!fptr.eof()){
			pos=fptr.tellg();
			fptr>>checkAdd;
			value=0;
			while(!fptr.eof()){
				value++;
				if(newAdd.compare(checkAdd)==0)
					break;
				fptr>>checkAdd;
			}
			if(newAdd.compare(checkAdd)==0)
				nextAccess.push_back(value);
			else
				nextAccess.push_back(50001);
			fptr.clear();
			fptr.seekg(pos,ios::beg);
			if(find(Address.begin(), Address.end(), newAdd)==Address.end()){
				Answers.push_back("MISS");
				if(Address.size()==size){
					iteration=distance(nextAccess.begin(),max_element(nextAccess.begin(), nextAccess.end()-1));
					Address.erase(Address.begin()+iteration);
					nextAccess.erase(max_element(nextAccess.begin(), nextAccess.end()-1));
				}
				Address.push_back(newAdd);
				if(find(SetOfAddress.begin(), SetOfAddress.end(), newAdd)==SetOfAddress.end()){
					SetOfAddress.push_back(newAdd);
					compMiss++;
				}
				else
					capMiss++;
			}
			else{
				Answers.push_back("HIT");
				nextAccess.erase(nextAccess.begin()+distance(Address.begin(),find(Address.begin(), Address.end(), newAdd)));
				Address.erase(find(Address.begin(), Address.end(), newAdd));
				Address.push_back(newAdd);
			}
			for(int i=0; i<nextAccess.size(); i++)
				nextAccess[i]--;
			totAccess++;
			fptr>>newAdd;
		}
		nextAccess.clear();
	}
	fout<<"TOTAL_ACCESSES = "<<totAccess<<endl;
	fout<<"TOTAL_MISSES = "<<compMiss+capMiss<<endl;
	fout<<"COMPULSORY_MISSES = "<<compMiss<<endl;
	fout<<"CAPACITY_MISSES = "<<capMiss<<endl;
	for(int i=0;i<Answers.size();i++)
		fout<<Answers[i]<<endl;
	Answers.clear();
	Address.clear();
	SetOfAddress.clear();
	fptr.close();
	fout.close();
	return 0;
}
