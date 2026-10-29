#include "SecurityDefinitionResponseMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

SecurityDefinitionResponseMessage::SecurityDefinitionResponseMessage(const OutboundBusinessHeader& outbound_business_header, const std::array<std::byte, 2>& offset_18_padding_2, std::uint64_t security_req_id, std::optional<std::uint64_t> security_id_optional, SecurityResponseType security_response_type, const std::string& security_strategy_type, const std::string& symbol, std::uint64_t security_response_id, const std::string& sender_location, const std::string& entering_trader)
  : outbound_business_header_(outbound_business_header), offset_18_padding_2_(offset_18_padding_2), security_req_id_(security_req_id), security_id_optional_(security_id_optional), security_response_type_(security_response_type), security_strategy_type_(security_strategy_type), symbol_(symbol), security_response_id_(security_response_id), sender_location_(sender_location), entering_trader_(entering_trader) {}

const OutboundBusinessHeader& SecurityDefinitionResponseMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& SecurityDefinitionResponseMessage::outbound_business_header() { return outbound_business_header_; }
void SecurityDefinitionResponseMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

const std::array<std::byte, 2>& SecurityDefinitionResponseMessage::offset_18_padding_2() const { return offset_18_padding_2_; }
std::array<std::byte, 2>& SecurityDefinitionResponseMessage::offset_18_padding_2() { return offset_18_padding_2_; }
void SecurityDefinitionResponseMessage::set_offset_18_padding_2(const std::array<std::byte, 2>& value) { offset_18_padding_2_ = value; }

std::uint64_t SecurityDefinitionResponseMessage::security_req_id() const { return security_req_id_; }
void SecurityDefinitionResponseMessage::set_security_req_id(std::uint64_t value) { security_req_id_ = value; }

std::optional<std::uint64_t> SecurityDefinitionResponseMessage::security_id_optional() const { return security_id_optional_; }
void SecurityDefinitionResponseMessage::set_security_id_optional(std::optional<std::uint64_t> value) { security_id_optional_ = value; }

SecurityResponseType SecurityDefinitionResponseMessage::security_response_type() const { return security_response_type_; }
void SecurityDefinitionResponseMessage::set_security_response_type(SecurityResponseType value) { security_response_type_ = value; }

const std::string& SecurityDefinitionResponseMessage::security_strategy_type() const { return security_strategy_type_; }
std::string& SecurityDefinitionResponseMessage::security_strategy_type() { return security_strategy_type_; }
void SecurityDefinitionResponseMessage::set_security_strategy_type(const std::string& value) { security_strategy_type_ = value; }

const std::string& SecurityDefinitionResponseMessage::symbol() const { return symbol_; }
std::string& SecurityDefinitionResponseMessage::symbol() { return symbol_; }
void SecurityDefinitionResponseMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint64_t SecurityDefinitionResponseMessage::security_response_id() const { return security_response_id_; }
void SecurityDefinitionResponseMessage::set_security_response_id(std::uint64_t value) { security_response_id_ = value; }

const std::string& SecurityDefinitionResponseMessage::sender_location() const { return sender_location_; }
std::string& SecurityDefinitionResponseMessage::sender_location() { return sender_location_; }
void SecurityDefinitionResponseMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& SecurityDefinitionResponseMessage::entering_trader() const { return entering_trader_; }
std::string& SecurityDefinitionResponseMessage::entering_trader() { return entering_trader_; }
void SecurityDefinitionResponseMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

MessageCode SecurityDefinitionResponseMessage::type() const { return message_type; }

std::string_view SecurityDefinitionResponseMessage::name() const { return "Security Definition Response Message"; }

std::size_t SecurityDefinitionResponseMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityDefinitionResponseMessage", wire_size, length);

    offset += outbound_business_header_.decode(data + offset, length - offset);

    wire::read_bytes(data + offset, offset_18_padding_2_.data(), 2);
    offset += 2;

    security_req_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    security_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    security_response_type_ = static_cast<SecurityResponseType>(wire::read_u8(data + offset));
    offset += 1;

    security_strategy_type_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    security_response_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    return offset;
}

std::size_t SecurityDefinitionResponseMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityDefinitionResponseMessage", wire_size, capacity);

    offset += outbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, offset_18_padding_2_.data(), 2);
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_req_id_));
    offset += 8;

    wire::write_u64_le(data + offset, security_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_response_type_));
    offset += 1;

    wire::write_text(data + offset, 3, '\0', security_strategy_type_);
    offset += 3;

    wire::write_text(data + offset, 20, '\0', symbol_);
    offset += 20;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_response_id_));
    offset += 8;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    return offset;
}

std::size_t SecurityDefinitionResponseMessage::encoded_size() const {
    return wire_size;
}

void SecurityDefinitionResponseMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecurityDefinitionResponseMessage::clone() const {
    return std::make_unique<SecurityDefinitionResponseMessage>(*this);
}

void SecurityDefinitionResponseMessage::print(std::ostream& out) const {
    out << "SecurityDefinitionResponseMessage{";
    out << "outbound_business_header=";
    outbound_business_header_.print(out);
    out << ", offset_18_padding_2=";
    print::hex(out, offset_18_padding_2_.data(), offset_18_padding_2_.size());
    out << ", security_req_id=";
    out << security_req_id_;
    out << ", security_id_optional=";
    print::optional(out, security_id_optional_);
    out << ", security_response_type=";
    out << security_response_type_;
    out << ", security_strategy_type=";
    print::text(out, security_strategy_type_);
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", security_response_id=";
    out << security_response_id_;
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << '}';
}

bool SecurityDefinitionResponseMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecurityDefinitionResponseMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityDefinitionResponseMessage::operator==(const SecurityDefinitionResponseMessage& other) const {
    return outbound_business_header_ == other.outbound_business_header_
        && offset_18_padding_2_ == other.offset_18_padding_2_
        && security_req_id_ == other.security_req_id_
        && security_id_optional_ == other.security_id_optional_
        && security_response_type_ == other.security_response_type_
        && security_strategy_type_ == other.security_strategy_type_
        && symbol_ == other.symbol_
        && security_response_id_ == other.security_response_id_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_;
}

bool SecurityDefinitionResponseMessage::operator!=(const SecurityDefinitionResponseMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
