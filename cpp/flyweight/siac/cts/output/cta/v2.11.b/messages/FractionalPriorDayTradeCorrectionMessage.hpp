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
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../structs/PriorDayTradeDateAndTime.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Used to correct a transaction originally reported on a trading day earlier than the current
// trading day. Volume is represented as a fractional value
class FractionalPriorDayTradeCorrectionMessage {
  public:
    static constexpr const char* name = "FractionalPriorDayTradeCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FractionalPriorDayTradeCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FractionalPriorDayTradeCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 67;
    static constexpr std::size_t fixed_size = 67;
    std::size_t encoded_size() const { return 67; }

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

    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const { return static_cast<ShortSaleRestrictionIndicator>(wire::read_char(at(57))); }

    TradeReportingFacilityId trade_reporting_facility_id() const { return static_cast<TradeReportingFacilityId>(wire::read_char(at(58))); }

    PriorDayTradeDateAndTime prior_day_trade_date_and_time() const { return PriorDayTradeDateAndTime{ bytes_.subspan(59) }; }

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
        out << ", short_sale_restriction_indicator=";
        out << short_sale_restriction_indicator();
        out << ", trade_reporting_facility_id=";
        out << trade_reporting_facility_id();
        out << ", prior_day_trade_date_and_time=";
        prior_day_trade_date_and_time().print(out);
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

} // namespace siac::cts::output::cta::v2_11_b
