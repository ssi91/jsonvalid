//
// Created by ssi on 17.03.15.
//

#include <iostream>
#include "fsmjson.h"
#include "renderexception.h"

int main()
{
	try
	{
		std::string testStr = "{\"error\":{\"error_code\":5,\"error_msg\":\"User authorization failed: invalid session.\",\"request_params\":[{\"key\":\"oauth\",\"value\":\"1\"},{\"key\":\"method\",\"value\":\"messages.get\"},{\"key\":\"out\",\"value\":\"0\"},{\"key\":\"count\",\"value\":\"1\"},{\"key\":\"user_id\",\"value\":\"9556448\"},{\"key\":\"v\",\"value\":\"5.27\"}]}}";
		FSMJson fsmJson("{\"@:#\"}[],.\"\"");
		fsmJson.setInMap(testStr.c_str());
	}
	catch (RenderException *e)
	{
		std::cout << e->what();
	}
	return 0;
}