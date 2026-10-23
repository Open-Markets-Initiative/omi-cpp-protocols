#include "RequestReject.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

RequestReject::RequestReject(std::optional<std::uint32_t> md_req_id_optional, MdReqRejReason md_req_rej_reason, const std::string& text)
  : md_req_id_optional_(md_req_id_optional), md_req_rej_reason_(md_req_rej_reason), text_(text) {}

std::optional<std::uint32_t> RequestReject::md_req_id_optional() const { return md_req_id_optional_; }
void RequestReject::set_md_req_id_optional(std::optional<std::uint32_t> value) { md_req_id_optional_ = value; }

MdReqRejReason RequestReject::md_req_rej_reason() const { return md_req_rej_reason_; }
void RequestReject::set_md_req_rej_reason(MdReqRejReason value) { md_req_rej_reason_ = value; }

const std::string& RequestReject::text() const { return text_; }
std::string& RequestReject::text() { return text_; }
void RequestReject::set_text(const std::string& value) { text_ = value; }

MdpsessionmgmtPayloadCode RequestReject::type() const { return message_type; }

std::string_view RequestReject::name() const { return "Request Reject"; }

std::size_t RequestReject::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RequestReject", wire_size, length);

    md_req_id_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(4294967295ULL));
    offset += 4;

    md_req_rej_reason_ = static_cast<MdReqRejReason>(wire::read_u8(data + offset));
    offset += 1;

    text_ = wire::read_text(data + offset, 100, '\0');
    offset += 100;

    return offset;
}

std::size_t RequestReject::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RequestReject", wire_size, capacity);

    wire::write_u32_le(data + offset, md_req_id_optional_.value_or(static_cast<std::uint32_t>(4294967295ULL)));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_req_rej_reason_));
    offset += 1;

    wire::write_text(data + offset, 100, '\0', text_);
    offset += 100;

    return offset;
}

std::size_t RequestReject::encoded_size() const {
    return wire_size;
}

void RequestReject::accept(MdpsessionmgmtPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MdpsessionmgmtPayload> RequestReject::clone() const {
    return std::make_unique<RequestReject>(*this);
}

void RequestReject::print(std::ostream& out) const {
    out << "RequestReject{";
    out << "md_req_id_optional=";
    print::optional(out, md_req_id_optional_);
    out << ", md_req_rej_reason=";
    out << md_req_rej_reason_;
    out << ", text=";
    print::text(out, text_);
    out << '}';
}

bool RequestReject::equals(const MdpsessionmgmtPayload& other) const {
    const auto* that = dynamic_cast<const RequestReject*>(&other);
    return that != nullptr && *this == *that;
}

bool RequestReject::operator==(const RequestReject& other) const {
    return md_req_id_optional_ == other.md_req_id_optional_
        && md_req_rej_reason_ == other.md_req_rej_reason_
        && text_ == other.text_;
}

bool RequestReject::operator!=(const RequestReject& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
