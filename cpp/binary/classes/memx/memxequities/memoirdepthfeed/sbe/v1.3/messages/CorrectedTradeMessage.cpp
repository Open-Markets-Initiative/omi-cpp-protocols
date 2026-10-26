#include "CorrectedTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

CorrectedTradeMessage::CorrectedTradeMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, std::uint64_t trade_id, std::uint32_t original_quantity, Decimal original_price, std::uint32_t corrected_quantity, Decimal corrected_price)
  : timestamp_(timestamp), security_id_(security_id), trade_id_(trade_id), original_quantity_(original_quantity), original_price_(original_price), corrected_quantity_(corrected_quantity), corrected_price_(corrected_price) {}

std::chrono::nanoseconds CorrectedTradeMessage::timestamp() const { return timestamp_; }
void CorrectedTradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t CorrectedTradeMessage::security_id() const { return security_id_; }
void CorrectedTradeMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

std::uint64_t CorrectedTradeMessage::trade_id() const { return trade_id_; }
void CorrectedTradeMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

std::uint32_t CorrectedTradeMessage::original_quantity() const { return original_quantity_; }
void CorrectedTradeMessage::set_original_quantity(std::uint32_t value) { original_quantity_ = value; }

Decimal CorrectedTradeMessage::original_price() const { return original_price_; }
void CorrectedTradeMessage::set_original_price(Decimal value) { original_price_ = value; }

std::uint32_t CorrectedTradeMessage::corrected_quantity() const { return corrected_quantity_; }
void CorrectedTradeMessage::set_corrected_quantity(std::uint32_t value) { corrected_quantity_ = value; }

Decimal CorrectedTradeMessage::corrected_price() const { return corrected_price_; }
void CorrectedTradeMessage::set_corrected_price(Decimal value) { corrected_price_ = value; }

PayloadCode CorrectedTradeMessage::type() const { return message_type; }

std::string_view CorrectedTradeMessage::name() const { return "Corrected Trade Message"; }

std::size_t CorrectedTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CorrectedTradeMessage", wire_size, length);

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

    corrected_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    corrected_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t CorrectedTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CorrectedTradeMessage", wire_size, capacity);

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

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(corrected_quantity_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(corrected_price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t CorrectedTradeMessage::encoded_size() const {
    return wire_size;
}

void CorrectedTradeMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> CorrectedTradeMessage::clone() const {
    return std::make_unique<CorrectedTradeMessage>(*this);
}

void CorrectedTradeMessage::print(std::ostream& out) const {
    out << "CorrectedTradeMessage{";
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
    out << ", corrected_quantity=";
    out << corrected_quantity_;
    out << ", corrected_price=";
    out << corrected_price_;
    out << '}';
}

bool CorrectedTradeMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const CorrectedTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CorrectedTradeMessage::operator==(const CorrectedTradeMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_
        && trade_id_ == other.trade_id_
        && original_quantity_ == other.original_quantity_
        && original_price_ == other.original_price_
        && corrected_quantity_ == other.corrected_quantity_
        && corrected_price_ == other.corrected_price_;
}

bool CorrectedTradeMessage::operator!=(const CorrectedTradeMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
