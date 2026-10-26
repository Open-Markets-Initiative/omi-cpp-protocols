#include "NegotiationResponse.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

NegotiationResponse::NegotiationResponse(std::uint64_t uuid, std::chrono::nanoseconds request_timestamp, std::optional<std::uint16_t> secret_key_secure_id_expiration, const std::array<std::byte, 4>& padding_4)
  : uuid_(uuid), request_timestamp_(request_timestamp), secret_key_secure_id_expiration_(secret_key_secure_id_expiration), padding_4_(padding_4) {}

std::uint64_t NegotiationResponse::uuid() const { return uuid_; }
void NegotiationResponse::set_uuid(std::uint64_t value) { uuid_ = value; }

std::chrono::nanoseconds NegotiationResponse::request_timestamp() const { return request_timestamp_; }
void NegotiationResponse::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

std::optional<std::uint16_t> NegotiationResponse::secret_key_secure_id_expiration() const { return secret_key_secure_id_expiration_; }
void NegotiationResponse::set_secret_key_secure_id_expiration(std::optional<std::uint16_t> value) { secret_key_secure_id_expiration_ = value; }

const std::array<std::byte, 4>& NegotiationResponse::padding_4() const { return padding_4_; }
std::array<std::byte, 4>& NegotiationResponse::padding_4() { return padding_4_; }
void NegotiationResponse::set_padding_4(const std::array<std::byte, 4>& value) { padding_4_ = value; }

MdpsessionmgmtPayloadCode NegotiationResponse::type() const { return message_type; }

std::string_view NegotiationResponse::name() const { return "Negotiation Response"; }

std::size_t NegotiationResponse::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NegotiationResponse", wire_size, length);

    uuid_ = wire::read_u64_le(data + offset);
    offset += 8;

    request_timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    secret_key_secure_id_expiration_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::read_bytes(data + offset, padding_4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t NegotiationResponse::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NegotiationResponse", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(uuid_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(request_timestamp_.count()));
    offset += 8;

    wire::write_u16_le(data + offset, secret_key_secure_id_expiration_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_bytes(data + offset, padding_4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t NegotiationResponse::encoded_size() const {
    return wire_size;
}

void NegotiationResponse::accept(MdpsessionmgmtPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MdpsessionmgmtPayload> NegotiationResponse::clone() const {
    return std::make_unique<NegotiationResponse>(*this);
}

void NegotiationResponse::print(std::ostream& out) const {
    out << "NegotiationResponse{";
    out << "uuid=";
    out << uuid_;
    out << ", request_timestamp=";
    out << request_timestamp_.count();
    out << ", secret_key_secure_id_expiration=";
    print::optional(out, secret_key_secure_id_expiration_);
    out << ", padding_4=";
    print::hex(out, padding_4_.data(), padding_4_.size());
    out << '}';
}

bool NegotiationResponse::equals(const MdpsessionmgmtPayload& other) const {
    const auto* that = dynamic_cast<const NegotiationResponse*>(&other);
    return that != nullptr && *this == *that;
}

bool NegotiationResponse::operator==(const NegotiationResponse& other) const {
    return uuid_ == other.uuid_
        && request_timestamp_ == other.request_timestamp_
        && secret_key_secure_id_expiration_ == other.secret_key_secure_id_expiration_
        && padding_4_ == other.padding_4_;
}

bool NegotiationResponse::operator!=(const NegotiationResponse& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
