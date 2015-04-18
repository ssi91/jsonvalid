//
// Created by ssi on 17.03.15.
//

#include <iostream>
#include "fsmjson.h"

int main()
{
	std::string testStr = "{\"error\":{\"error_code\":5,\"error_msg\":\"User authorization failed: invalid session.\",\"request_params\":[{\"key\":\"oauth\",\"value\":\"1\"},{\"key\":\"method\",\"value\":\"messages.get\"},{\"key\":\"out\",\"value\":\"0\"},{\"key\":\"count\",\"value\":\"1\"},{\"key\":\"user_id\",\"value\":\"9556448\"},{\"key\":\"v\",\"value\":\"5.27\"}]}}";
	FSMJson fsmJson("{\"@:#\"}[],.\"\"");
	if (fsmJson.isValidJson(testStr.c_str()))
		std::cout << "valid" << std::endl;
	size_t state = 0, endIndex;
	size_t start = 0;

	for (int i = 0; i < 4; ++i)
	{
		state = fsmJson.getNextState(testStr.c_str(), state, endIndex, start);
		if (state == 3)
		{
			testStr = testStr.substr(start, endIndex - start);
			start = 0;
			std::cout << state << ": " + testStr << std::endl;
		}
		else
		{
			std::cout << state << ": " + testStr.substr(start, endIndex - start) << std::endl;
			start = endIndex;
		}
	}
	return 0;
}