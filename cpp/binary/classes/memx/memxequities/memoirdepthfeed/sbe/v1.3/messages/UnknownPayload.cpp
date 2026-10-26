#include "UnknownPayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

UnknownPayload::UnknownPayload(PayloadCode code) : type_(code) {}

UnknownPayload::UnknownPayload(PayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownPayload::set_type(PayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownPayload::body() const { return body_; }
std::vector<std::byte>& UnknownPayload::body() { return body_; }
void UnknownPayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

PayloadCode UnknownPayload::type() const { return type_; }

std::string_view UnknownPayload::name() const { return "Unknown Payload"; }

std::size_t UnknownPayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownPayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownPayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownPayload::encoded_size() const { return body_.size(); }

void UnknownPayload::accept(PayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Payload> UnknownPayload::clone() const { return std::make_unique<UnknownPayload>(*this); }

void UnknownPayload::print(std::ostream& out) const {
    out << "UnknownPayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownPayload::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const UnknownPayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownPayload::operator==(const UnknownPayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownPayload::operator!=(const UnknownPayload& other) const { return !(*this == other); }

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
