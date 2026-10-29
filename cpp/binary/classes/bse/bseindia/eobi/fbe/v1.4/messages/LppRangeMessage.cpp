#include "LppRangeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

LppRangeMessage::LppRangeMessage(std::int64_t security_id, Decimal upper_exec_limit, Decimal lower_exec_limit)
  : security_id_(security_id), upper_exec_limit_(upper_exec_limit), lower_exec_limit_(lower_exec_limit) {}

std::int64_t LppRangeMessage::security_id() const { return security_id_; }
void LppRangeMessage::set_security_id(std::int64_t value) { security_id_ = value; }

Decimal LppRangeMessage::upper_exec_limit() const { return upper_exec_limit_; }
void LppRangeMessage::set_upper_exec_limit(Decimal value) { upper_exec_limit_ = value; }

Decimal LppRangeMessage::lower_exec_limit() const { return lower_exec_limit_; }
void LppRangeMessage::set_lower_exec_limit(Decimal value) { lower_exec_limit_ = value; }

MessageCode LppRangeMessage::type() const { return message_type; }

std::string_view LppRangeMessage::name() const { return "Lpp Range Message"; }

std::size_t LppRangeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LppRangeMessage", wire_size, length);

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    upper_exec_limit_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    lower_exec_limit_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t LppRangeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LppRangeMessage", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(upper_exec_limit_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(lower_exec_limit_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t LppRangeMessage::encoded_size() const {
    return wire_size;
}

void LppRangeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> LppRangeMessage::clone() const {
    return std::make_unique<LppRangeMessage>(*this);
}

void LppRangeMessage::print(std::ostream& out) const {
    out << "LppRangeMessage{";
    out << "security_id=";
    out << security_id_;
    out << ", upper_exec_limit=";
    out << upper_exec_limit_;
    out << ", lower_exec_limit=";
    out << lower_exec_limit_;
    out << '}';
}

bool LppRangeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const LppRangeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LppRangeMessage::operator==(const LppRangeMessage& other) const {
    return security_id_ == other.security_id_
        && upper_exec_limit_ == other.upper_exec_limit_
        && lower_exec_limit_ == other.lower_exec_limit_;
}

bool LppRangeMessage::operator!=(const LppRangeMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
