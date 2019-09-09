# Design-And-Implementation-Of-32-Bit-Virtual-Computer-Based-On-Simulation
基于仿真的32位虚拟计算机设计与实现，计算机组成原理与系统结构课程设计

Abstract: in this paper, according to the learning requirements of computer composition principle and system structure course, in order to further study the execution of different instructions in CPU and pipeline process, and try to use different solutions to solve pipeline block, based on C/C++ language, a 32-bit virtual computer is designed and implemented.The virtual computer USES MIPS32 instruction set, which can simulate running most MIPS32 instructions, show the pipeline process of instructions in the computer, and solve data conflicts by suspending execution.Finally, in order to show the pipeline process more vividly, this paper USES computer graphics library graphics.h to program the pipeline generation program, and completes all the goals of the design task book with the use of the system.

Key words: virtual computer, MIPS32 instruction set, pipeline, C/C++

1 project introduction

Project description: develop virtual computer based on MIPS32 instruction system by C/C++ language.Requirements:

(1) software simulation to complete the five steps of picking, decoding, computing, memory access and writing back of MIPS32 instruction

(2) able to input machine language source programs into the system

(3) be able to start the internal register

(4) able to run programs

(5) it can check the running results and reflect the execution process of instructions

(6) can simulate the execution process of five-stage pipeline

(7) able to solve data-related problems

(8) can reflect the execution process of pipeline

Development language: C/C++

Development environment: Windows10 1803, Visual Studio 2017

2 function introduction

2.1 an overview of the

In order to meet the program design requirements set forth in the "project introduction", it is necessary to have a clear division of the program functions, so that users can quickly get used to and skillfully use the program.In this section, the author will make a brief introduction to each functional module of the program, so as to help users quickly know the module division of the program, the functions of each module and the use method of each module.

This program is divided into 8 functional modules, which are: 1- instruction control, 2- instruction execution, 3- memory control, 4- register control, 5- pipeline, 6- instructions, 7- about, 8- exit.Each function module has its different function and function, the reader may guess from the function module name.Each function module also has different small modules, the specific introduction will be described in detail below.

In order to show the process of pipeline more vividly, the author also compiled a program based on graphics graphics library using C language alone to present the information output by the console in a graphical way.This function module will also be described in detail below.