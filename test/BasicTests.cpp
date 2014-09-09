//!
//! @file 			BasicTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-09-08
//! @last-modified 	2014-09-09
//! @brief 			Contains basic tests.
//! @details
//!					See README.rst in root dir for more info.

// System includes
#include <iostream>
#include <unistd.h>
#include <cstring>

// User libraries
#include "MUnitTestCpp/api/MUnitTestApi.hpp"

// User source
#include "../api/MStateMachineApi.hpp"

using namespace MbeddedNinja;

namespace MStateMachineTestsNs
{

	class TestSm : public MStateMachineNs::StateMachine
	{

	public:
		TestSm()
			: StateMachine()
		{}

		void Transitions(uint32_t returnCode);
	};

	class StAwake : public MStateMachineNs::State
	{
		public:

		StAwake(const char * uniqueId)	:
			State(uniqueId)
		{}

		enum ReturnCodes
		{
			AWAKE
		};

		uint32_t HandlerFunc()
		{
			std::cout << "StAwake::HandlerFunc() called." << std::endl;
			return AWAKE;
		}
	};

	class StSleeping : public MStateMachineNs::State
	{
	public:
		StSleeping(const char * uniqueId)	:
			State(uniqueId)
		{}

		enum ReturnCodes
		{
			SLEPT
		};

		static uint32_t uniqueId;


		uint32_t HandlerFunc()
		{
			std::cout << "StSleeping::HandlerFunc() called." << std::endl;
			return SLEPT;
		}
	};

	void TestSm::Transitions(uint32_t returnCode)
	{
		sleep(1);

		std::cout << "currStateNum = '" << this->currStateNum << "'." << std::endl;
		//std::cout << "CurrState UniqueId = '" << this->states[currStateNum]->GetId() << "'." << std::endl;
		//std::cout << "StAwake UniqueId = '" << StAwake::uniqueId << "'." << std::endl;
		//std::cout << "StSleeping UniqueId = '" << StSleeping::uniqueId << "'." << std::endl;
		//std::cout << "this->states[0]->uniqueId = '" << this->states[0]->GetId() << "'." << std::endl;
		//std::cout << "this->states[1]->uniqueId = '" << this->states[1]->GetId() << "'." << std::endl;

		MString temp = this->CurrStateId();
		std::cout << "temp = '" << temp.cStr << "'." << std::endl;
		//std::cout << "strcmp = '" << strcmp(temp.cStr, "StAwake") << "'." << std::endl;
		std::cout << "strcmp = '" << strcmp(this->CurrStateId().cStr, "StAwake") << "'." << std::endl;
		std::cout << "this->currStateId = '" << this->CurrStateId() << "'." << std::endl;
		if(temp == "StAwake")
		{
			std::cout << "StAwake!." << std::endl;

			this->TransToState("StSleeping");
			//this->currStateNum = 1;
			return;

		}
		else if(temp == "StSleeping")
		{
			std::cout << "StSleeping!." << std::endl;
			this->TransToState("StAwake");
			return;
		}

	}

	MTEST(BasicTest)
	{
		//MyData myData;
		//std::cout << "Num states = '" << satModemSm.numOfStates << "'." << std::endl;
		StAwake stAwake("StAwake");
		//std::cout << "Num states = '" << satModemSm.numOfStates << "'." << std::endl;
		StSleeping stSleeping("StSleeping");
		TestSm satModemSm;
		satModemSm.AddState(&stAwake);
		satModemSm.AddState(&stSleeping);
		std::cout << "Num states = '" << satModemSm.numOfStates << "'." << std::endl;
		std::cout << ((char *)"Running state machine...") << std::endl;
		satModemSm.Run();
		std::cout << ((char *)"State machine returned!") << std::endl;
	}

	MTEST(BasicCheckEqualTest)
	{
		// Check capacity is calculated correctly
		CHECK_EQUAL("Testing", "Testing");
	}

} // namespace MUnitTestTestsNs
