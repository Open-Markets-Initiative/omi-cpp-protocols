#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SettlementType.hpp"
#include "../enums/TradeThroughExemptReason.hpp"
#include "../enums/ExtendedHoursOrSequenceType.hpp"
#include "../enums/SroTradeDetail.hpp"

namespace siac::cts::output::cta::v2_9 {

// Sale Conditions
class SaleConditions {
  public:
    static constexpr const char* name = "SaleConditions";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SaleConditions(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SaleConditions has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    SettlementType settlement_type() const { return static_cast<SettlementType>(wire::read_char(at(0))); }

    TradeThroughExemptReason trade_through_exempt_reason() const { return static_cast<TradeThroughExemptReason>(wire::read_char(at(1))); }

    ExtendedHoursOrSequenceType extended_hours_or_sequence_type() const { return static_cast<ExtendedHoursOrSequenceType>(wire::read_char(at(2))); }

    SroTradeDetail sro_trade_detail() const { return static_cast<SroTradeDetail>(wire::read_char(at(3))); }

    void print(std::ostream& out) const {
        out << "SaleConditions{";
        out << "settlement_type=";
        out << settlement_type();
        out << ", trade_through_exempt_reason=";
        out << trade_through_exempt_reason();
        out << ", extended_hours_or_sequence_type=";
        out << extended_hours_or_sequence_type();
        out << ", sro_trade_detail=";
        out << sro_trade_detail();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SaleConditions& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_9
