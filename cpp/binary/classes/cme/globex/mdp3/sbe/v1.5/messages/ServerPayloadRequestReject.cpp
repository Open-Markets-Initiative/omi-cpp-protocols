#include "ServerPayloadRequestReject.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

ServerPayloadRequestReject::ServerPayloadRequestReject(std::optional<std::uint32_t> md_req_id_optional, MdReqRejReason md_req_rej_reason, const std::string& text)
  : md_req_id_optional_(md_req_id_optional), md_req_rej_reason_(md_req_rej_reason), text_(text) {}

std::optional<std::uint32_t> ServerPayloadRequestReject::md_req_id_optional() const { return md_req_id_optional_; }
void ServerPayloadRequestReject::set_md_req_id_optional(std::optional<std::uint32_t> value) { md_req_id_optional_ = value; }

MdReqRejReason ServerPayloadRequestReject::md_req_rej_reason() const { return md_req_rej_reason_; }
void ServerPayloadRequestReject::set_md_req_rej_reason(MdReqRejReason value) { md_req_rej_reason_ = value; }

const std::string& ServerPayloadRequestReject::text() const { return text_; }
std::string& ServerPayloadRequestReject::text() { return text_; }
void ServerPayloadRequestReject::set_text(const std::string& value) { text_ = value; }

ServerTcpMessageCode ServerPayloadRequestReject::type() const { return message_type; }

std::string_view ServerPayloadRequestReject::name() const { return "Request Reject"; }

std::size_t ServerPayloadRequestReject::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ServerPayloadRequestReject", wire_size, length);

    md_req_id_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(4294967295ULL));
    offset += 4;

    md_req_rej_reason_ = static_cast<MdReqRejReason>(wire::read_u8(data + offset));
    offset += 1;

    text_ = wire::read_text(data + offset, 100, '\0');
    offset += 100;

    return offset;
}

std::size_t ServerPayloadRequestReject::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadRequestReject", wire_size, capacity);

    wire::write_u32_le(data + offset, md_req_id_optional_.value_or(static_cast<std::uint32_t>(4294967295ULL)));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_req_rej_reason_));
    offset += 1;

    wire::write_text(data + offset, 100, '\0', text_);
    offset += 100;

    return offset;
}

std::size_t ServerPayloadRequestReject::encoded_size() const {
    return wire_size;
}

void ServerPayloadRequestReject::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadRequestReject::clone() const {
    return std::make_unique<ServerPayloadRequestReject>(*this);
}

void ServerPayloadRequestReject::print(std::ostream& out) const {
    out << "ServerPayloadRequestReject{";
    out << "md_req_id_optional=";
    print::optional(out, md_req_id_optional_);
    out << ", md_req_rej_reason=";
    out << md_req_rej_reason_;
    out << ", text=";
    print::text(out, text_);
    out << '}';
}

bool ServerPayloadRequestReject::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadRequestReject*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadRequestReject::operator==(const ServerPayloadRequestReject& other) const {
    return md_req_id_optional_ == other.md_req_id_optional_
        && md_req_rej_reason_ == other.md_req_rej_reason_
        && text_ == other.text_;
}

bool ServerPayloadRequestReject::operator!=(const ServerPayloadRequestReject& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_5
