// Databento.MarketData.Normalized.Dbn.v3: enums/MatchAlgorithm.cpp
#include "MatchAlgorithm.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(MatchAlgorithm value) {
    switch (value) {
        case MatchAlgorithm::Undefined: return "Undefined";
        case MatchAlgorithm::Allocation: return "Allocation";
        case MatchAlgorithm::ProRata: return "Pro Rata";
        case MatchAlgorithm::Fifo: return "Fifo";
        case MatchAlgorithm::Configurable: return "Configurable";
        case MatchAlgorithm::ThresholdProRata: return "Threshold Pro Rata";
        case MatchAlgorithm::TimeProRata: return "Time Pro Rata";
        case MatchAlgorithm::ThresholdProRataLmm: return "Threshold Pro Rata Lmm";
        case MatchAlgorithm::FifoTopLmm: return "Fifo Top Lmm";
        case MatchAlgorithm::FifoLmm: return "Fifo Lmm";
        case MatchAlgorithm::InstitutionalPrioritization: return "Institutional Prioritization";
        case MatchAlgorithm::EurodollarFutures: return "Eurodollar Futures";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MatchAlgorithm value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
