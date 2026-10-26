#include "MinimumPriceIncrementIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(MinimumPriceIncrementIndicator value) {
    switch (value) {
        case MinimumPriceIncrementIndicator::PennyMpi001: return "Penny Mpi 0.01";
        case MinimumPriceIncrementIndicator::HalfPennyMpi0005: return "Half Penny Mpi 0.005";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MinimumPriceIncrementIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
