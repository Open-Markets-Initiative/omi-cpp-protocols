#include "SystemMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

SystemMsg::SystemMsg(const std::string& msg)
  : msg_(msg) {}

const std::string& SystemMsg::msg() const { return msg_; }
std::string& SystemMsg::msg() { return msg_; }
void SystemMsg::set_msg(const std::string& value) { msg_ = value; }

MessageCode SystemMsg::type() const { return message_type; }

std::string_view SystemMsg::name() const { return "System Msg"; }

std::size_t SystemMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SystemMsg", wire_size, length);

    msg_ = wire::read_text(data + offset, 64, '\0');
    offset += 64;

    return offset;
}

std::size_t SystemMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SystemMsg", wire_size, capacity);

    wire::write_text(data + offset, 64, '\0', msg_);
    offset += 64;

    return offset;
}

std::size_t SystemMsg::encoded_size() const {
    return wire_size;
}

void SystemMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SystemMsg::clone() const {
    return std::make_unique<SystemMsg>(*this);
}

void SystemMsg::print(std::ostream& out) const {
    out << "SystemMsg{";
    out << "msg=";
    print::text(out, msg_);
    out << '}';
}

bool SystemMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SystemMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool SystemMsg::operator==(const SystemMsg& other) const {
    return msg_ == other.msg_;
}

bool SystemMsg::operator!=(const SystemMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v1
