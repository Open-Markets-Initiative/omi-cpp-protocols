#include "LogoutRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

LogoutRequest::LogoutRequest(LogoutReason logout_reason, const std::string& logout_text)
  : logout_reason_(logout_reason), logout_text_(logout_text) {}

LogoutReason LogoutRequest::logout_reason() const { return logout_reason_; }
void LogoutRequest::set_logout_reason(LogoutReason value) { logout_reason_ = value; }

const std::string& LogoutRequest::logout_text() const { return logout_text_; }
std::string& LogoutRequest::logout_text() { return logout_text_; }
void LogoutRequest::set_logout_text(const std::string& value) { logout_text_ = value; }

TcpMessageCode LogoutRequest::type() const { return message_type; }

std::string_view LogoutRequest::name() const { return "Logout Request"; }

std::size_t LogoutRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("LogoutRequest", offset + 1, length);
    logout_reason_ = static_cast<LogoutReason>(wire::read_char(data + offset));
    offset += 1;

    {
        const std::size_t count = length - offset;
        wire::require("LogoutRequest", offset + count, length);
        logout_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t LogoutRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LogoutRequest", encoded_size(), capacity);

    wire::write_char(data + offset, static_cast<char>(logout_reason_));
    offset += 1;

    wire::require_capacity("encode", offset + logout_text_.size(), capacity);
    wire::write_text(data + offset, logout_text_.size(), ' ', logout_text_);
    offset += logout_text_.size();

    return offset;
}

std::size_t LogoutRequest::encoded_size() const {
    return 1 + logout_text_.size();
}

void LogoutRequest::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> LogoutRequest::clone() const {
    return std::make_unique<LogoutRequest>(*this);
}

void LogoutRequest::print(std::ostream& out) const {
    out << "LogoutRequest{";
    out << "logout_reason=";
    out << logout_reason_;
    out << ", logout_text=";
    print::text(out, logout_text_);
    out << '}';
}

bool LogoutRequest::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const LogoutRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool LogoutRequest::operator==(const LogoutRequest& other) const {
    return logout_reason_ == other.logout_reason_
        && logout_text_ == other.logout_text_;
}

bool LogoutRequest::operator!=(const LogoutRequest& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
