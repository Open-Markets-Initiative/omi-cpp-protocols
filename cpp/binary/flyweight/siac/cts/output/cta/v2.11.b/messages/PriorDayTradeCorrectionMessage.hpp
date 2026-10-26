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
#include "../common/Decimal.hpp"
#include "../structs/CorrectedPriorDayTradeDateAndTime.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../structs/OriginalPriorDayTradeDateAndTime.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Used to correct a transaction originally reported on a trading day earlier than the current
// trading day. To be descoped when Fractional Trade Volume publication is activated
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

    std::string_view corrected_sale_condition() const { return view::text(at(34), 4, ' '); }

    Decimal corrected_trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(38))), -6); }

    std::uint32_t corrected_trade_volume() const { return wire::read_u32_be(at(46)); }

    std::uint8_t corrected_sellers_sale_days() const { return wire::read_u8(at(50)); }

    char corrected_stop_stock_indicator() const { return wire::read_char(at(51)); }

    char corrected_trade_through_exempt_indicator() const { return wire::read_char(at(52)); }

    char corrected_short_sale_restriction_indicator() const { return wire::read_char(at(53)); }

    CorrectedPriorDayTradeDateAndTime corrected_prior_day_trade_date_and_time() const { return CorrectedPriorDayTradeDateAndTime{ bytes_.subspan(54) }; }

    TradeReportingFacilityId trade_reporting_facility_id() const { return static_cast<TradeReportingFacilityId>(wire::read_char(at(62))); }

    std::string_view original_sale_condition() const { return view::text(at(63), 4, ' '); }

    Decimal original_trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(67))), -6); }

    std::uint32_t original_trade_volume() const { return wire::read_u32_be(at(75)); }

    std::uint8_t original_sellers_sale_days() const { return wire::read_u8(at(79)); }

    char original_stop_stock_indicator() const { return wire::read_char(at(80)); }

    char original_trade_through_exempt_indicator() const { return wire::read_char(at(81)); }

    char original_short_sale_restriction_indicator() const { return wire::read_char(at(82)); }

    OriginalPriorDayTradeDateAndTime original_prior_day_trade_date_and_time() const { return OriginalPriorDayTradeDateAndTime{ bytes_.subspan(83) }; }

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
        out << ", corrected_sale_condition=";
        print::text(out, corrected_sale_condition());
        out << ", corrected_trade_price=";
        out << corrected_trade_price();
        out << ", corrected_trade_volume=";
        out << corrected_trade_volume();
        out << ", corrected_sellers_sale_days=";
        out << static_cast<int>(corrected_sellers_sale_days());
        out << ", corrected_stop_stock_indicator=";
        print::character(out, corrected_stop_stock_indicator());
        out << ", corrected_trade_through_exempt_indicator=";
        print::character(out, corrected_trade_through_exempt_indicator());
        out << ", corrected_short_sale_restriction_indicator=";
        print::character(out, corrected_short_sale_restriction_indicator());
        out << ", corrected_prior_day_trade_date_and_time=";
        corrected_prior_day_trade_date_and_time().print(out);
        out << ", trade_reporting_facility_id=";
        out << trade_reporting_facility_id();
        out << ", original_sale_condition=";
        print::text(out, original_sale_condition());
        out << ", original_trade_price=";
        out << original_trade_price();
        out << ", original_trade_volume=";
        out << original_trade_volume();
        out << ", original_sellers_sale_days=";
        out << static_cast<int>(original_sellers_sale_days());
        out << ", original_stop_stock_indicator=";
        print::character(out, original_stop_stock_indicator());
        out << ", original_trade_through_exempt_indicator=";
        print::character(out, original_trade_through_exempt_indicator());
        out << ", original_short_sale_restriction_indicator=";
        print::character(out, original_short_sale_restriction_indicator());
        out << ", original_prior_day_trade_date_and_time=";
        original_prior_day_trade_date_and_time().print(out);
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

} // namespace siac::cts::output::cta::v2_11_b
