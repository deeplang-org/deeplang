#pragma once

#include "utils/error.h"

#include <cstdio>
#include <memory>
#include <string>

namespace dp {

enum class PrintHeader {
	Never,
	Once,
	Always,
};

std::string FormatErrorsToString(const Errors&,
																 const std::string& header                 = {},
																 PrintHeader        print_header           = PrintHeader::Never,
																 int                source_line_max_length = 80);

void FormatErrorsToFile(const Errors&,
												FILE*                                     = stderr,
												const std::string& header                 = {},
												PrintHeader        print_header           = PrintHeader::Never,
												int                source_line_max_length = 80);

} // namespace dp
