// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/TradeReportTermsMessage.cpp
#include "TradeReportTermsMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

TradeReportTermsMessage::TradeReportTermsMessage(const std::string& symbol, std::optional<std::uint32_t> trade_number, std::optional<Decimal> price, std::optional<std::uint32_t> volume, std::optional<std::uint16_t> buy_broker_number, std::optional<std::uint64_t> buy_order_id, std::optional<std::uint32_t> buy_display_volume, std::optional<std::uint16_t> sell_broker_number, std::optional<std::uint64_t> sell_order_id, std::optional<std::uint32_t> sell_display_volume, std::optional<std::uint32_t> trade_time_stamp, NonResident non_resident, SettlementTerms settlement_terms, std::optional<std::uint32_t> settlement_date, CrossType cross_type, std::optional<std::chrono::microseconds> trading_system_time_stamp)
  : symbol_(symbol), trade_number_(trade_number), price_(price), volume_(volume), buy_broker_number_(buy_broker_number), buy_order_id_(buy_order_id), buy_display_volume_(buy_display_volume), sell_broker_number_(sell_broker_number), sell_order_id_(sell_order_id), sell_display_volume_(sell_display_volume), trade_time_stamp_(trade_time_stamp), non_resident_(non_resident), settlement_terms_(settlement_terms), settlement_date_(settlement_date), cross_type_(cross_type), trading_system_time_stamp_(trading_system_time_stamp) {}

const std::string& TradeReportTermsMessage::symbol() const { return symbol_; }
std::string& TradeReportTermsMessage::symbol() { return symbol_; }
void TradeReportTermsMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::optional<std::uint32_t> TradeReportTermsMessage::trade_number() const { return trade_number_; }
void TradeReportTermsMessage::set_trade_number(std::optional<std::uint32_t> value) { trade_number_ = value; }

std::optional<Decimal> TradeReportTermsMessage::price() const { return price_; }
void TradeReportTermsMessage::set_price(std::optional<Decimal> value) { price_ = value; }

std::optional<std::uint32_t> TradeReportTermsMessage::volume() const { return volume_; }
void TradeReportTermsMessage::set_volume(std::optional<std::uint32_t> value) { volume_ = value; }

std::optional<std::uint16_t> TradeReportTermsMessage::buy_broker_number() const { return buy_broker_number_; }
void TradeReportTermsMessage::set_buy_broker_number(std::optional<std::uint16_t> value) { buy_broker_number_ = value; }

std::optional<std::uint64_t> TradeReportTermsMessage::buy_order_id() const { return buy_order_id_; }
void TradeReportTermsMessage::set_buy_order_id(std::optional<std::uint64_t> value) { buy_order_id_ = value; }

std::optional<std::uint32_t> TradeReportTermsMessage::buy_display_volume() const { return buy_display_volume_; }
void TradeReportTermsMessage::set_buy_display_volume(std::optional<std::uint32_t> value) { buy_display_volume_ = value; }

std::optional<std::uint16_t> TradeReportTermsMessage::sell_broker_number() const { return sell_broker_number_; }
void TradeReportTermsMessage::set_sell_broker_number(std::optional<std::uint16_t> value) { sell_broker_number_ = value; }

std::optional<std::uint64_t> TradeReportTermsMessage::sell_order_id() const { return sell_order_id_; }
void TradeReportTermsMessage::set_sell_order_id(std::optional<std::uint64_t> value) { sell_order_id_ = value; }

std::optional<std::uint32_t> TradeReportTermsMessage::sell_display_volume() const { return sell_display_volume_; }
void TradeReportTermsMessage::set_sell_display_volume(std::optional<std::uint32_t> value) { sell_display_volume_ = value; }

std::optional<std::uint32_t> TradeReportTermsMessage::trade_time_stamp() const { return trade_time_stamp_; }
void TradeReportTermsMessage::set_trade_time_stamp(std::optional<std::uint32_t> value) { trade_time_stamp_ = value; }

NonResident TradeReportTermsMessage::non_resident() const { return non_resident_; }
void TradeReportTermsMessage::set_non_resident(NonResident value) { non_resident_ = value; }

SettlementTerms TradeReportTermsMessage::settlement_terms() const { return settlement_terms_; }
void TradeReportTermsMessage::set_settlement_terms(SettlementTerms value) { settlement_terms_ = value; }

