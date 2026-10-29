#include "InstrumentInfoMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

InstrumentInfoMessage::InstrumentInfoMessage(std::int64_t security_id, std::optional<Decimal> close_price, std::optional<Decimal> prev_close_price, std::optional<Decimal> upper_ckt_limit, std::optional<Decimal> lower_ckt_limit)
  : security_id_(security_id), close_price_(close_price), prev_close_price_(prev_close_price), upper_ckt_limit_(upper_ckt_limit), lower_ckt_limit_(lower_ckt_limit) {}

std::int64_t InstrumentInfoMessage::security_id() const { return security_id_; }
void InstrumentInfoMessage::set_security_id(std::int64_t value) { security_id_ = value; }

std::optional<Decimal> InstrumentInfoMessage::close_price() const { return close_price_; }
void InstrumentInfoMessage::set_close_price(std::optional<Decimal> value) { close_price_ = value; }

std::optional<Decimal> InstrumentInfoMessage::prev_close_price() const { return prev_close_price_; }
void InstrumentInfoMessage::set_prev_close_price(std::optional<Decimal> value) { prev_close_price_ = value; }

std::optional<Decimal> InstrumentInfoMessage::upper_ckt_limit() const { return upper_ckt_limit_; }
void InstrumentInfoMessage::set_upper_ckt_limit(std::optional<Decimal> value) { upper_ckt_limit_ = value; }

std::optional<Decimal> InstrumentInfoMessage::lower_ckt_limit() const { return lower_ckt_limit_; }
void InstrumentInfoMessage::set_lower_ckt_limit(std::optional<Decimal> value) { lower_ckt_limit_ = value; }

MessageCode InstrumentInfoMessage::type() const { return message_type; }

std::string_view InstrumentInfoMessage::name() const { return "Instrument Info Message"; }

std::size_t InstrumentInfoMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentInfoMessage", wire_size, length);

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    close_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -6);
    offset += 8;

    prev_close_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -6);
    offset += 8;

    upper_ckt_limit_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -6);
    offset += 8;

    lower_ckt_limit_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -6);
    offset += 8;

    return offset;
}

std::size_t InstrumentInfoMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentInfoMessage", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_i64_le(data + offset, close_price_ ? static_cast<std::int64_t>(close_price_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, prev_close_price_ ? static_cast<std::int64_t>(prev_close_price_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, upper_ckt_limit_ ? static_cast<std::int64_t>(upper_ckt_limit_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, lower_ckt_limit_ ? static_cast<std::int64_t>(lower_ckt_limit_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    return offset;
}

std::size_t InstrumentInfoMessage::encoded_size() const {
    return wire_size;
}

void InstrumentInfoMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> InstrumentInfoMessage::clone() const {
    return std::make_unique<InstrumentInfoMessage>(*this);
}

void InstrumentInfoMessage::print(std::ostream& out) const {
    out << "InstrumentInfoMessage{";
    out << "security_id=";
    out << security_id_;
    out << ", close_price=";
    print::optional(out, close_price_);
    out << ", prev_close_price=";
    print::optional(out, prev_close_price_);
    out << ", upper_ckt_limit=";
    print::optional(out, upper_ckt_limit_);
    out << ", lower_ckt_limit=";
    print::optional(out, lower_ckt_limit_);
    out << '}';
}

bool InstrumentInfoMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const InstrumentInfoMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool InstrumentInfoMessage::operator==(const InstrumentInfoMessage& other) const {
    return security_id_ == other.security_id_
        && close_price_ == other.close_price_
        && prev_close_price_ == other.prev_close_price_
        && upper_ckt_limit_ == other.upper_ckt_limit_
        && lower_ckt_limit_ == other.lower_ckt_limit_;
}

bool InstrumentInfoMessage::operator!=(const InstrumentInfoMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
