#include "CRenderQueue.h"

void CRenderQueue::WriteCommand(ERQCommand cmd)
{
	semWrite.acquire();

	std::cout << "Send command =====> " << cmd << "\n";
	buffer.push(static_cast<char>(cmd));

	semRead.release();
};

void CRenderQueue::WriteValue(uint32_t value)
{
	semWrite.acquire();

	//if (!buffer.empty())		/// ?
	std::cout << "Send value   =====> " << value << "\n";
	for (size_t i = 0; i < 4; ++i)
	{
		buffer.push(value & 0xFF);
		value >>= 8;
	}

	semRead.release();
};

void CRenderQueue::WriteData(const char* data, size_t size)
{
	semWrite.acquire();

	std::cout << "Send data    =====> \"" << std::string(data) << "\"\n";
	for (size_t i = 0; i < size; ++i)
	{
		buffer.push(data[i]);
	}

	semRead.release();
};

ERQCommand CRenderQueue::ReadCommand()
{
	semRead.acquire();

	ERQCommand cmd{ 0 };
	if (!buffer.empty())
	{
		cmd = static_cast<ERQCommand>(buffer.front());
		buffer.pop();
		try
		{
			std::cout << "\t\t\t\t\t====> Read command: " << cmd << "\n";
		}
		catch (...)
		{
			std::cout << "INVALID\n";
			cmd = ERQCommand::INVALID;
		}
	}

	if (!isFlushing.load() && !isSendingDone.load())
		semWrite.release();
	else
		semRead.release();
	return cmd;
};

uint32_t CRenderQueue::ReadValue()
{
	semRead.acquire();

	uint32_t res{ 0 };

	if (!buffer.empty())
	{
		for (size_t i = 0; i < 4; ++i)
		{
			unsigned char oneByte = static_cast<unsigned char>(buffer.front());
			res |= oneByte << (8 * i);
			buffer.pop();
		}
		std::cout << "\t\t\t\t\t====> Read value: " << res << "\n";
	}

	if (!isFlushing.load() && !isSendingDone.load())
		semWrite.release();
	else
		semRead.release();
	return res;
};

const char* CRenderQueue::ReadData(size_t size)
{
	semRead.acquire();

	char* res = new char[size + 1] {};

	if (!buffer.empty())
	{
		if (size > buffer.size())
			throw "Not enough data in buffer";
		for (size_t i = 0; i < size; i++)
		{
			res[i] = buffer.front();
			buffer.pop();
		}
		res[size] = '\0';
		std::cout << "\t\t\t\t\t====> Read data: \"" << std::string(res) << "\"\n";
	}

	if (!isFlushing.load() && !isSendingDone.load())
		semWrite.release();
	else
		semRead.release();
	return res;
};


void CRenderQueue::Flush()
{
	isFlushing.store(true);
	std::cout << "\n.....waiting for flush....... \n\n";
	// wait current command to be processed
	while (!isProcessingDone.load())
	{
	}
	std::cout << "\n.....done...................... \n\n";
	isFlushing.store(false);
	// continue
	semWrite.release();
}

void CRenderQueue::Reset()
{
	isFlushing.store(true);
	std::cout << "\n.....waiting for reset....... \n\n";
	// wait for current command being processed // atomic flag ?
	while (!isProcessingDone.load())
	{
	}
	std::cout << "\n.....done...................... \n\n";
	// clear buffer
	buffer = {};
	// clear semaphores
	while (semRead.try_acquire())
	{
		semWrite.release();
	}
	isFlushing.store(false);
}
