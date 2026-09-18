#include "ResultCode.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(ResultCode value) {
    switch (value) {
        case ResultCode::Accepted: return "Accepted";
        case ResultCode::OutOfService: return "Out Of Service";
        case ResultCode::IncorrectUserId: return "Incorrect User Id";
        case ResultCode::IncorrectSequenceNumber: return "Incorrect Sequence Number";
        case ResultCode::IncorrectPacketType: return "Incorrect Packet Type";
        case ResultCode::IncorrectMcgNumber: return "Incorrect Mcg Number";
        case ResultCode::OtherError: return "Other Error";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ResultCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
