#include "ClientPayloadTerminate.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

ClientPayloadTerminate::ClientPayloadTerminate(const std::string& reason, std::uint64_t uuid, std::chrono::nanoseconds request_timestamp, ErrorCodes error_codes, const std::array<std::byte, 5>& padding_5)
  : reason_(reason), uuid_(uuid), request_timestamp_(request_timestamp), error_codes_(error_codes), padding_5_(padding_5) {}

const std::string& ClientPayloadTerminate::reason() const { return reason_; }
std::string& ClientPayloadTerminate::reason() { return reason_; }
void ClientPayloadTerminate::set_reason(const std::string& value) { reason_ = value; }

std::uint64_t ClientPayloadTerminate::uuid() const { return uuid_; }
void ClientPayloadTerminate::set_uuid(std::uint64_t value) { uuid_ = value; }

std::chrono::nanoseconds ClientPayloadTerminate::request_timestamp() const { return request_timestamp_; }
void ClientPayloadTerminate::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

ErrorCodes ClientPayloadTerminate::error_codes() const { return error_codes_; }
void ClientPayloadTerminate::set_error_codes(ErrorCodes value) { error_codes_ = value; }

const std::array<std::byte, 5>& ClientPayloadTerminate::padding_5() const { return padding_5_; }
std::array<std::byte, 5>& ClientPayloadTerminate::padding_5() { return padding_5_; }
void ClientPayloadTerminate::set_padding_5(const std::array<std::byte, 5>& value) { padding_5_ = value; }

ClientTcpMessageCode ClientPayloadTerminate::type() const { return message_type; }

std::string_view ClientPayloadTerminate::name() const { return "Terminate"; }

std::size_t ClientPayloadTerminate::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ClientPayloadTerminate", wire_size, length);

    reason_ = wire::read_text(data + offset, 48, '\0');
    offset += 48;

    uuid_ = wire::read_u64_le(data + offset);
    offset += 8;

    request_timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    error_codes_ = static_cast<ErrorCodes>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_5_.data(), 5);
    offset += 5;

    return offset;
}

std::size_t ClientPayloadTerminate::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientPayloadTerminate", wire_size, capacity);

    wire::write_text(data + offset, 48, '\0', reason_);
    offset += 48;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(uuid_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(request_timestamp_.count()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(error_codes_));
    offset += 1;

    wire::write_bytes(data + offset, padding_5_.data(), 5);
    offset += 5;

    return offset;
}

std::size_t ClientPayloadTerminate::encoded_size() const {
    return wire_size;
}

void ClientPayloadTerminate::accept(ClientTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ClientTcpMessage> ClientPayloadTerminate::clone() const {
    return std::make_unique<ClientPayloadTerminate>(*this);
}

void ClientPayloadTerminate::print(std::ostream& out) const {
    out << "ClientPayloadTerminate{";
    out << "reason=";
    print::text(out, reason_);
    out << ", uuid=";
    out << uuid_;
    out << ", request_timestamp=";
    out << request_timestamp_.count();
    out << ", error_codes=";
    out << error_codes_;
    out << ", padding_5=";
    print::hex(out, padding_5_.data(), padding_5_.size());
    out << '}';
}

bool ClientPayloadTerminate::equals(const ClientTcpMessage& other) const {
    const auto* that = dynamic_cast<const ClientPayloadTerminate*>(&other);
    return that != nullptr && *this == *that;
}

bool ClientPayloadTerminate::operator==(const ClientPayloadTerminate& other) const {
    return reason_ == other.reason_
        && uuid_ == other.uuid_
        && request_timestamp_ == other.request_timestamp_
        && error_codes_ == other.error_codes_
        && padding_5_ == other.padding_5_;
}

bool ClientPayloadTerminate::operator!=(const ClientPayloadTerminate& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
