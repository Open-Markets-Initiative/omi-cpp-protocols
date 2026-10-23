#include "ClearBookMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

ClearBookMessage::ClearBookMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id)
  : timestamp_(timestamp), security_id_(security_id) {}

std::chrono::nanoseconds ClearBookMessage::timestamp() const { return timestamp_; }
void ClearBookMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t ClearBookMessage::security_id() const { return security_id_; }
void ClearBookMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

PayloadCode ClearBookMessage::type() const { return message_type; }

std::string_view ClearBookMessage::name() const { return "Clear Book Message"; }

std::size_t ClearBookMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ClearBookMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    security_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t ClearBookMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClearBookMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(security_id_));
    offset += 2;

    return offset;
}

std::size_t ClearBookMessage::encoded_size() const {
    return wire_size;
}

void ClearBookMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> ClearBookMessage::clone() const {
    return std::make_unique<ClearBookMessage>(*this);
}

void ClearBookMessage::print(std::ostream& out) const {
    out << "ClearBookMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", security_id=";
    out << security_id_;
    out << '}';
}

bool ClearBookMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const ClearBookMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ClearBookMessage::operator==(const ClearBookMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_;
}

bool ClearBookMessage::operator!=(const ClearBookMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
