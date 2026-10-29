#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../enums/InstrumentType.hpp"
#include "../structs/FractionalPriorDayCorrectedTrade.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../structs/FractionalPriorDayOriginalTrade.hpp"

namespace siac::cts::output::cta::v2_10 {

// Prior Day messages are used to report CTA eligible Equity, Local Issue or Bond trades,
// corrections, cancels or errors for transactions that occurred earlier than the current
// trading day and had not been reported
class FractionalPriorDayTradeCorrectionMessage {
  public:
    static constexpr const char* name = "FractionalPriorDayTradeCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FractionalPriorDayTradeCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FractionalPriorDayTradeCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 99;
    static constexpr std::size_t fixed_size = 99;
    std::size_t encoded_size() const { return 99; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    FractionalPriorDayCorrectedTrade fractional_prior_day_corrected_trade() const { return FractionalPriorDayCorrectedTrade{ bytes_.subspan(34) }; }

    TradeReportingFacilityId trade_reporting_facility_id() const { return static_cast<TradeReportingFacilityId>(wire::read_char(at(66))); }

    FractionalPriorDayOriginalTrade fractional_prior_day_original_trade() const { return FractionalPriorDayOriginalTrade{ bytes_.subspan(67) }; }

    void print(std::ostream& out) const {
        out << "FractionalPriorDayTradeCorrectionMessage{";
        out << "participant_id=";
        out << participant_id();
        out << ", timestamp_1=";
        timestamp_1().print(out);
        out << ", message_id=";
        out << static_cast<int>(message_id());
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << ", security_symbol=";
        print::text(out, security_symbol());
        out << ", instrument_type=";
        out << instrument_type();
        out << ", fractional_prior_day_corrected_trade=";
        fractional_prior_day_corrected_trade().print(out);
        out << ", trade_reporting_facility_id=";
        out << trade_reporting_facility_id();
        out << ", fractional_prior_day_original_trade=";
        fractional_prior_day_original_trade().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FractionalPriorDayTradeCorrectionMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
