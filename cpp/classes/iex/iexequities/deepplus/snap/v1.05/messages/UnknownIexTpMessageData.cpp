#include "UnknownIexTpMessageData.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

UnknownIexTpMessageData::UnknownIexTpMessageData(IexTpMessageDataCode code) : type_(code) {}

UnknownIexTpMessageData::UnknownIexTpMessageData(IexTpMessageDataCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownIexTpMessageData::set_type(IexTpMessageDataCode code) { type_ = code; }

const std::vector<std::byte>& UnknownIexTpMessageData::body() const { return body_; }
std::vector<std::byte>& UnknownIexTpMessageData::body() { return body_; }
void UnknownIexTpMessageData::set_body(const std::vector<std::byte>& value) { body_ = value; }

IexTpMessageDataCode UnknownIexTpMessageData::type() const { return type_; }

std::string_view UnknownIexTpMessageData::name() const { return "Unknown IexTpMessageData"; }

std::size_t UnknownIexTpMessageData::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownIexTpMessageData::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownIexTpMessageData", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownIexTpMessageData::encoded_size() const { return body_.size(); }

void UnknownIexTpMessageData::accept(IexTpMessageDataVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<IexTpMessageData> UnknownIexTpMessageData::clone() const { return std::make_unique<UnknownIexTpMessageData>(*this); }

void UnknownIexTpMessageData::print(std::ostream& out) const {
    out << "UnknownIexTpMessageData{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownIexTpMessageData::equals(const IexTpMessageData& other) const {
    const auto* that = dynamic_cast<const UnknownIexTpMessageData*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownIexTpMessageData::operator==(const UnknownIexTpMessageData& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownIexTpMessageData::operator!=(const UnknownIexTpMessageData& other) const { return !(*this == other); }

} // namespace iex::iexequities::deepplus::snap::v1_05
