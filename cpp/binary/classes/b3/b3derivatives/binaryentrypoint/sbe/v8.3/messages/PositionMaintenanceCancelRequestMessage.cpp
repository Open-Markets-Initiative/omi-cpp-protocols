#include "PositionMaintenanceCancelRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

PositionMaintenanceCancelRequestMessage::PositionMaintenanceCancelRequestMessage(const InboundBusinessHeader& inbound_business_header, std::uint64_t pos_req_id, std::uint64_t security_id, std::optional<std::uint64_t> orig_pos_req_ref_id, std::optional<std::uint64_t> pos_maint_rpt_ref_id, const std::string& sender_location, const std::string& entering_trader)
  : inbound_business_header_(inbound_business_header), pos_req_id_(pos_req_id), security_id_(security_id), orig_pos_req_ref_id_(orig_pos_req_ref_id), pos_maint_rpt_ref_id_(pos_maint_rpt_ref_id), sender_location_(sender_location), entering_trader_(entering_trader) {}

const InboundBusinessHeader& PositionMaintenanceCancelRequestMessage::inbound_business_header() const { return inbound_business_header_; }
InboundBusinessHeader& PositionMaintenanceCancelRequestMessage::inbound_business_header() { return inbound_business_header_; }
void PositionMaintenanceCancelRequestMessage::set_inbound_business_header(const InboundBusinessHeader& value) { inbound_business_header_ = value; }

std::uint64_t PositionMaintenanceCancelRequestMessage::pos_req_id() const { return pos_req_id_; }
void PositionMaintenanceCancelRequestMessage::set_pos_req_id(std::uint64_t value) { pos_req_id_ = value; }

std::uint64_t PositionMaintenanceCancelRequestMessage::security_id() const { return security_id_; }
void PositionMaintenanceCancelRequestMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::optional<std::uint64_t> PositionMaintenanceCancelRequestMessage::orig_pos_req_ref_id() const { return orig_pos_req_ref_id_; }
void PositionMaintenanceCancelRequestMessage::set_orig_pos_req_ref_id(std::optional<std::uint64_t> value) { orig_pos_req_ref_id_ = value; }

std::optional<std::uint64_t> PositionMaintenanceCancelRequestMessage::pos_maint_rpt_ref_id() const { return pos_maint_rpt_ref_id_; }
void PositionMaintenanceCancelRequestMessage::set_pos_maint_rpt_ref_id(std::optional<std::uint64_t> value) { pos_maint_rpt_ref_id_ = value; }

const std::string& PositionMaintenanceCancelRequestMessage::sender_location() const { return sender_location_; }
std::string& PositionMaintenanceCancelRequestMessage::sender_location() { return sender_location_; }
void PositionMaintenanceCancelRequestMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& PositionMaintenanceCancelRequestMessage::entering_trader() const { return entering_trader_; }
std::string& PositionMaintenanceCancelRequestMessage::entering_trader() { return entering_trader_; }
void PositionMaintenanceCancelRequestMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

MessageCode PositionMaintenanceCancelRequestMessage::type() const { return message_type; }

std::string_view PositionMaintenanceCancelRequestMessage::name() const { return "Position Maintenance Cancel Request Message"; }

std::size_t PositionMaintenanceCancelRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PositionMaintenanceCancelRequestMessage", wire_size, length);

    offset += inbound_business_header_.decode(data + offset, length - offset);

    pos_req_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    orig_pos_req_ref_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    pos_maint_rpt_ref_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    return offset;
}

std::size_t PositionMaintenanceCancelRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PositionMaintenanceCancelRequestMessage", wire_size, capacity);

    offset += inbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(pos_req_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, orig_pos_req_ref_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, pos_maint_rpt_ref_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    return offset;
}

std::size_t PositionMaintenanceCancelRequestMessage::encoded_size() const {
    return wire_size;
}

void PositionMaintenanceCancelRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PositionMaintenanceCancelRequestMessage::clone() const {
    return std::make_unique<PositionMaintenanceCancelRequestMessage>(*this);
}

void PositionMaintenanceCancelRequestMessage::print(std::ostream& out) const {
    out << "PositionMaintenanceCancelRequestMessage{";
    out << "inbound_business_header=";
    inbound_business_header_.print(out);
    out << ", pos_req_id=";
    out << pos_req_id_;
    out << ", security_id=";
    out << security_id_;
    out << ", orig_pos_req_ref_id=";
    print::optional(out, orig_pos_req_ref_id_);
    out << ", pos_maint_rpt_ref_id=";
    print::optional(out, pos_maint_rpt_ref_id_);
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << '}';
}

bool PositionMaintenanceCancelRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PositionMaintenanceCancelRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PositionMaintenanceCancelRequestMessage::operator==(const PositionMaintenanceCancelRequestMessage& other) const {
    return inbound_business_header_ == other.inbound_business_header_
        && pos_req_id_ == other.pos_req_id_
        && security_id_ == other.security_id_
        && orig_pos_req_ref_id_ == other.orig_pos_req_ref_id_
        && pos_maint_rpt_ref_id_ == other.pos_maint_rpt_ref_id_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_;
}

bool PositionMaintenanceCancelRequestMessage::operator!=(const PositionMaintenanceCancelRequestMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
