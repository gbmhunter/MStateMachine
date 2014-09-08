//!
//! @file 			BasicTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-09-08
//! @last-modified 	2014-09-08
//! @brief 			Contains basic tests.
//! @details
//!					See README.rst in root dir for more info.

// System includes
#include <iostream>
#include <unistd.h>

// User libraries
#include "MUnitTestCpp/api/MUnitTestApi.hpp"

// User source
#include "../api/MStateMachineApi.hpp"

using namespace MbeddedNinja;

namespace MStateMachineTestsNs
{

	class MyData
	{
	public:
		void Print(const char * msg)
		{
			std::cout << msg;

		}

	};

	class SatModemSm : public MStateMachineNs::StateMachine< MyData >
	{

	public:
		SatModemSm(MyData * satModem)
			: StateMachine(satModem)
		{}

		void Transition(uint32_t currentIndex);
	};

	CREATE_STATE(StPinging2, MyData)
	{
		DEFINE_RETURN_CODES()
		{
			MODEM_RESPONDED,
			MODEM_DID_NOT_RESPOND
		};

		DEFINE_HANDLER_FUNC(StPinging2, MyData)
		{
			this->stateMachine->parent->Print("StPinging handler called!");
			// Do stuff here, then return code
			RETURN_CODE(MODEM_RESPONDED);
			//this->returnCode = MODEM
			//this->returnCode = StPinging2ReturnCodes::MODEM_RESPONDED;
		}

	};

	CREATE_STATE(StSleeping2, MyData)
	{
		DEFINE_RETURN_CODES()
		{
			MODEM_SLEPT
		};

		DEFINE_HANDLER_FUNC(StSleeping2, MyData)
		{
			this->stateMachine->parent->Print("StSleeping handler called!");
			// Do stuff here, then return code
			RETURN_CODE(MODEM_SLEPT);
		}

	};

	void SatModemSm::Transition(uint32_t currIndex)
		{
			if(!StPinging2::GetInstance())
				std::cout << "GetInstance() NULL!!!";

			std::cout << "Curr index = '" << currIndex << "'." << std::endl;
			std::cout << "StPinging state index = " << (StPinging2::GetInstance())->stateIndex << std::endl;
			std::cout << "StSleeping state index = " << (StSleeping2::GetInstance())->stateIndex << std::endl;
			std::cout << "Return code = " << (StPinging2::GetInstance())->stateIndex << std::endl;

			sleep(1);

			switch(currIndex)
			{
				case 0:
				{
					std::cout << "Match found!" << std::endl;
					HANDLE_CODE(StPinging2, MODEM_RESPONDED)
					{
						this->currStateNum = 1;
					}
					break;
				}
				case 1:
				{
					HANDLE_CODE(StSleeping2, MODEM_SLEPT)
					{
						this->currStateNum = 0;
					}
					break;
				}

			}

		}

		MTEST(BasicTest)
		{
			MyData myData;
			SatModemSm satModemSm(&myData);
			std::cout << "Num states = '" << satModemSm.numOfStates << "'." << std::endl;
			StPinging2 stPinging2(&satModemSm);
			std::cout << "Num states = '" << satModemSm.numOfStates << "'." << std::endl;
			StSleeping2 stSleeping2(&satModemSm);
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
