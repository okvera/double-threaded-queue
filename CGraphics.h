#ifndef CGRAPHICS_H
#define CGRAPHICS_H

#include "CRenderQueue.h"
#include "ERQCommand.h"

#include <iostream>
#include <thread>

class CGraphics
{
	CRenderQueue* queue;

	void Process(uint32_t value);
	void Process(const char* data, size_t size);

public:
	CGraphics(CRenderQueue* q) : queue(q) {};
	void Receive();
};

#endif // !CGRAPHICS_H
