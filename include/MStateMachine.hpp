//!
//! @file				MStateMachine.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-09-08
//! @last-modified		2014-09-09
//! @brief				
//! @details
//!						See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef M_STATE_MACHINE_CPP_M_STATE_MACHINE_H
#define M_STATE_MACHINE_CPP_M_STATE_MACHINE_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MStateMachineNs
	{

		class StateMachine;

	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// System headers
#include <cstdint>		// int8_t, int32_t e.t.c
#include <vector>
#include <iostream>
#include <cstring>

// User libraries
#include "MStringCpp/api/MStringApi.hpp"

// User headers
// none



namespace MbeddedNinja
{
	namespace MStateMachineNs
	{

		class State
		{

		public:

			virtual uint32_t HandlerFunc() = 0;

			//virtual void Transition() = 0;

			State(const char * uniqueId)
			{
				// Save the unique ID
				this->uniqueId = uniqueId;
			}


			//uint32_t returnCode;
			uint32_t stateIndex;
			const char * uniqueId;

			StateMachine * stateMachine;

		private:



		}; // class State

		//! @brief		Virtual state machine class which is designed to be inherited by concrete
		//!				state machine classes.
		class StateMachine
		{

		public:

			//! @todo	Add dynamic allocation.
			State * states[10];

			//! @brief		Remebers the total number of states registered with this state machine.
			uint32_t numOfStates;

			//! @brief		Remebers what is the current state. Modified from
			//!				Transitions by calling TransToState().
			uint32_t currStateNum;

			StateMachine() :
				numOfStates(0),
				currStateNum(0)
			{

			}

			//virtual ~StateMachine(){};

			void TransToState(const char * uniqueId)
			{
				//std::cout << "Looking for state..." << std::endl;
				for(uint32_t x = 0; x < this->numOfStates; x++)
				{
					if(strcmp(uniqueId, this->states[x]->uniqueId) == 0)
					{
						//std::cout << "State found!" << std::endl;
						this->currStateNum = x;
						return;
					}
				}
				//std::cout << "ERROR" << std::endl;

			}

			//! @brief		Call to find out what the current state unique ID is.
			MString CurrStateId()
			{
				//std::cout << "Returning '" << MString(this->states[this->currStateNum]->uniqueId) << "'." << std::endl;
				MString myString(this->states[this->currStateNum]->uniqueId);
				return myString;
			}


			void AddState(State * state)
			{
				// Save into state machine state array
				this->states[this->numOfStates] = state;
				// Save stateIndex in state
				state->stateIndex = this->numOfStates;

				//std::cout << "state->stateIndex = '" << state->stateIndex << "'." << std::endl;
				this->numOfStates++;
			}

			//! @brief		The method which controls state transitions, based on the current
			//!				state and the returned state code.
			virtual void Transitions(uint32_t returnCode) = 0;

			//! @warning	Will not return!
			void Run()
			{

				while(true)
				{

					uint32_t returnCode = this->states[this->currStateNum]->HandlerFunc();
					// This should modify currStateNum
					this->Transitions(returnCode);
				}
			}
		};


	} // namespace MStateMachineNs

} // namespace MbeddedNinja

#endif	// #ifndef M_STATE_MACHINE_CPP_M_STATE_MACHINE_H

// EOF
