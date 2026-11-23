// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/TestSymbol.cpp
#include "TestSymbol.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(TestSymbol value) {
    switch (value) {
        case TestSymbol::Yes: return "Yes";
        case TestSymbol::No: return "No";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TestSymbol value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
