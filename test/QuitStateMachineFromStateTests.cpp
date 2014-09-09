//!
//! @file 			QuitStateMachineFromStateTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-09-09
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

	class QuitFromStateSm : public MStateMachineNs::StateMachine
	{

	public:
		QuitFromStateSm()
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

		uint32_t Run()
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


		uint32_t Run()
		{
			std::cout << "StSleeping::HandlerFunc() called." << std::endl;
			return SLEPT;
		}
	};

	void QuitFromStateSm::Transitions(uint32_t returnCode)
	{
		sleep(1);

		static uint32_t callCounter = 0;
		callCounter++;
		if(callCounter == 6)
		{
			// Lets quit the state machine
			this->quitStateMachine = true;
		}

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

	MTEST(QuitStateMachineFromStateTest)
	{
		StAwake stAwake("StAwake");
		StSleeping stSleeping("StSleeping");
		QuitFromStateSm quitFromStateSm;
		quitFromStateSm.AddState(&stAwake);
		quitFromStateSm.AddState(&stSleeping);
		//std::cout << "Num states = '" << satModemSm.numOfStates << "'." << std::endl;
		std::cout << "Running state machine..." << std::endl;
		quitFromStateSm.Run();
		std::cout << "State machine returned!" << std::endl;
		CHECK(true);
	}

} // namespace MUnitTestTestsNs
