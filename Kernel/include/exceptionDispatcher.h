#ifndef EXCEPTION_DISPATCHER_H
#define EXCEPTION_DISPATCHER_H


void zero_division(uint64_t * instructionPointer, uint64_t * stackPointer);

void invalid_opcode(uint64_t * instructionPointer, uint64_t * stackPointer);

void exceptionDispatcher(int exceptionNum, uint64_t * instructionPointer, uint64_t * stackPointer);

void zero_division(uint64_t * instructionPointer, uint64_t * stackPointer);

void invalid_opcode(uint64_t * instructionPointer, uint64_t * stackPointer);

void writeRegisters(uint64_t * instructionPointer, uint64_t * stackPointer);


#endif
