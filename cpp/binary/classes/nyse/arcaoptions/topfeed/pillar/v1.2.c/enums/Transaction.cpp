#include "Transaction.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(Transaction value) {
    switch (value) {
        case Transaction::OpeningTradeInSequence: return "Opening Trade In Sequence";
        case Transaction::OpeningTradeOutOfSequence: return "Opening Trade Out Of Sequence";
        case Transaction::InSequence: return "In Sequence";
        case Transaction::OutOfSequence: return "Out Of Sequence";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Transaction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
