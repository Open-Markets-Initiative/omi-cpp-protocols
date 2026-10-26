#include "Test.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(Test value) {
    switch (value) {
        case Test::NotATestSymbol: return "Not A Test Symbol";
        case Test::TestSymbol: return "Test Symbol";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Test value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
