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
#include "../structs/PriorDayCorrectedTrade.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../structs/PriorDayOriginalTrade.hpp"

namespace siac::cts::output::cta::v2_10 {

// Prior Day messages are used to report CTA eligible Equity, Local Issue or Bond trades,
// corrections, cancels or errors for transactions that occurred earlier than the current
// trading day and had not been reported
class PriorDayTradeCorrectionMessage {
  public:
    static constexpr const char* name = "PriorDayTradeCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PriorDayTradeCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PriorDayTradeCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 91;
    static constexpr std::size_t fixed_size = 91;
    std::size_t encoded_size() const { return 91; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    PriorDayCorrectedTrade prior_day_corrected_trade() const { return PriorDayCorrectedTrade{ bytes_.subspan(34) }; }

    TradeReportingFacilityId trade_reporting_facility_id() const { return static_cast<TradeReportingFacilityId>(wire::read_char(at(62))); }

    PriorDayOriginalTrade prior_day_original_trade() const { return PriorDayOriginalTrade{ bytes_.subspan(63) }; }

    void print(std::ostream& out) const {
        out << "PriorDayTradeCorrectionMessage{";
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
        out << ", prior_day_corrected_trade=";
        prior_day_corrected_trade().print(out);
        out << ", trade_reporting_facility_id=";
        out << trade_reporting_facility_id();
        out << ", prior_day_original_trade=";
        prior_day_original_trade().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PriorDayTradeCorrectionMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
