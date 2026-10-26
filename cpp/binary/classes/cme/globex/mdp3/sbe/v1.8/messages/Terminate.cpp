#include "Terminate.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

Terminate::Terminate(const std::string& reason, std::uint64_t uuid, std::chrono::nanoseconds request_timestamp, ErrorCodes error_codes, const std::array<std::byte, 5>& padding_5)
  : reason_(reason), uuid_(uuid), request_timestamp_(request_timestamp), error_codes_(error_codes), padding_5_(padding_5) {}

const std::string& Terminate::reason() const { return reason_; }
std::string& Terminate::reason() { return reason_; }
void Terminate::set_reason(const std::string& value) { reason_ = value; }

std::uint64_t Terminate::uuid() const { return uuid_; }
void Terminate::set_uuid(std::uint64_t value) { uuid_ = value; }

std::chrono::nanoseconds Terminate::request_timestamp() const { return request_timestamp_; }
void Terminate::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

ErrorCodes Terminate::error_codes() const { return error_codes_; }
void Terminate::set_error_codes(ErrorCodes value) { error_codes_ = value; }

const std::array<std::byte, 5>& Terminate::padding_5() const { return padding_5_; }
std::array<std::byte, 5>& Terminate::padding_5() { return padding_5_; }
void Terminate::set_padding_5(const std::array<std::byte, 5>& value) { padding_5_ = value; }

MdpsessionmgmtPayloadCode Terminate::type() const { return message_type; }

std::string_view Terminate::name() const { return "Terminate"; }

std::size_t Terminate::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Terminate", wire_size, length);

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

std::size_t Terminate::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Terminate", wire_size, capacity);

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

std::size_t Terminate::encoded_size() const {
    return wire_size;
}

void Terminate::accept(MdpsessionmgmtPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MdpsessionmgmtPayload> Terminate::clone() const {
    return std::make_unique<Terminate>(*this);
}

void Terminate::print(std::ostream& out) const {
    out << "Terminate{";
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

bool Terminate::equals(const MdpsessionmgmtPayload& other) const {
    const auto* that = dynamic_cast<const Terminate*>(&other);
    return that != nullptr && *this == *that;
}

bool Terminate::operator==(const Terminate& other) const {
    return reason_ == other.reason_
        && uuid_ == other.uuid_
        && request_timestamp_ == other.request_timestamp_
        && error_codes_ == other.error_codes_
        && padding_5_ == other.padding_5_;
}

bool Terminate::operator!=(const Terminate& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_8
