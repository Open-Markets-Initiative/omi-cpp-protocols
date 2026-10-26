#include "UnknownMktdataPayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

UnknownMktdataPayload::UnknownMktdataPayload(MktdataPayloadCode code) : type_(code) {}

UnknownMktdataPayload::UnknownMktdataPayload(MktdataPayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownMktdataPayload::set_type(MktdataPayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownMktdataPayload::body() const { return body_; }
std::vector<std::byte>& UnknownMktdataPayload::body() { return body_; }
void UnknownMktdataPayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

MktdataPayloadCode UnknownMktdataPayload::type() const { return type_; }

std::string_view UnknownMktdataPayload::name() const { return "Unknown MktdataPayload"; }

std::size_t UnknownMktdataPayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownMktdataPayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownMktdataPayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownMktdataPayload::encoded_size() const { return body_.size(); }

void UnknownMktdataPayload::accept(MktdataPayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<MktdataPayload> UnknownMktdataPayload::clone() const { return std::make_unique<UnknownMktdataPayload>(*this); }

void UnknownMktdataPayload::print(std::ostream& out) const {
    out << "UnknownMktdataPayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownMktdataPayload::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const UnknownMktdataPayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownMktdataPayload::operator==(const UnknownMktdataPayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownMktdataPayload::operator!=(const UnknownMktdataPayload& other) const { return !(*this == other); }

} // namespace cme::globex::mdp3::sbe::v1_8
