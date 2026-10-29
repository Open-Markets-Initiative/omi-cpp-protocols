#include "SecurityDefinitionRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

SecurityDefinitionRequestMessage::SecurityDefinitionRequestMessage(const InboundBusinessHeader& inbound_business_header, std::uint64_t security_req_id, const std::string& sender_location, const std::string& entering_trader, const LegsGroups& legs_groups)
  : inbound_business_header_(inbound_business_header), security_req_id_(security_req_id), sender_location_(sender_location), entering_trader_(entering_trader), legs_groups_(legs_groups) {}

const InboundBusinessHeader& SecurityDefinitionRequestMessage::inbound_business_header() const { return inbound_business_header_; }
InboundBusinessHeader& SecurityDefinitionRequestMessage::inbound_business_header() { return inbound_business_header_; }
void SecurityDefinitionRequestMessage::set_inbound_business_header(const InboundBusinessHeader& value) { inbound_business_header_ = value; }

std::uint64_t SecurityDefinitionRequestMessage::security_req_id() const { return security_req_id_; }
void SecurityDefinitionRequestMessage::set_security_req_id(std::uint64_t value) { security_req_id_ = value; }

const std::string& SecurityDefinitionRequestMessage::sender_location() const { return sender_location_; }
std::string& SecurityDefinitionRequestMessage::sender_location() { return sender_location_; }
void SecurityDefinitionRequestMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& SecurityDefinitionRequestMessage::entering_trader() const { return entering_trader_; }
std::string& SecurityDefinitionRequestMessage::entering_trader() { return entering_trader_; }
void SecurityDefinitionRequestMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

const LegsGroups& SecurityDefinitionRequestMessage::legs_groups() const { return legs_groups_; }
LegsGroups& SecurityDefinitionRequestMessage::legs_groups() { return legs_groups_; }
void SecurityDefinitionRequestMessage::set_legs_groups(const LegsGroups& value) { legs_groups_ = value; }

MessageCode SecurityDefinitionRequestMessage::type() const { return message_type; }

std::string_view SecurityDefinitionRequestMessage::name() const { return "Security Definition Request Message"; }

std::size_t SecurityDefinitionRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += inbound_business_header_.decode(data + offset, length - offset);

    wire::require("SecurityDefinitionRequestMessage", offset + 8, length);
    security_req_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("SecurityDefinitionRequestMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("SecurityDefinitionRequestMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    offset += legs_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SecurityDefinitionRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityDefinitionRequestMessage", encoded_size(), capacity);

    offset += inbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_req_id_));
    offset += 8;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    offset += legs_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SecurityDefinitionRequestMessage::encoded_size() const {
    return inbound_business_header_.encoded_size() + 8 + 10 + 5 + legs_groups_.encoded_size();
}

void SecurityDefinitionRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecurityDefinitionRequestMessage::clone() const {
    return std::make_unique<SecurityDefinitionRequestMessage>(*this);
}

void SecurityDefinitionRequestMessage::print(std::ostream& out) const {
    out << "SecurityDefinitionRequestMessage{";
    out << "inbound_business_header=";
    inbound_business_header_.print(out);
    out << ", security_req_id=";
    out << security_req_id_;
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << ", legs_groups=";
    legs_groups_.print(out);
    out << '}';
}

bool SecurityDefinitionRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecurityDefinitionRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityDefinitionRequestMessage::operator==(const SecurityDefinitionRequestMessage& other) const {
    return inbound_business_header_ == other.inbound_business_header_
        && security_req_id_ == other.security_req_id_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_
        && legs_groups_ == other.legs_groups_;
}

bool SecurityDefinitionRequestMessage::operator!=(const SecurityDefinitionRequestMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
