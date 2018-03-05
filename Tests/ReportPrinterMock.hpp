#include <gmock/gmock.h>
#include "../reportPrinter/ReportPrinter.hpp"
#include <map>
#include <string>

namespace printer
{
class ReportPrinterMock : public ReportPrinter
{
public:
	MOCK_METHOD2(print, void(std::map<std::string, double>, double));
};
}
