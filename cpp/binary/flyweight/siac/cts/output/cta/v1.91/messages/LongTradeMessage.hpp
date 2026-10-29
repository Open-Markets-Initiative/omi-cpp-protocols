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
#include "../structs/SaleConditions.hpp"
#include "../common/Decimal.hpp"
#include "../enums/StopStockIndicator.hpp"
#include "../enums/TradeThroughExemptIndicator.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../structs/Timestamp2.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/HeldTradeIndicator.hpp"
#include "../enums/ConsolidatedHighLowLastIndicator.hpp"
#include "../enums/ParticipantOpenHighLowLastIndicator.hpp"

namespace siac::cts::output::cta::v1_91 {

// The Long Trade message is used to report trade information for Cta eligible Equity, Local
// Issue or Bonds.
class LongTradeMessage {
  public:
    static constexpr const char* name = "LongTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LongTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LongTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 68;
    static constexpr std::size_t fixed_size = 68;
    std::size_t encoded_size() const { return 68; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    SaleConditions sale_conditions() const { return SaleConditions{ bytes_.subspan(34) }; }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(38))), -6); }

    std::uint32_t trade_volume() const { return wire::read_u32_be(at(46)); }

    std::uint8_t sellers_sale_days() const { return wire::read_u8(at(50)); }

    StopStockIndicator stop_stock_indicator() const { return static_cast<StopStockIndicator>(wire::read_char(at(51))); }

    TradeThroughExemptIndicator trade_through_exempt_indicator() const { return static_cast<TradeThroughExemptIndicator>(wire::read_char(at(52))); }

    TradeReportingFacilityId trade_reporting_facility_id() const { return static_cast<TradeReportingFacilityId>(wire::read_char(at(53))); }

    Timestamp2 timestamp_2() const { return Timestamp2{ bytes_.subspan(54) }; }

    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const { return static_cast<ShortSaleRestrictionIndicator>(wire::read_char(at(62))); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(63))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(64))); }

    HeldTradeIndicator held_trade_indicator() const { return static_cast<HeldTradeIndicator>(wire::read_char(at(65))); }

    ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator() const { return static_cast<ConsolidatedHighLowLastIndicator>(wire::read_char(at(66))); }

    ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator() const { return static_cast<ParticipantOpenHighLowLastIndicator>(wire::read_char(at(67))); }

    void print(std::ostream& out) const {
        out << "LongTradeMessage{";
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
        out << ", sale_conditions=";
        sale_conditions().print(out);
        out << ", trade_price=";
        out << trade_price();
        out << ", trade_volume=";
        out << trade_volume();
        out << ", sellers_sale_days=";
        out << static_cast<int>(sellers_sale_days());
        out << ", stop_stock_indicator=";
        out << stop_stock_indicator();
        out << ", trade_through_exempt_indicator=";
        out << trade_through_exempt_indicator();
        out << ", trade_reporting_facility_id=";
        out << trade_reporting_facility_id();
        out << ", timestamp_2=";
        timestamp_2().print(out);
        out << ", short_sale_restriction_indicator=";
        out << short_sale_restriction_indicator();
        out << ", primary_listing_market_participant_id=";
        out << primary_listing_market_participant_id();
        out << ", financial_status_indicator=";
        out << financial_status_indicator();
        out << ", held_trade_indicator=";
        out << held_trade_indicator();
        out << ", consolidated_high_low_last_indicator=";
        out << consolidated_high_low_last_indicator();
        out << ", participant_open_high_low_last_indicator=";
        out << participant_open_high_low_last_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LongTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v1_91
