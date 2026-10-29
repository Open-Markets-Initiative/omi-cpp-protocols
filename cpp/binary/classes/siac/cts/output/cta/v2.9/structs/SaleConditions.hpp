#pragma once

#include <cstddef>
#include <ostream>

#include "../enums/ExtendedHoursOrSequenceType.hpp"
#include "../enums/SettlementType.hpp"
#include "../enums/SroTradeDetail.hpp"
#include "../enums/TradeThroughExemptReason.hpp"

namespace siac::cts::output::cta::v2_9 {

// Sale Conditions
class SaleConditions {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    SaleConditions() = default;
    SaleConditions(SettlementType settlement_type, TradeThroughExemptReason trade_through_exempt_reason, ExtendedHoursOrSequenceType extended_hours_or_sequence_type, SroTradeDetail sro_trade_detail);

    // Settlement Type: Category 1: Settlement Type
    SettlementType settlement_type() const;
    void set_settlement_type(SettlementType value);

    // Trade Through Exempt Reason: Category 2: Reason for Trade-Through Exemption / Other
    // Reason
    TradeThroughExemptReason trade_through_exempt_reason() const;
    void set_trade_through_exempt_reason(TradeThroughExemptReason value);

    // Extended Hours Or Sequence Type: Category 3: Extended Hours Or Sequence Type
    ExtendedHoursOrSequenceType extended_hours_or_sequence_type() const;
    void set_extended_hours_or_sequence_type(ExtendedHoursOrSequenceType value);

    // Sro Trade Detail: Category 4: SRO Trade Detail
    SroTradeDetail sro_trade_detail() const;
    void set_sro_trade_detail(SroTradeDetail value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SaleConditions& other) const;
    bool operator!=(const SaleConditions& other) const;

  private:
    SettlementType settlement_type_{};
    TradeThroughExemptReason trade_through_exempt_reason_{};
    ExtendedHoursOrSequenceType extended_hours_or_sequence_type_{};
    SroTradeDetail sro_trade_detail_{};
};

std::ostream& operator<<(std::ostream& out, const SaleConditions& value);

} // namespace siac::cts::output::cta::v2_9
