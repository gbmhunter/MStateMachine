//!
//! @file				MStateMachine.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-09-08
//! @last-modified		2014-09-08
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

		template < typename ParentT >
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

// User headers
// none



namespace MbeddedNinja
{
	namespace MStateMachineNs
	{

		template < typename ParentT >
		class State
		{

		public:

			virtual void HandlerFunc() = 0;

			//virtual void Transition() = 0;

			State(StateMachine< ParentT > * stateMachine)
			{
				this->stateMachine = stateMachine;
				this->stateMachine->AddState(this);
				// Save to static instance variable
				State::myInstance = this;
			}

			static State * GetInstance()
			{
				return State::myInstance;
			}

			static State * myInstance;

			uint32_t returnCode;
			uint32_t stateIndex;

			StateMachine< ParentT > * stateMachine;

		private:



		}; // class State


		template <typename ParentT>
		typename MStateMachineNs::State< ParentT > * State< ParentT >::myInstance = nullptr;

		//! @brief		Virtual state machine class which is designed to be inherited by concrete
		//!				state machine classes.
		template < typename ParentT >
		class StateMachine
		{

		public:

			State< ParentT > * states[10];
			uint32_t numOfStates;
			uint32_t currStateNum;

			//! @brief		Pointer to parent object (the owner of the state machine).
			ParentT * parent;

			StateMachine(ParentT * parent) :
				numOfStates(0),
				currStateNum(0)
			{
				this->parent = parent;
			}

			//virtual ~StateMachine(){};


			void AddState(State< ParentT > * state)
			{
				// Save into state machine state array
				this->states[this->numOfStates] = state;
				// Save stateIndex in state
				state->stateIndex = this->numOfStates;
				std::cout << "state->stateIndex = '" << state->stateIndex << "'." << std::endl;
				this->numOfStates++;
			}

			virtual void Transition(uint32_t currIndex) = 0;

			void Run()
			{
				//CyDebugUart_PutString("Run() called!");
				while(true)
				{
					//CyDebugUart_PutString("Calling HandlerFunc()!");
					this->states[this->currStateNum]->HandlerFunc();
					// This should modify currStateNum
					this->Transition(currStateNum);
				}
			}
		};


		#define CREATE_STATE(StateName, ParentT)	\
			class StateName : public MbeddedNinja::MStateMachineNs::State< ParentT >

		#define DEFINE_RETURN_CODES()	\
			public:	\
			enum ReturnCodes

		#define DEFINE_HANDLER_FUNC(StateName, ParentT)	\
			StateName(MbeddedNinja::MStateMachineNs::StateMachine< ParentT > * stateMachine)	\
				: State(stateMachine)	\
			{};	\
			void HandlerFunc()

		#define RETURN_CODE(returnCode1)	\
			this->returnCode = returnCode1;	\
			return

		#define HANDLE_STATE(StateName)		\
			if(currIndex == StateName->stateIndex)


		#define HANDLE_CODE(StateName, ReturnCode)	\
			if(this->states[currIndex]->returnCode == StateName::ReturnCode)

		#define DEFINE_TRANSITIONS()	\
			void Transition(uint32_t currIndex)

	} // namespace MStateMachineNs

} // namespace MbeddedNinja

#endif	// #ifndef M_STATE_MACHINE_CPP_M_STATE_MACHINE_H

// EOF
