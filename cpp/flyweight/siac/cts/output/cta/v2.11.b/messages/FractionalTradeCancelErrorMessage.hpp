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
#include "../structs/SaleCondition4.hpp"
#include "../common/Decimal.hpp"
#include "../enums/StopStockIndicator.hpp"
#include "../enums/TradeThroughExemptIndicator.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../structs/Timestamp2.hpp"
#include "../enums/CancelErrorAction.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/FinancialStatusIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Used to cancel or error CTA eligible securities, Local Issues or Bond information. Volume is
// represented as a fractional value
class FractionalTradeCancelErrorMessage {
  public:
    static constexpr const char* name = "FractionalTradeCancelErrorMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FractionalTradeCancelErrorMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FractionalTradeCancelErrorMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 161;
    static constexpr std::size_t fixed_size = 161;
    std::size_t encoded_size() const { return 161; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    SaleCondition4 sale_condition_4() const { return SaleCondition4{ bytes_.subspan(34) }; }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(38))), -6); }

    std::uint64_t fractional_trade_volume() const { return wire::read_u64_be(at(46)); }

    std::uint8_t sellers_sale_days() const { return wire::read_u8(at(54)); }

    StopStockIndicator stop_stock_indicator() const { return static_cast<StopStockIndicator>(wire::read_char(at(55))); }

    TradeThroughExemptIndicator trade_through_exempt_indicator() const { return static_cast<TradeThroughExemptIndicator>(wire::read_char(at(56))); }

    TradeReportingFacilityId trade_reporting_facility_id() const { return static_cast<TradeReportingFacilityId>(wire::read_char(at(57))); }

    std::int64_t original_participant_reference_number() const { return wire::read_i64_be(at(58)); }

    Timestamp2 timestamp_2() const { return Timestamp2{ bytes_.subspan(66) }; }

    CancelErrorAction cancel_error_action() const { return static_cast<CancelErrorAction>(wire::read_char(at(74))); }

    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const { return static_cast<ShortSaleRestrictionIndicator>(wire::read_char(at(75))); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(76))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(77))); }

    std::uint32_t consolidated_previous_close_price_date() const { return wire::read_u32_be(at(78)); }

    char consolidated_last_participant_id() const { return wire::read_char(at(82)); }

    Decimal consolidated_last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(83))), -6); }

    Decimal consolidated_high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(91))), -6); }

    Decimal consolidated_low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(99))), -6); }

    std::uint64_t consolidated_fractional_total_volume() const { return wire::read_u64_be(at(107)); }

    char consolidated_tick() const { return wire::read_char(at(115)); }

    std::uint32_t participant_previous_close_price_date() const { return wire::read_u32_be(at(116)); }

    Decimal participant_last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(120))), -6); }

    Decimal participant_high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(128))), -6); }

    Decimal participant_low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(136))), -6); }

    Decimal participant_open_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(144))), -6); }

    std::uint64_t participant_fractional_total_volume() const { return wire::read_u64_be(at(152)); }

    char participant_tick() const { return wire::read_char(at(160)); }

    void print(std::ostream& out) const {
        out << "FractionalTradeCancelErrorMessage{";
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
        out << ", sale_condition_4=";
        sale_condition_4().print(out);
        out << ", trade_price=";
        out << trade_price();
        out << ", fractional_trade_volume=";
        out << fractional_trade_volume();
        out << ", sellers_sale_days=";
        out << static_cast<int>(sellers_sale_days());
        out << ", stop_stock_indicator=";
        out << stop_stock_indicator();
        out << ", trade_through_exempt_indicator=";
        out << trade_through_exempt_indicator();
        out << ", trade_reporting_facility_id=";
        out << trade_reporting_facility_id();
        out << ", original_participant_reference_number=";
        out << original_participant_reference_number();
        out << ", timestamp_2=";
        timestamp_2().print(out);
        out << ", cancel_error_action=";
        out << cancel_error_action();
        out << ", short_sale_restriction_indicator=";
        out << short_sale_restriction_indicator();
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

inline std::ostream& operator<<(std::ostream& out, const FractionalTradeCancelErrorMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
