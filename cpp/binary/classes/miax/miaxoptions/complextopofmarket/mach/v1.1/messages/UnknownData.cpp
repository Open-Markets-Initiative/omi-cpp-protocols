#include "UnknownData.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

UnknownData::UnknownData(DataCode code) : type_(code) {}

UnknownData::UnknownData(DataCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownData::set_type(DataCode code) { type_ = code; }

const std::vector<std::byte>& UnknownData::body() const { return body_; }
std::vector<std::byte>& UnknownData::body() { return body_; }
void UnknownData::set_body(const std::vector<std::byte>& value) { body_ = value; }

DataCode UnknownData::type() const { return type_; }

std::string_view UnknownData::name() const { return "Unknown Data"; }

std::size_t UnknownData::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownData::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownData", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownData::encoded_size() const { return body_.size(); }

void UnknownData::accept(DataVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Data> UnknownData::clone() const { return std::make_unique<UnknownData>(*this); }

void UnknownData::print(std::ostream& out) const {
    out << "UnknownData{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownData::equals(const Data& other) const {
    const auto* that = dynamic_cast<const UnknownData*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownData::operator==(const UnknownData& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownData::operator!=(const UnknownData& other) const { return !(*this == other); }

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
