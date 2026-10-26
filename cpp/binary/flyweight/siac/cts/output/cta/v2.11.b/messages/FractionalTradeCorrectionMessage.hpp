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
#include "../enums/TradeReportingFacilityId.hpp"
#include "../structs/Timestamp2.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/FinancialStatusIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Used to correct CTA eligible Equity, Local Issue or Bond information. Volume is represented
// as a fractional value
class FractionalTradeCorrectionMessage {
  public:
    static constexpr const char* name = "FractionalTradeCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FractionalTradeCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FractionalTradeCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 184;
    static constexpr std::size_t fixed_size = 184;
    std::size_t encoded_size() const { return 184; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    std::string_view corrected_sale_condition() const { return view::text(at(34), 4, ' '); }

    Decimal corrected_trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(38))), -6); }

    Decimal corrected_fractional_trade_volume() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(46))), -6); }

    std::uint8_t corrected_sellers_sale_days() const { return wire::read_u8(at(54)); }

    char corrected_stop_stock_indicator() const { return wire::read_char(at(55)); }

    char corrected_trade_through_exempt_indicator() const { return wire::read_char(at(56)); }

    char corrected_short_sale_restriction_indicator() const { return wire::read_char(at(57)); }

    TradeReportingFacilityId trade_reporting_facility_id() const { return static_cast<TradeReportingFacilityId>(wire::read_char(at(58))); }

    Timestamp2 timestamp_2() const { return Timestamp2{ bytes_.subspan(59) }; }

    std::int64_t original_participant_reference_number() const { return wire::read_i64_be(at(67)); }

    std::string_view original_sale_condition() const { return view::text(at(75), 4, ' '); }

    Decimal original_trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(79))), -6); }

    Decimal original_fractional_trade_volume() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(87))), -6); }

    std::uint8_t original_sellers_sale_days() const { return wire::read_u8(at(95)); }

    char original_stop_stock_indicator() const { return wire::read_char(at(96)); }

    char original_trade_through_exempt_indicator() const { return wire::read_char(at(97)); }

    char original_short_sale_restriction_indicator() const { return wire::read_char(at(98)); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(99))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(100))); }

    std::uint32_t consolidated_previous_close_price_date() const { return wire::read_u32_be(at(101)); }

    char consolidated_last_participant_id() const { return wire::read_char(at(105)); }

    Decimal consolidated_last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(106))), -6); }

    Decimal consolidated_high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(114))), -6); }

    Decimal consolidated_low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(122))), -6); }

    Decimal consolidated_fractional_total_volume() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(130))), -6); }

    char consolidated_tick() const { return wire::read_char(at(138)); }

    std::uint32_t participant_previous_close_price_date() const { return wire::read_u32_be(at(139)); }

    Decimal participant_last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(143))), -6); }

    Decimal participant_high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(151))), -6); }

    Decimal participant_low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(159))), -6); }

    Decimal participant_open_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(167))), -6); }

    Decimal participant_fractional_total_volume() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(175))), -6); }

    char participant_tick() const { return wire::read_char(at(183)); }

    void print(std::ostream& out) const {
        out << "FractionalTradeCorrectionMessage{";
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
        out << ", corrected_fractional_trade_volume=";
        out << corrected_fractional_trade_volume();
        out << ", corrected_sellers_sale_days=";
        out << static_cast<int>(corrected_sellers_sale_days());
        out << ", corrected_stop_stock_indicator=";
        print::character(out, corrected_stop_stock_indicator());
        out << ", corrected_trade_through_exempt_indicator=";
        print::character(out, corrected_trade_through_exempt_indicator());
        out << ", corrected_short_sale_restriction_indicator=";
        print::character(out, corrected_short_sale_restriction_indicator());
        out << ", trade_reporting_facility_id=";
        out << trade_reporting_facility_id();
        out << ", timestamp_2=";
        timestamp_2().print(out);
        out << ", original_participant_reference_number=";
        out << original_participant_reference_number();
        out << ", original_sale_condition=";
        print::text(out, original_sale_condition());
        out << ", original_trade_price=";
        out << original_trade_price();
        out << ", original_fractional_trade_volume=";
        out << original_fractional_trade_volume();
        out << ", original_sellers_sale_days=";
        out << static_cast<int>(original_sellers_sale_days());
        out << ", original_stop_stock_indicator=";
        print::character(out, original_stop_stock_indicator());
        out << ", original_trade_through_exempt_indicator=";
        print::character(out, original_trade_through_exempt_indicator());
        out << ", original_short_sale_restriction_indicator=";
        print::character(out, original_short_sale_restriction_indicator());
        out << ", primary_listing_market_participant_id=";
        out << primary_listing_market_participant_id();
        out << ", financial_status_indicator=";
        out << financial_status_indicator();
        out << ", consolidated_previous_close_price_date=";
        out << consolidated_previous_close_price_date();
        out << ", consolidated_last_participant_id=";
        print::character(out, consolidated_last_participant_id());
        out << ", consolidated_last_price=";
        out << consolidated_last_price();
        out << ", consolidated_high_price=";
        out << consolidated_high_price();
        out << ", consolidated_low_price=";
        out << consolidated_low_price();
        out << ", consolidated_fractional_total_volume=";
        out << consolidated_fractional_total_volume();
        out << ", consolidated_tick=";
        print::character(out, consolidated_tick());
        out << ", participant_previous_close_price_date=";
        out << participant_previous_close_price_date();
        out << ", participant_last_price=";
        out << participant_last_price();
        out << ", participant_high_price=";
        out << participant_high_price();
        out << ", participant_low_price=";
        out << participant_low_price();
        out << ", participant_open_price=";
        out << participant_open_price();
        out << ", participant_fractional_total_volume=";
        out << participant_fractional_total_volume();
        out << ", participant_tick=";
        print::character(out, participant_tick());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FractionalTradeCorrectionMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
