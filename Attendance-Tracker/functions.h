#ifndef FUNCTIONS_H
#define FUNCTIONS_H




#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include "List.h"

using std::string; 
using std::vector;
using std::to_string;
using std::fstream;


//Reading functions
fstream& readRecordsNode(ListNode*& node, fstream& is);

bool readRecordsList(List& list);

fstream& readMasterNode(ListNode*& pNode, fstream& is);

bool readMasterList(List& list);

//Writing functions
bool writeMaster(List& list);

void reportType(List& list);

bool writeReportLastAbsence(List& list);

bool writeReportThreshold(List& list);

//Absence marking and editing functions
void markAbsences(List& list);

void editAbsence(List& list);

void editByName(List& list);

void editByIDnum(List& list);

void editHelper(ListNode*& pNode);
#endif // !FUNCTIONS_H