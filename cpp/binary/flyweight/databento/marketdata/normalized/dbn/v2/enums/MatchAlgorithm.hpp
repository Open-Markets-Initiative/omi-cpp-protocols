// Databento.MarketData.Normalized.Dbn.v2: enums/MatchAlgorithm.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v2 {

// The matching algorithm used for the instrument, typically FIFO
enum class MatchAlgorithm : char {
    Undefined = ' ',                   // Undefined
    Allocation = 'A',                  // Allocation
    ProRata = 'C',                     // Pro Rata
    Fifo = 'F',                        // Fifo
    Configurable = 'K',                // Configurable
    ThresholdProRata = 'O',            // Threshold Pro Rata
    TimeProRata = 'P',                 // Time Pro Rata
    ThresholdProRataLmm = 'Q',         // Threshold Pro Rata Lmm
    FifoTopLmm = 'S',                  // Fifo Top Lmm
    FifoLmm = 'T',                     // Fifo Lmm
    InstitutionalPrioritization = 'V', // Institutional Prioritization
    EurodollarFutures = 'Y',           // Eurodollar Futures
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MatchAlgorithm value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MatchAlgorithm value);

} // namespace databento::marketdata::normalized::dbn::v2
