#include "BrokenTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

BrokenTradeMessage::BrokenTradeMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, std::uint64_t trade_id, std::uint32_t original_quantity, Decimal original_price)
  : timestamp_(timestamp), security_id_(security_id), trade_id_(trade_id), original_quantity_(original_quantity), original_price_(original_price) {}

std::chrono::nanoseconds BrokenTradeMessage::timestamp() const { return timestamp_; }
void BrokenTradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t BrokenTradeMessage::security_id() const { return security_id_; }
void BrokenTradeMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

std::uint64_t BrokenTradeMessage::trade_id() const { return trade_id_; }
void BrokenTradeMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

std::uint32_t BrokenTradeMessage::original_quantity() const { return original_quantity_; }
void BrokenTradeMessage::set_original_quantity(std::uint32_t value) { original_quantity_ = value; }

Decimal BrokenTradeMessage::original_price() const { return original_price_; }
void BrokenTradeMessage::set_original_price(Decimal value) { original_price_ = value; }

PayloadCode BrokenTradeMessage::type() const { return message_type; }

std::string_view BrokenTradeMessage::name() const { return "Broken Trade Message"; }

std::size_t BrokenTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BrokenTradeMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    security_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    original_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    original_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t BrokenTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BrokenTradeMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(security_id_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_quantity_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(original_price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t BrokenTradeMessage::encoded_size() const {
    return wire_size;
}

void BrokenTradeMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> BrokenTradeMessage::clone() const {
    return std::make_unique<BrokenTradeMessage>(*this);
}

void BrokenTradeMessage::print(std::ostream& out) const {
    out << "BrokenTradeMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", original_quantity=";
    out << original_quantity_;
    out << ", original_price=";
    out << original_price_;
    out << '}';
}

bool BrokenTradeMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const BrokenTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool BrokenTradeMessage::operator==(const BrokenTradeMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_
        && trade_id_ == other.trade_id_
        && original_quantity_ == other.original_quantity_
        && original_price_ == other.original_price_;
}

bool BrokenTradeMessage::operator!=(const BrokenTradeMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
