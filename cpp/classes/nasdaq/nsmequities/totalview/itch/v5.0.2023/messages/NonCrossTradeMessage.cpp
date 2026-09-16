#include "NonCrossTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

NonCrossTradeMessage::NonCrossTradeMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, BuySellIndicator buy_sell_indicator, std::uint32_t shares, const std::string& stock, Decimal price, std::uint64_t match_number)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number), buy_sell_indicator_(buy_sell_indicator), shares_(shares), stock_(stock), price_(price), match_number_(match_number) {}

std::uint16_t NonCrossTradeMessage::stock_locate() const { return stock_locate_; }
void NonCrossTradeMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t NonCrossTradeMessage::tracking_number() const { return tracking_number_; }
void NonCrossTradeMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds NonCrossTradeMessage::timestamp() const { return timestamp_; }
void NonCrossTradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t NonCrossTradeMessage::order_reference_number() const { return order_reference_number_; }
void NonCrossTradeMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

BuySellIndicator NonCrossTradeMessage::buy_sell_indicator() const { return buy_sell_indicator_; }
void NonCrossTradeMessage::set_buy_sell_indicator(BuySellIndicator value) { buy_sell_indicator_ = value; }

std::uint32_t NonCrossTradeMessage::shares() const { return shares_; }
void NonCrossTradeMessage::set_shares(std::uint32_t value) { shares_ = value; }

const std::string& NonCrossTradeMessage::stock() const { return stock_; }
std::string& NonCrossTradeMessage::stock() { return stock_; }
void NonCrossTradeMessage::set_stock(const std::string& value) { stock_ = value; }

Decimal NonCrossTradeMessage::price() const { return price_; }
void NonCrossTradeMessage::set_price(Decimal value) { price_ = value; }

std::uint64_t NonCrossTradeMessage::match_number() const { return match_number_; }
void NonCrossTradeMessage::set_match_number(std::uint64_t value) { match_number_ = value; }

MessageCode NonCrossTradeMessage::type() const { return message_type; }

std::string_view NonCrossTradeMessage::name() const { return "Non Cross Trade Message"; }

std::size_t NonCrossTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NonCrossTradeMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    buy_sell_indicator_ = static_cast<BuySellIndicator>(wire::read_char(data + offset));
    offset += 1;

    shares_ = wire::read_u32_be(data + offset);
    offset += 4;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    match_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t NonCrossTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NonCrossTradeMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(buy_sell_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(shares_));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_.mantissa()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(match_number_));
    offset += 8;

    return offset;
}

std::size_t NonCrossTradeMessage::encoded_size() const {
    return wire_size;
}

void NonCrossTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NonCrossTradeMessage::clone() const {
    return std::make_unique<NonCrossTradeMessage>(*this);
}

void NonCrossTradeMessage::print(std::ostream& out) const {
    out << "NonCrossTradeMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", buy_sell_indicator=";
    out << buy_sell_indicator_;
    out << ", shares=";
    out << shares_;
    out << ", stock=";
    print::text(out, stock_);
    out << ", price=";
    out << price_;
    out << ", match_number=";
    out << match_number_;
    out << '}';
}

bool NonCrossTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NonCrossTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NonCrossTradeMessage::operator==(const NonCrossTradeMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_
        && buy_sell_indicator_ == other.buy_sell_indicator_
        && shares_ == other.shares_
        && stock_ == other.stock_
        && price_ == other.price_
        && match_number_ == other.match_number_;
}

bool NonCrossTradeMessage::operator!=(const NonCrossTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
