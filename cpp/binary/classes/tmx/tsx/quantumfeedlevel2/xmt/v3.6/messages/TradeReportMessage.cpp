// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeReportMessage.cpp
#include "TradeReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

TradeReportMessage::TradeReportMessage(const std::string& symbol, std::optional<std::uint32_t> trade_number, std::optional<Decimal> price, std::optional<std::uint32_t> volume, std::optional<std::uint16_t> buy_broker_number, std::optional<std::uint64_t> buy_order_id, std::optional<std::uint32_t> buy_display_volume, std::optional<std::uint16_t> sell_broker_number, std::optional<std::uint64_t> sell_order_id, std::optional<std::uint32_t> sell_display_volume, Bypass bypass, std::optional<std::uint32_t> trade_time_stamp, CrossType cross_type, std::optional<std::chrono::nanoseconds> trading_system_time_stamp, ListingMarket listing_market, ProductType product_type, std::optional<std::uint32_t> trade_date, IsMidOnly is_mid_only, IsDark is_dark, IsConditional is_conditional)
  : symbol_(symbol), trade_number_(trade_number), price_(price), volume_(volume), buy_broker_number_(buy_broker_number), buy_order_id_(buy_order_id), buy_display_volume_(buy_display_volume), sell_broker_number_(sell_broker_number), sell_order_id_(sell_order_id), sell_display_volume_(sell_display_volume), bypass_(bypass), trade_time_stamp_(trade_time_stamp), cross_type_(cross_type), trading_system_time_stamp_(trading_system_time_stamp), listing_market_(listing_market), product_type_(product_type), trade_date_(trade_date), is_mid_only_(is_mid_only), is_dark_(is_dark), is_conditional_(is_conditional) {}

const std::string& TradeReportMessage::symbol() const { return symbol_; }
std::string& TradeReportMessage::symbol() { return symbol_; }
void TradeReportMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::optional<std::uint32_t> TradeReportMessage::trade_number() const { return trade_number_; }
void TradeReportMessage::set_trade_number(std::optional<std::uint32_t> value) { trade_number_ = value; }

std::optional<Decimal> TradeReportMessage::price() const { return price_; }
void TradeReportMessage::set_price(std::optional<Decimal> value) { price_ = value; }

std::optional<std::uint32_t> TradeReportMessage::volume() const { return volume_; }
void TradeReportMessage::set_volume(std::optional<std::uint32_t> value) { volume_ = value; }

std::optional<std::uint16_t> TradeReportMessage::buy_broker_number() const { return buy_broker_number_; }
void TradeReportMessage::set_buy_broker_number(std::optional<std::uint16_t> value) { buy_broker_number_ = value; }

std::optional<std::uint64_t> TradeReportMessage::buy_order_id() const { return buy_order_id_; }
void TradeReportMessage::set_buy_order_id(std::optional<std::uint64_t> value) { buy_order_id_ = value; }

std::optional<std::uint32_t> TradeReportMessage::buy_display_volume() const { return buy_display_volume_; }
void TradeReportMessage::set_buy_display_volume(std::optional<std::uint32_t> value) { buy_display_volume_ = value; }

std::optional<std::uint16_t> TradeReportMessage::sell_broker_number() const { return sell_broker_number_; }
void TradeReportMessage::set_sell_broker_number(std::optional<std::uint16_t> value) { sell_broker_number_ = value; }

std::optional<std::uint64_t> TradeReportMessage::sell_order_id() const { return sell_order_id_; }
void TradeReportMessage::set_sell_order_id(std::optional<std::uint64_t> value) { sell_order_id_ = value; }

std::optional<std::uint32_t> TradeReportMessage::sell_display_volume() const { return sell_display_volume_; }
void TradeReportMessage::set_sell_display_volume(std::optional<std::uint32_t> value) { sell_display_volume_ = value; }

Bypass TradeReportMessage::bypass() const { return bypass_; }
void TradeReportMessage::set_bypass(Bypass value) { bypass_ = value; }

std::optional<std::uint32_t> TradeReportMessage::trade_time_stamp() const { return trade_time_stamp_; }
void TradeReportMessage::set_trade_time_stamp(std::optional<std::uint32_t> value) { trade_time_stamp_ = value; }

