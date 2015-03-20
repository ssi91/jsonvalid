//
// Created by ssi on 17.03.15.
//

#include <iostream>
#include "fsmjson.h"
int main (){
	FSMJson fsmJson("{\"@:#\"}[],.\"\"");
	fsmJson.isValidJson("ddfdf");
//	std::cout << FSMJson::MARK_DEF;
	return 0;
}