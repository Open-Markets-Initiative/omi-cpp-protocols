#include "UnknownMdpsessionmgmtPayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

UnknownMdpsessionmgmtPayload::UnknownMdpsessionmgmtPayload(MdpsessionmgmtPayloadCode code) : type_(code) {}

UnknownMdpsessionmgmtPayload::UnknownMdpsessionmgmtPayload(MdpsessionmgmtPayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownMdpsessionmgmtPayload::set_type(MdpsessionmgmtPayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownMdpsessionmgmtPayload::body() const { return body_; }
std::vector<std::byte>& UnknownMdpsessionmgmtPayload::body() { return body_; }
void UnknownMdpsessionmgmtPayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

MdpsessionmgmtPayloadCode UnknownMdpsessionmgmtPayload::type() const { return type_; }

std::string_view UnknownMdpsessionmgmtPayload::name() const { return "Unknown MdpsessionmgmtPayload"; }

std::size_t UnknownMdpsessionmgmtPayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownMdpsessionmgmtPayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownMdpsessionmgmtPayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownMdpsessionmgmtPayload::encoded_size() const { return body_.size(); }

void UnknownMdpsessionmgmtPayload::accept(MdpsessionmgmtPayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<MdpsessionmgmtPayload> UnknownMdpsessionmgmtPayload::clone() const { return std::make_unique<UnknownMdpsessionmgmtPayload>(*this); }

void UnknownMdpsessionmgmtPayload::print(std::ostream& out) const {
    out << "UnknownMdpsessionmgmtPayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownMdpsessionmgmtPayload::equals(const MdpsessionmgmtPayload& other) const {
    const auto* that = dynamic_cast<const UnknownMdpsessionmgmtPayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownMdpsessionmgmtPayload::operator==(const UnknownMdpsessionmgmtPayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownMdpsessionmgmtPayload::operator!=(const UnknownMdpsessionmgmtPayload& other) const { return !(*this == other); }

} // namespace cme::globex::mdp3::sbe::v1_13
