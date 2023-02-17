#include "CGame.h"

void CGame::Send(int testType)
{
	switch (testType)
	{
	case 1:
		NormalDataTest();
		break;
	case 2:
		IncorrectDataTest();
		break;
	case 3:
		FlushBufferTest();
		break;
	case 4:
		ResetBufferTest();
		break;
	default:
		std::cout << "There is no test with number " << testType << "\n";
		queue->isSendingDone.store(true);
		break;
	}
}

void CGame::NormalDataTest()
{
	std::mt19937 engine{ std::random_device{}() };
	std::uniform_int_distribution<> msecDistr{ 10, 100 };
	std::uniform_int_distribution<uint32_t> valuesDistr{ 0, UINT32_MAX };

	std::cout << "Normal data test\n";
	std::cout << "-----------------\n\n";

	queue->isSendingDone.store(false);

	for (auto value = 1; value <= 10; ++value)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds{ msecDistr(engine) });
	
		queue->WriteCommand(ERQCommand::PRINT_VALUE);
		queue->WriteValue(valuesDistr(engine));
	}

	for (auto value = 10; value <= 20; ++value)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds{ msecDistr(engine) });

		queue->WriteCommand(ERQCommand::PRINT_STRING);
		std::string str{ "This is " + std::to_string(value) + " test string" };
		queue->WriteValue(static_cast<uint32_t>(str.size()));
		queue->WriteData(str.c_str(), str.size());
	}

	queue->isSendingDone.store(true);
	std::cout << "All sended\n";
}

void CGame::IncorrectDataTest()
{
	std::mt19937 engine{ std::random_device{}() };
	std::uniform_int_distribution<> msecDistr{ 10, 100 };
	std::uniform_int_distribution<uint32_t> valuesDistr{ 0, UINT32_MAX };

	std::cout << "Incorrect data test\n";
	std::cout << "-----------------\n\n";

	queue->isSendingDone.store(false);

	for (auto value = 1; value <= 5; ++value)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds{ msecDistr(engine) });

		queue->WriteCommand(ERQCommand::PRINT_VALUE);
		queue->WriteValue(valuesDistr(engine));
	}

	queue->WriteValue(valuesDistr(engine));
	queue->WriteCommand(ERQCommand::PRINT_VALUE);
	queue->WriteValue(valuesDistr(engine));

	for (auto value = 10; value <= 15; ++value)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds{ msecDistr(engine) });

		queue->WriteCommand(ERQCommand::PRINT_STRING);
		std::string str{ "This is " + std::to_string(value) + " test string" };
		queue->WriteValue(static_cast<uint32_t>(str.size()));
		queue->WriteData(str.c_str(), str.size());
	}

	queue->WriteCommand(ERQCommand::PRINT_STRING);
	std::string str{ "This is BAD test string, skip it" };
	queue->WriteData(str.c_str(), str.size());

	queue->isSendingDone.store(true);
	std::cout << "All sended\n";
}

void CGame::FlushBufferTest()
{
	std::mt19937 engine{ std::random_device{}() };
	std::uniform_int_distribution<> msecDistr{ 10, 100 };
	std::uniform_int_distribution<uint32_t> valuesDistr{ 0, UINT32_MAX };

	std::cout << "Flush buffer test\n";
	std::cout << "-----------------\n\n";

	queue->isSendingDone.store(false);

	for (auto value = 1; value <= 5; ++value)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds{ msecDistr(engine) });

		if (value == 4)
		{
			queue->Flush();
			continue;
		}

		queue->WriteCommand(ERQCommand::PRINT_VALUE);
		queue->WriteValue(valuesDistr(engine));
	}

	for (auto value = 10; value <= 20; ++value)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds{ msecDistr(engine) });

		if (value == 16)
		{
			queue->Flush();
			continue;
		}

		queue->WriteCommand(ERQCommand::PRINT_STRING);
		std::string str{ "This is " + std::to_string(value) + " test string" };
		queue->WriteValue(static_cast<uint32_t>(str.size()));
		queue->WriteData(str.c_str(), str.size());
	}

	queue->isSendingDone.store(true);
	std::cout << "All sended\n";
}

void CGame::ResetBufferTest()
{
	std::mt19937 engine{ std::random_device{}() };
	std::uniform_int_distribution<> msecDistr{ 10, 100 };
	std::uniform_int_distribution<uint32_t> valuesDistr{ 0, UINT32_MAX };

	std::cout << "Reset buffer test\n";
	std::cout << "-----------------\n\n";

	queue->isSendingDone.store(false);

	for (auto value = 1; value <= 5; ++value)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds{ msecDistr(engine) });

		if (value == 4)
		{
			queue->Reset();
		}
		queue->WriteCommand(ERQCommand::PRINT_VALUE);
		queue->WriteValue(valuesDistr(engine));
	}

	for (auto value = 10; value <= 20; ++value)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds{ msecDistr(engine) });

		if (value == 16)
		{
			queue->Reset();
		}

		queue->WriteCommand(ERQCommand::PRINT_STRING);
		std::string str{ "This is " + std::to_string(value) + " test string" };
		queue->WriteValue(static_cast<uint32_t>(str.size()));
		queue->WriteData(str.c_str(), str.size());
	}

	queue->isSendingDone.store(true);
	std::cout << "All sended\n";
}
