#include "UnknownFileMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

UnknownFileMessage::UnknownFileMessage(FileMessageCode code) : type_(code) {}

UnknownFileMessage::UnknownFileMessage(FileMessageCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownFileMessage::set_type(FileMessageCode code) { type_ = code; }

const std::vector<std::byte>& UnknownFileMessage::body() const { return body_; }
std::vector<std::byte>& UnknownFileMessage::body() { return body_; }
void UnknownFileMessage::set_body(const std::vector<std::byte>& value) { body_ = value; }

FileMessageCode UnknownFileMessage::type() const { return type_; }

std::string_view UnknownFileMessage::name() const { return "Unknown FileMessage"; }

std::size_t UnknownFileMessage::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownFileMessage::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownFileMessage", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownFileMessage::encoded_size() const { return body_.size(); }

void UnknownFileMessage::accept(FileMessageVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<FileMessage> UnknownFileMessage::clone() const { return std::make_unique<UnknownFileMessage>(*this); }

void UnknownFileMessage::print(std::ostream& out) const {
    out << "UnknownFileMessage{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownFileMessage::equals(const FileMessage& other) const {
    const auto* that = dynamic_cast<const UnknownFileMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownFileMessage::operator==(const UnknownFileMessage& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownFileMessage::operator!=(const UnknownFileMessage& other) const { return !(*this == other); }

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
