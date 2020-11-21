#include "utils/error-formatter.h"

namespace dp {

namespace {

std::string FormatError(const Error& error,
												int          source_line_max_length,
												int          indent) {
	std::string indent_str(indent, ' ');
	std::string result = indent_str;

	//result += color.MaybeBoldCode();

	const Location& loc = error.loc;
//	if (!loc.fileName.empty()) {
//		result += loc.fileName;
//		result += ":";
//	}

	result += StringPrintf("%d:%d: ", loc.range.start, loc.range.start.character);

	//result += color.MaybeRedCode();
	result += GetErrorLevelName(error.level);
	result += ": ";
	//result += color.MaybeDefaultCode();

	result += error.message;
	result += '\n';

	//LexerSourceLineFinder::SourceLine source_line;
	//if (line_finder) {
	//  line_finder->GetSourceLine(loc, source_line_max_length, &source_line);
	//}

	//if (!source_line.line.empty()) {
	// result += indent_str;
	//result += source_line.line;
	// result += '\n';
	// result += indent_str;

	//size_t num_spaces = (loc.firstColumn - 1) - source_line.column_offset;
	//size_t num_carets = loc.lastColumn - loc.firstColumn;
	//num_carets        = std::min(num_carets, source_line.line.size() - num_spaces);
	//num_carets        = std::max<size_t>(num_carets, 1);
	//result.append(num_spaces, ' ');
	//result += color.MaybeBoldCode();
	//result += color.MaybeGreenCode();
	//result.append(num_carets, '^');
	//result += color.MaybeDefaultCode();
	// result += '\n';
	//}

	return result;
}

} // namespace

std::string FormatErrorsToString(const Errors&      errors,
																 const std::string& header,
																 PrintHeader        print_header,
																 int                source_line_max_length) {
	std::string result;
	for (const auto& error : errors) {
		if (!header.empty()) {
			switch (print_header) {
			case PrintHeader::Never:
				break;
			case PrintHeader::Once:
				print_header = PrintHeader::Never;
				// Fallthrough.
			case PrintHeader::Always:
				result += header;
				result += ":\n";
				break;
			}
		}

		int indent = header.empty() ? 0 : 2;

		result += FormatError(error, source_line_max_length, indent);
	}
	return result;
}

void FormatErrorsToFile(const Errors&      errors,
												FILE*              file,
												const std::string& header,
												PrintHeader        print_header,
												int                source_line_max_length) {
	//Color       color(file);
	std::string s = FormatErrorsToString(errors, header,
																			 print_header, source_line_max_length);
	fwrite(s.data(), 1, s.size(), file);
}

} // namespace dp
