#ifndef CRENDERQUEUE_H
#define CRENDERQUEUE_H

#include "ERQCommand.h"

#include <iostream>
#include <queue>
#include <semaphore>

class CRenderQueue
{
	std::queue<char> buffer;
	std::uint32_t maxSize;

	std::counting_semaphore<100> semWrite{ 100 };
	std::counting_semaphore<100> semRead{ 0 };
	std::binary_semaphore semData{ 1 };

public:
	CRenderQueue(uint32_t size) : maxSize(size) {};
	
	void WriteCommand(ERQCommand cmd);
	void WriteValue(uint32_t value);
	void WriteData(const char* data, size_t size);

	ERQCommand ReadCommand();
	uint32_t ReadValue();
	const char* ReadData(size_t size);

	void Flush();
	void Reset();

	bool isEmpty() { return buffer.empty(); }

	std::atomic<bool> isSendingDone{ false };
	std::atomic<bool> isProcessingDone{ false };
	std::atomic<bool> isFlushing{ false };
};

#endif // !CRENDERQUEUE_H
