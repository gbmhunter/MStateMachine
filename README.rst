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
- Last Modified: 2014-09-08
- Version: v1.0.0.0
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

To be compatible with mid-range microcontrollers, no exceptions are used, the entire module has a no-throw guarantee.
	

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
v1.0.0.0  2014-09-08 Initial commit. Basic state machine and state objects working, along with a few helper macros to tidy up the interface. Basic test working (toggling between two states).
========= ========== ====================================================================================