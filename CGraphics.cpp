#include "CGraphics.h"

void CGraphics::Receive()
{
	while (!queue->isSendingDone.load()  || !queue->isEmpty())
	{
		if (queue->isFlushing.load())
			continue;
		
		ERQCommand cmd = queue->ReadCommand();
		queue->isProcessingDone.store(false);
		switch (cmd)
		{
			case ERQCommand::INVALID:
				continue;
			break;

			case ERQCommand::PRINT_VALUE:
			{
				uint32_t value = queue->ReadValue();
				Process(value);
			}
			break;

			case ERQCommand::PRINT_STRING:
			{
				uint32_t size = queue->ReadValue();
				const char* data{};
				try
				{
					 data = queue->ReadData(size);
				}
				catch (...)
				{
					// forced done
					queue->isProcessingDone.store(true);
					queue->isProcessingDone.notify_all();
					continue;
				}
				Process(data, size);
			}
			break;

			default:
				continue;
		}
	}

	std::cout << "All received\n";
}

void CGraphics::Process(uint32_t value)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "\t\t\t\t\t====> Processed value: " << value << "\n";

	queue->isProcessingDone.store(true);
	queue->isProcessingDone.notify_all();
}

void CGraphics::Process(const char* data, size_t size)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::string str(data);
	std::cout << "\t\t\t\t\t====> Processed string: \"" << str << "\"\n";

	queue->isProcessingDone.store(true);
	queue->isProcessingDone.notify_all();
}
