#include "NegotiateRejectMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

NegotiateRejectMessage::NegotiateRejectMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds request_timestamp, std::optional<std::uint32_t> entering_firm_optional, NegotiationRejectCode negotiation_reject_code, const std::array<std::byte, 3>& offset_25_padding_3, std::optional<std::uint64_t> current_session_ver_id)
  : session_id_(session_id), session_ver_id_(session_ver_id), request_timestamp_(request_timestamp), entering_firm_optional_(entering_firm_optional), negotiation_reject_code_(negotiation_reject_code), offset_25_padding_3_(offset_25_padding_3), current_session_ver_id_(current_session_ver_id) {}

std::uint32_t NegotiateRejectMessage::session_id() const { return session_id_; }
void NegotiateRejectMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint64_t NegotiateRejectMessage::session_ver_id() const { return session_ver_id_; }
void NegotiateRejectMessage::set_session_ver_id(std::uint64_t value) { session_ver_id_ = value; }

std::chrono::nanoseconds NegotiateRejectMessage::request_timestamp() const { return request_timestamp_; }
void NegotiateRejectMessage::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

std::optional<std::uint32_t> NegotiateRejectMessage::entering_firm_optional() const { return entering_firm_optional_; }
void NegotiateRejectMessage::set_entering_firm_optional(std::optional<std::uint32_t> value) { entering_firm_optional_ = value; }

NegotiationRejectCode NegotiateRejectMessage::negotiation_reject_code() const { return negotiation_reject_code_; }
void NegotiateRejectMessage::set_negotiation_reject_code(NegotiationRejectCode value) { negotiation_reject_code_ = value; }

const std::array<std::byte, 3>& NegotiateRejectMessage::offset_25_padding_3() const { return offset_25_padding_3_; }
std::array<std::byte, 3>& NegotiateRejectMessage::offset_25_padding_3() { return offset_25_padding_3_; }
void NegotiateRejectMessage::set_offset_25_padding_3(const std::array<std::byte, 3>& value) { offset_25_padding_3_ = value; }

std::optional<std::uint64_t> NegotiateRejectMessage::current_session_ver_id() const { return current_session_ver_id_; }
void NegotiateRejectMessage::set_current_session_ver_id(std::optional<std::uint64_t> value) { current_session_ver_id_ = value; }

MessageCode NegotiateRejectMessage::type() const { return message_type; }

std::string_view NegotiateRejectMessage::name() const { return "Negotiate Reject Message"; }

std::size_t NegotiateRejectMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NegotiateRejectMessage", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    session_ver_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    request_timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    entering_firm_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    negotiation_reject_code_ = static_cast<NegotiationRejectCode>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_25_padding_3_.data(), 3);
    offset += 3;

    current_session_ver_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t NegotiateRejectMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NegotiateRejectMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(session_ver_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(request_timestamp_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, entering_firm_optional_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(negotiation_reject_code_));
    offset += 1;

    wire::write_bytes(data + offset, offset_25_padding_3_.data(), 3);
    offset += 3;

    wire::write_u64_le(data + offset, current_session_ver_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    return offset;
}

std::size_t NegotiateRejectMessage::encoded_size() const {
    return wire_size;
}

void NegotiateRejectMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NegotiateRejectMessage::clone() const {
    return std::make_unique<NegotiateRejectMessage>(*this);
}

void NegotiateRejectMessage::print(std::ostream& out) const {
    out << "NegotiateRejectMessage{";
    out << "session_id=";
    out << session_id_;
    out << ", session_ver_id=";
    out << session_ver_id_;
    out << ", request_timestamp=";
    out << request_timestamp_.count();
    out << ", entering_firm_optional=";
    print::optional(out, entering_firm_optional_);
    out << ", negotiation_reject_code=";
    out << negotiation_reject_code_;
    out << ", offset_25_padding_3=";
    print::hex(out, offset_25_padding_3_.data(), offset_25_padding_3_.size());
    out << ", current_session_ver_id=";
    print::optional(out, current_session_ver_id_);
    out << '}';
}

bool NegotiateRejectMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NegotiateRejectMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NegotiateRejectMessage::operator==(const NegotiateRejectMessage& other) const {
    return session_id_ == other.session_id_
        && session_ver_id_ == other.session_ver_id_
        && request_timestamp_ == other.request_timestamp_
        && entering_firm_optional_ == other.entering_firm_optional_
        && negotiation_reject_code_ == other.negotiation_reject_code_
        && offset_25_padding_3_ == other.offset_25_padding_3_
        && current_session_ver_id_ == other.current_session_ver_id_;
}

bool NegotiateRejectMessage::operator!=(const NegotiateRejectMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
