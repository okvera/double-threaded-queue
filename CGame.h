#ifndef CGAME_H
#define CGAME_H

#include "CRenderQueue.h"
#include "ERQCommand.h"

#include <iostream>
#include <random>
#include <chrono>

class CGame
{
	CRenderQueue* queue;

	void NormalDataTest();
	void IncorrectDataTest();
	void FlushBufferTest();
	void ResetBufferTest();

public:
	CGame(CRenderQueue* q) : queue(q) {};
	void Send(int testType);
};

#endif // !CGAME_H
