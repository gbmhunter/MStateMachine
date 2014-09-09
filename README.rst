================
MStateMachineCpp
================

-------------------------------------------------------------------------------------------------------
A microcontroller-friendly C++ state machine framework specifically designed for embedded applications.
-------------------------------------------------------------------------------------------------------

.. image:: https://api.travis-ci.org/mbedded-ninja/MStateMachineCpp.png?branch=master   
	:target: https://travis-ci.org/mbedded-ninja/MStateMachineCpp

- Author: gbmhunter <gbmhunter@gmail.com> (www.mbedded.ninja)
- First Ever Commit: 2014-09-08
- Last Modified: 2014-09-09
- Version: v1.1.2.0
- Company: mbedded.ninja
- Project: MToolkit
- Language: C++
- Compiler: GCC	
- uC Model: Any
- Computer Architecture: Any
- Operating System: Any
- Documentation Format: Doxygen
- License: GPLv3

Description
===========

A microcontroller-friendly C++ state machine framework specifically designed for embedded applications.

The main aims of this state machine framework are:

- To keep the transitional logic for the entire state machine in one place (logic is defined in :code:`StateMachine::Transitions()`).
- To seperate the general-purpose state procedural code from the transitional logic (state procedural code is defined in :code:`State::Run()`).
- To allow for complex transitional logic, i.e. not just a transition table. Guards are supported.
- To allow the framework to work with any OS (including Realtime OS's)
- To work well in an embedded environment

Basic Workflow
--------------

1. Inherit from :code:`StateMachine` to create your own concrete statemachine class, specifying definitions for :code:`StateMachine::Transitions()`. 

2. Inherit from :code:`State` to create your concrete states classes, specifying definitions for :code:`State::Run()` and an enumeration of return status's that :code:`State::Run()` could return (e.g. :code:`MSG_SENT_SUCCESSFULLY`, :code:`MSG_SENDING_FAILED`).

3. At runtime, create a concrete statemachine object, create your concrete state objects, and register the states with the state machine. This is usually done all within the same thread or task (note there is nothing stopping you from creating multiple statemachines in multiple threads).

4. Call :code:`StateMachine::Run()`, and the framework handles it from here.


To be compatible with mid-range microcontrollers, no exceptions are used, and the entire framework has a no-throw guarantee.
	

External Dependencies
=====================

Nothing here yet.

Issues
======

See GitHub Issues.

Limitations
===========

Nothing here yet.

Usage
=====

See the unit tests in the 'test/' directory for basic examples.

::

	
	
	
Changelog
=========

========= ========== ====================================================================================
Version   Date       Comment
========= ========== ====================================================================================
v1.1.2.1  2014-09-09 Added more to the description part of the README.
v1.1.2.0  2014-09-09 Removed inclusion of <vector> and <iostream> from 'MStateMachine.hpp', closes #4.
v1.1.1.0  2014-09-09 Changed 'State::HandlerFunc()' name to 'State::Run()', closes #3.
v1.1.0.0  2014-09-09 Swicthed to non-macro style state machine, as although it was making the syntax shorter, it was confusing things. Now using strings as the unique identifier for each state.
v1.0.0.0  2014-09-08 Initial commit. Basic state machine and state objects working, along with a few helper macros to tidy up the interface. Basic test working (toggling between two states).
========= ========== ====================================================================================