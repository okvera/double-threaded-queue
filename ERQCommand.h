#ifndef ERQCOMMAND_H
#define ERQCOMMAND_H

#include <ostream>
#include <string>

enum class ERQCommand : uint8_t
{
	INVALID = 0,
	PRINT_VALUE,
	PRINT_STRING,
};

static std::ostream &operator<<(std::ostream &stream, const ERQCommand &cmd)
{
	const std::string commandName[]={ "UNKNOWN", "PRINT_VALUE", "PRINT_STRING"};
	if (cmd > ERQCommand::PRINT_STRING)
	{
		throw "Wrong ERQCommand id";
	}
	return stream << commandName[static_cast<uint8_t>(cmd)];
}
#endif // !ERQCOMMAND_H