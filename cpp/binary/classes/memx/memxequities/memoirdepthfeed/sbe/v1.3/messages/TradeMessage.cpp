#include "TradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

TradeMessage::TradeMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, std::uint64_t trade_id, std::uint32_t quantity, Decimal price)
  : timestamp_(timestamp), security_id_(security_id), trade_id_(trade_id), quantity_(quantity), price_(price) {}

std::chrono::nanoseconds TradeMessage::timestamp() const { return timestamp_; }
void TradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t TradeMessage::security_id() const { return security_id_; }
void TradeMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

std::uint64_t TradeMessage::trade_id() const { return trade_id_; }
void TradeMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

std::uint32_t TradeMessage::quantity() const { return quantity_; }
void TradeMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

Decimal TradeMessage::price() const { return price_; }
void TradeMessage::set_price(Decimal value) { price_ = value; }

PayloadCode TradeMessage::type() const { return message_type; }

std::string_view TradeMessage::name() const { return "Trade Message"; }

std::size_t TradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    security_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t TradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(security_id_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t TradeMessage::encoded_size() const {
    return wire_size;
}

void TradeMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> TradeMessage::clone() const {
    return std::make_unique<TradeMessage>(*this);
}

void TradeMessage::print(std::ostream& out) const {
    out << "TradeMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", quantity=";
    out << quantity_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool TradeMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const TradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMessage::operator==(const TradeMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_
        && trade_id_ == other.trade_id_
        && quantity_ == other.quantity_
        && price_ == other.price_;
}

bool TradeMessage::operator!=(const TradeMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