std::optional<std::uint32_t> TradeReportTermsMessage::settlement_date() const { return settlement_date_; }
void TradeReportTermsMessage::set_settlement_date(std::optional<std::uint32_t> value) { settlement_date_ = value; }

CrossType TradeReportTermsMessage::cross_type() const { return cross_type_; }
void TradeReportTermsMessage::set_cross_type(CrossType value) { cross_type_ = value; }

std::optional<std::chrono::microseconds> TradeReportTermsMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void TradeReportTermsMessage::set_trading_system_time_stamp(std::optional<std::chrono::microseconds> value) { trading_system_time_stamp_ = value; }

MessageCode TradeReportTermsMessage::type() const { return message_type; }

std::string_view TradeReportTermsMessage::name() const { return "Trade Report Terms Message"; }

std::size_t TradeReportTermsMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeReportTermsMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 9, ' ');
    offset += 9;

    trade_number_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    volume_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    buy_broker_number_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    buy_order_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    buy_display_volume_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    sell_broker_number_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    sell_order_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    sell_display_volume_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    trade_time_stamp_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    non_resident_ = static_cast<NonResident>(wire::read_char(data + offset));
    offset += 1;

    settlement_terms_ = static_cast<SettlementTerms>(wire::read_char(data + offset));
    offset += 1;

    settlement_date_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t TradeReportTermsMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeReportTermsMessage", wire_size, capacity);

    wire::write_text(data + offset, 9, ' ', symbol_);
    offset += 9;

    wire::write_u32_le(data + offset, trade_number_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, price_ ? static_cast<std::uint64_t>(price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, volume_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u16_le(data + offset, buy_broker_number_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_u64_le(data + offset, buy_order_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u32_le(data + offset, buy_display_volume_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u16_le(data + offset, sell_broker_number_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_u64_le(data + offset, sell_order_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u32_le(data + offset, sell_display_volume_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u32_le(data + offset, trade_time_stamp_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(non_resident_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(settlement_terms_));
    offset += 1;

    wire::write_u32_le(data + offset, settlement_date_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t TradeReportTermsMessage::encoded_size() const {
    return wire_size;
}

void TradeReportTermsMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeReportTermsMessage::clone() const {
    return std::make_unique<TradeReportTermsMessage>(*this);
}

void TradeReportTermsMessage::print(std::ostream& out) const {
    out << "TradeReportTermsMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", trade_number=";
    print::optional(out, trade_number_);
    out << ", price=";
    print::optional(out, price_);
    out << ", volume=";
    print::optional(out, volume_);
    out << ", buy_broker_number=";
    print::optional(out, buy_broker_number_);
    out << ", buy_order_id=";
    print::optional(out, buy_order_id_);
    out << ", buy_display_volume=";
    print::optional(out, buy_display_volume_);
    out << ", sell_broker_number=";
    print::optional(out, sell_broker_number_);
    out << ", sell_order_id=";
    print::optional(out, sell_order_id_);
    out << ", sell_display_volume=";
    print::optional(out, sell_display_volume_);
    out << ", trade_time_stamp=";
    print::optional(out, trade_time_stamp_);
    out << ", non_resident=";
    out << non_resident_;
    out << ", settlement_terms=";
    out << settlement_terms_;
    out << ", settlement_date=";
    print::optional(out, settlement_date_);
    out << ", cross_type=";
    out << cross_type_;
    out << ", trading_system_time_stamp=";
    print::optional_duration(out, trading_system_time_stamp_);
    out << '}';
}

bool TradeReportTermsMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeReportTermsMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeReportTermsMessage::operator==(const TradeReportTermsMessage& other) const {
    return symbol_ == other.symbol_
        && trade_number_ == other.trade_number_
        && price_ == other.price_
        && volume_ == other.volume_
        && buy_broker_number_ == other.buy_broker_number_
        && buy_order_id_ == other.buy_order_id_
        && buy_display_volume_ == other.buy_display_volume_
        && sell_broker_number_ == other.sell_broker_number_
        && sell_order_id_ == other.sell_order_id_
        && sell_display_volume_ == other.sell_display_volume_
        && trade_time_stamp_ == other.trade_time_stamp_
        && non_resident_ == other.non_resident_
        && settlement_terms_ == other.settlement_terms_
        && settlement_date_ == other.settlement_date_
        && cross_type_ == other.cross_type_
        && trading_system_time_stamp_ == other.trading_system_time_stamp_;
}

bool TradeReportTermsMessage::operator!=(const TradeReportTermsMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
