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

// Used to correct CTA eligible Equity, Local Issue or Bond information. To be descoped when
// Fractional Trade Volume publication is activated
class TradeCorrectionMessage {
  public:
    static constexpr const char* name = "TradeCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 168;
    static constexpr std::size_t fixed_size = 168;
    std::size_t encoded_size() const { return 168; }

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

    TradeReportingFacilityId trade_reporting_facility_id() const { return static_cast<TradeReportingFacilityId>(wire::read_char(at(54))); }

    Timestamp2 timestamp_2() const { return Timestamp2{ bytes_.subspan(55) }; }

    std::int64_t original_participant_reference_number() const { return wire::read_i64_be(at(63)); }

    std::string_view original_sale_condition() const { return view::text(at(71), 4, ' '); }

    Decimal original_trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(75))), -6); }

    std::uint32_t original_trade_volume() const { return wire::read_u32_be(at(83)); }

    std::uint8_t original_sellers_sale_days() const { return wire::read_u8(at(87)); }

    char original_stop_stock_indicator() const { return wire::read_char(at(88)); }

    char original_trade_through_exempt_indicator() const { return wire::read_char(at(89)); }

    char original_short_sale_restriction_indicator() const { return wire::read_char(at(90)); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(91))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(92))); }

    std::uint32_t consolidated_previous_close_price_date() const { return wire::read_u32_be(at(93)); }

    char consolidated_last_participant_id() const { return wire::read_char(at(97)); }

    Decimal consolidated_last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(98))), -6); }

    Decimal consolidated_high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(106))), -6); }

    Decimal consolidated_low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(114))), -6); }

    std::uint32_t consolidated_total_volume() const { return wire::read_u32_be(at(122)); }

    char consolidated_tick() const { return wire::read_char(at(126)); }

    std::uint32_t participant_previous_close_price_date() const { return wire::read_u32_be(at(127)); }

    Decimal participant_last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(131))), -6); }

    Decimal participant_high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(139))), -6); }

    Decimal participant_low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(147))), -6); }

    Decimal participant_open_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(155))), -6); }

    std::uint32_t participant_total_volume() const { return wire::read_u32_be(at(163)); }

    char participant_tick() const { return wire::read_char(at(167)); }

    void print(std::ostream& out) const {
        out << "TradeCorrectionMessage{";
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
        out << ", consolidated_total_volume=";
        out << consolidated_total_volume();
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
        out << ", participant_total_volume=";
        out << participant_total_volume();
        out << ", participant_tick=";
        print::character(out, participant_tick());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeCorrectionMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
