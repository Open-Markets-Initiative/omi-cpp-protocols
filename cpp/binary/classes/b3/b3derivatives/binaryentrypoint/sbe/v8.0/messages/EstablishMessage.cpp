#include "EstablishMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

EstablishMessage::EstablishMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds timestamp, std::uint64_t keep_alive_interval, std::uint32_t next_seq_no, CancelOnDisconnectType cancel_on_disconnect_type, const std::array<std::byte, 1>& offset_33_padding_1, std::uint64_t cod_timeout_window, const Credentials& credentials)
  : session_id_(session_id), session_ver_id_(session_ver_id), timestamp_(timestamp), keep_alive_interval_(keep_alive_interval), next_seq_no_(next_seq_no), cancel_on_disconnect_type_(cancel_on_disconnect_type), offset_33_padding_1_(offset_33_padding_1), cod_timeout_window_(cod_timeout_window), credentials_(credentials) {}

std::uint32_t EstablishMessage::session_id() const { return session_id_; }
void EstablishMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint64_t EstablishMessage::session_ver_id() const { return session_ver_id_; }
void EstablishMessage::set_session_ver_id(std::uint64_t value) { session_ver_id_ = value; }

std::chrono::nanoseconds EstablishMessage::timestamp() const { return timestamp_; }
void EstablishMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t EstablishMessage::keep_alive_interval() const { return keep_alive_interval_; }
void EstablishMessage::set_keep_alive_interval(std::uint64_t value) { keep_alive_interval_ = value; }

std::uint32_t EstablishMessage::next_seq_no() const { return next_seq_no_; }
void EstablishMessage::set_next_seq_no(std::uint32_t value) { next_seq_no_ = value; }

CancelOnDisconnectType EstablishMessage::cancel_on_disconnect_type() const { return cancel_on_disconnect_type_; }
void EstablishMessage::set_cancel_on_disconnect_type(CancelOnDisconnectType value) { cancel_on_disconnect_type_ = value; }

const std::array<std::byte, 1>& EstablishMessage::offset_33_padding_1() const { return offset_33_padding_1_; }
std::array<std::byte, 1>& EstablishMessage::offset_33_padding_1() { return offset_33_padding_1_; }
void EstablishMessage::set_offset_33_padding_1(const std::array<std::byte, 1>& value) { offset_33_padding_1_ = value; }

std::uint64_t EstablishMessage::cod_timeout_window() const { return cod_timeout_window_; }
void EstablishMessage::set_cod_timeout_window(std::uint64_t value) { cod_timeout_window_ = value; }

const Credentials& EstablishMessage::credentials() const { return credentials_; }
Credentials& EstablishMessage::credentials() { return credentials_; }
void EstablishMessage::set_credentials(const Credentials& value) { credentials_ = value; }

MessageCode EstablishMessage::type() const { return message_type; }

std::string_view EstablishMessage::name() const { return "Establish Message"; }

std::size_t EstablishMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("EstablishMessage", offset + 4, length);
    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("EstablishMessage", offset + 8, length);
    session_ver_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("EstablishMessage", offset + 8, length);
    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("EstablishMessage", offset + 8, length);
    keep_alive_interval_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("EstablishMessage", offset + 4, length);
    next_seq_no_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("EstablishMessage", offset + 1, length);
    cancel_on_disconnect_type_ = static_cast<CancelOnDisconnectType>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("EstablishMessage", offset + 1, length);
    wire::read_bytes(data + offset, offset_33_padding_1_.data(), 1);
    offset += 1;

    wire::require("EstablishMessage", offset + 8, length);
    cod_timeout_window_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += credentials_.decode(data + offset, length - offset);

    return offset;
}

std::size_t EstablishMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EstablishMessage", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(session_ver_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(keep_alive_interval_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(next_seq_no_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(cancel_on_disconnect_type_));
    offset += 1;

    wire::write_bytes(data + offset, offset_33_padding_1_.data(), 1);
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(cod_timeout_window_));
    offset += 8;

    offset += credentials_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t EstablishMessage::encoded_size() const {
    return 4 + 8 + 8 + 8 + 4 + 1 + 1 + 8 + credentials_.encoded_size();
}

void EstablishMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EstablishMessage::clone() const {
    return std::make_unique<EstablishMessage>(*this);
}

void EstablishMessage::print(std::ostream& out) const {
    out << "EstablishMessage{";
    out << "session_id=";
    out << session_id_;
    out << ", session_ver_id=";
    out << session_ver_id_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", keep_alive_interval=";
    out << keep_alive_interval_;
    out << ", next_seq_no=";
    out << next_seq_no_;
    out << ", cancel_on_disconnect_type=";
    out << cancel_on_disconnect_type_;
    out << ", offset_33_padding_1=";
    print::hex(out, offset_33_padding_1_.data(), offset_33_padding_1_.size());
    out << ", cod_timeout_window=";
    out << cod_timeout_window_;
    out << ", credentials=";
    credentials_.print(out);
    out << '}';
}

bool EstablishMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EstablishMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EstablishMessage::operator==(const EstablishMessage& other) const {
    return session_id_ == other.session_id_
        && session_ver_id_ == other.session_ver_id_
        && timestamp_ == other.timestamp_
        && keep_alive_interval_ == other.keep_alive_interval_
        && next_seq_no_ == other.next_seq_no_
        && cancel_on_disconnect_type_ == other.cancel_on_disconnect_type_
        && offset_33_padding_1_ == other.offset_33_padding_1_
        && cod_timeout_window_ == other.cod_timeout_window_
        && credentials_ == other.credentials_;
}

bool EstablishMessage::operator!=(const EstablishMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