CrossType TradeReportMessage::cross_type() const { return cross_type_; }
void TradeReportMessage::set_cross_type(CrossType value) { cross_type_ = value; }

std::optional<std::chrono::nanoseconds> TradeReportMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void TradeReportMessage::set_trading_system_time_stamp(std::optional<std::chrono::nanoseconds> value) { trading_system_time_stamp_ = value; }

ListingMarket TradeReportMessage::listing_market() const { return listing_market_; }
void TradeReportMessage::set_listing_market(ListingMarket value) { listing_market_ = value; }

ProductType TradeReportMessage::product_type() const { return product_type_; }
void TradeReportMessage::set_product_type(ProductType value) { product_type_ = value; }

std::optional<std::uint32_t> TradeReportMessage::trade_date() const { return trade_date_; }
void TradeReportMessage::set_trade_date(std::optional<std::uint32_t> value) { trade_date_ = value; }

IsMidOnly TradeReportMessage::is_mid_only() const { return is_mid_only_; }
void TradeReportMessage::set_is_mid_only(IsMidOnly value) { is_mid_only_ = value; }

IsDark TradeReportMessage::is_dark() const { return is_dark_; }
void TradeReportMessage::set_is_dark(IsDark value) { is_dark_ = value; }

IsConditional TradeReportMessage::is_conditional() const { return is_conditional_; }
void TradeReportMessage::set_is_conditional(IsConditional value) { is_conditional_ = value; }

MessageCode TradeReportMessage::type() const { return message_type; }

std::string_view TradeReportMessage::name() const { return "Trade Report Message"; }

std::size_t TradeReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeReportMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

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

    bypass_ = static_cast<Bypass>(wire::read_char(data + offset));
    offset += 1;

    trade_time_stamp_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    listing_market_ = static_cast<ListingMarket>(wire::read_char(data + offset));
    offset += 1;

    product_type_ = static_cast<ProductType>(wire::read_char(data + offset));
    offset += 1;

    trade_date_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    is_mid_only_ = static_cast<IsMidOnly>(wire::read_char(data + offset));
    offset += 1;

    is_dark_ = static_cast<IsDark>(wire::read_char(data + offset));
    offset += 1;

    is_conditional_ = static_cast<IsConditional>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t TradeReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeReportMessage", wire_size, capacity);

    wire::write_text(data + offset, 12, ' ', symbol_);
    offset += 12;

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

    wire::write_char(data + offset, static_cast<char>(bypass_));
    offset += 1;

    wire::write_u32_le(data + offset, trade_time_stamp_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(listing_market_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(product_type_));
    offset += 1;

    wire::write_u32_le(data + offset, trade_date_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(is_mid_only_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(is_dark_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(is_conditional_));
    offset += 1;

    return offset;
}

std::size_t TradeReportMessage::encoded_size() const {
    return wire_size;
}

void TradeReportMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeReportMessage::clone() const {
    return std::make_unique<TradeReportMessage>(*this);
}

void TradeReportMessage::print(std::ostream& out) const {
    out << "TradeReportMessage{";
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
    out << ", bypass=";
    out << bypass_;
    out << ", trade_time_stamp=";
    print::optional(out, trade_time_stamp_);
    out << ", cross_type=";
    out << cross_type_;
    out << ", trading_system_time_stamp=";
    print::optional_duration(out, trading_system_time_stamp_);
    out << ", listing_market=";
    out << listing_market_;
    out << ", product_type=";
    out << product_type_;
    out << ", trade_date=";
    print::optional(out, trade_date_);
    out << ", is_mid_only=";
    out << is_mid_only_;
    out << ", is_dark=";
    out << is_dark_;
    out << ", is_conditional=";
    out << is_conditional_;
    out << '}';
}

bool TradeReportMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeReportMessage::operator==(const TradeReportMessage& other) const {
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
        && bypass_ == other.bypass_
        && trade_time_stamp_ == other.trade_time_stamp_
        && cross_type_ == other.cross_type_
        && trading_system_time_stamp_ == other.trading_system_time_stamp_
        && listing_market_ == other.listing_market_
        && product_type_ == other.product_type_
        && trade_date_ == other.trade_date_
        && is_mid_only_ == other.is_mid_only_
        && is_dark_ == other.is_dark_
        && is_conditional_ == other.is_conditional_;
}

bool TradeReportMessage::operator!=(const TradeReportMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
