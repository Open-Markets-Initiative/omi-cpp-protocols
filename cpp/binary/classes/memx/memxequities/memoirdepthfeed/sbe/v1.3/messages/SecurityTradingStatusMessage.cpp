#include "SecurityTradingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

SecurityTradingStatusMessage::SecurityTradingStatusMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, SecurityTradingStatus security_trading_status, SecurityTradingStatusReason security_trading_status_reason)
  : timestamp_(timestamp), security_id_(security_id), security_trading_status_(security_trading_status), security_trading_status_reason_(security_trading_status_reason) {}

std::chrono::nanoseconds SecurityTradingStatusMessage::timestamp() const { return timestamp_; }
void SecurityTradingStatusMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t SecurityTradingStatusMessage::security_id() const { return security_id_; }
void SecurityTradingStatusMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

SecurityTradingStatus SecurityTradingStatusMessage::security_trading_status() const { return security_trading_status_; }
void SecurityTradingStatusMessage::set_security_trading_status(SecurityTradingStatus value) { security_trading_status_ = value; }

SecurityTradingStatusReason SecurityTradingStatusMessage::security_trading_status_reason() const { return security_trading_status_reason_; }
void SecurityTradingStatusMessage::set_security_trading_status_reason(SecurityTradingStatusReason value) { security_trading_status_reason_ = value; }

PayloadCode SecurityTradingStatusMessage::type() const { return message_type; }

std::string_view SecurityTradingStatusMessage::name() const { return "Security Trading Status Message"; }

std::size_t SecurityTradingStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityTradingStatusMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    security_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    security_trading_status_ = static_cast<SecurityTradingStatus>(wire::read_char(data + offset));
    offset += 1;

    security_trading_status_reason_ = static_cast<SecurityTradingStatusReason>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SecurityTradingStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityTradingStatusMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(security_id_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(security_trading_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(security_trading_status_reason_));
    offset += 1;

    return offset;
}

std::size_t SecurityTradingStatusMessage::encoded_size() const {
    return wire_size;
}

void SecurityTradingStatusMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> SecurityTradingStatusMessage::clone() const {
    return std::make_unique<SecurityTradingStatusMessage>(*this);
}

void SecurityTradingStatusMessage::print(std::ostream& out) const {
    out << "SecurityTradingStatusMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", security_trading_status=";
    out << security_trading_status_;
    out << ", security_trading_status_reason=";
    out << security_trading_status_reason_;
    out << '}';
}

bool SecurityTradingStatusMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const SecurityTradingStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityTradingStatusMessage::operator==(const SecurityTradingStatusMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_
        && security_trading_status_ == other.security_trading_status_
        && security_trading_status_reason_ == other.security_trading_status_reason_;
}

bool SecurityTradingStatusMessage::operator!=(const SecurityTradingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
