#include "EstablishRejectMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

EstablishRejectMessage::EstablishRejectMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds request_timestamp, EstablishmentRejectCode establishment_reject_code, const std::array<std::byte, 1>& offset_21_padding_1, std::optional<std::uint32_t> last_incoming_seq_no_optional)
  : session_id_(session_id), session_ver_id_(session_ver_id), request_timestamp_(request_timestamp), establishment_reject_code_(establishment_reject_code), offset_21_padding_1_(offset_21_padding_1), last_incoming_seq_no_optional_(last_incoming_seq_no_optional) {}

std::uint32_t EstablishRejectMessage::session_id() const { return session_id_; }
void EstablishRejectMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint64_t EstablishRejectMessage::session_ver_id() const { return session_ver_id_; }
void EstablishRejectMessage::set_session_ver_id(std::uint64_t value) { session_ver_id_ = value; }

std::chrono::nanoseconds EstablishRejectMessage::request_timestamp() const { return request_timestamp_; }
void EstablishRejectMessage::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

EstablishmentRejectCode EstablishRejectMessage::establishment_reject_code() const { return establishment_reject_code_; }
void EstablishRejectMessage::set_establishment_reject_code(EstablishmentRejectCode value) { establishment_reject_code_ = value; }

const std::array<std::byte, 1>& EstablishRejectMessage::offset_21_padding_1() const { return offset_21_padding_1_; }
std::array<std::byte, 1>& EstablishRejectMessage::offset_21_padding_1() { return offset_21_padding_1_; }
void EstablishRejectMessage::set_offset_21_padding_1(const std::array<std::byte, 1>& value) { offset_21_padding_1_ = value; }

std::optional<std::uint32_t> EstablishRejectMessage::last_incoming_seq_no_optional() const { return last_incoming_seq_no_optional_; }
void EstablishRejectMessage::set_last_incoming_seq_no_optional(std::optional<std::uint32_t> value) { last_incoming_seq_no_optional_ = value; }

MessageCode EstablishRejectMessage::type() const { return message_type; }

std::string_view EstablishRejectMessage::name() const { return "Establish Reject Message"; }

std::size_t EstablishRejectMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EstablishRejectMessage", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    session_ver_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    request_timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    establishment_reject_code_ = static_cast<EstablishmentRejectCode>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_21_padding_1_.data(), 1);
    offset += 1;

    last_incoming_seq_no_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t EstablishRejectMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EstablishRejectMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(session_ver_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(request_timestamp_.count()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(establishment_reject_code_));
    offset += 1;

    wire::write_bytes(data + offset, offset_21_padding_1_.data(), 1);
    offset += 1;

    wire::write_u32_le(data + offset, last_incoming_seq_no_optional_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t EstablishRejectMessage::encoded_size() const {
    return wire_size;
}

void EstablishRejectMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EstablishRejectMessage::clone() const {
    return std::make_unique<EstablishRejectMessage>(*this);
}

void EstablishRejectMessage::print(std::ostream& out) const {
    out << "EstablishRejectMessage{";
    out << "session_id=";
    out << session_id_;
    out << ", session_ver_id=";
    out << session_ver_id_;
    out << ", request_timestamp=";
    out << request_timestamp_.count();
    out << ", establishment_reject_code=";
    out << establishment_reject_code_;
    out << ", offset_21_padding_1=";
    print::hex(out, offset_21_padding_1_.data(), offset_21_padding_1_.size());
    out << ", last_incoming_seq_no_optional=";
    print::optional(out, last_incoming_seq_no_optional_);
    out << '}';
}

bool EstablishRejectMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EstablishRejectMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EstablishRejectMessage::operator==(const EstablishRejectMessage& other) const {
    return session_id_ == other.session_id_
        && session_ver_id_ == other.session_ver_id_
        && request_timestamp_ == other.request_timestamp_
        && establishment_reject_code_ == other.establishment_reject_code_
        && offset_21_padding_1_ == other.offset_21_padding_1_
        && last_incoming_seq_no_optional_ == other.last_incoming_seq_no_optional_;
}

bool EstablishRejectMessage::operator!=(const EstablishRejectMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
