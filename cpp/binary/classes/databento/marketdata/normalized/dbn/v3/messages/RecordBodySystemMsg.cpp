#include "RecordBodySystemMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

RecordBodySystemMsg::RecordBodySystemMsg(const std::string& msg, SystemCode system_code)
  : msg_(msg), system_code_(system_code) {}

const std::string& RecordBodySystemMsg::msg() const { return msg_; }
std::string& RecordBodySystemMsg::msg() { return msg_; }
void RecordBodySystemMsg::set_msg(const std::string& value) { msg_ = value; }

SystemCode RecordBodySystemMsg::system_code() const { return system_code_; }
void RecordBodySystemMsg::set_system_code(SystemCode value) { system_code_ = value; }

GatewayMessageCode RecordBodySystemMsg::type() const { return message_type; }

std::string_view RecordBodySystemMsg::name() const { return "System Msg"; }

std::size_t RecordBodySystemMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RecordBodySystemMsg", wire_size, length);

    msg_ = wire::read_text(data + offset, 303, '\0');
    offset += 303;

    system_code_ = static_cast<SystemCode>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t RecordBodySystemMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RecordBodySystemMsg", wire_size, capacity);

    wire::write_text(data + offset, 303, '\0', msg_);
    offset += 303;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(system_code_));
    offset += 1;

    return offset;
}

std::size_t RecordBodySystemMsg::encoded_size() const {
    return wire_size;
}

void RecordBodySystemMsg::accept(GatewayMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<GatewayMessage> RecordBodySystemMsg::clone() const {
    return std::make_unique<RecordBodySystemMsg>(*this);
}

void RecordBodySystemMsg::print(std::ostream& out) const {
    out << "RecordBodySystemMsg{";
    out << "msg=";
    print::text(out, msg_);
    out << ", system_code=";
    out << system_code_;
    out << '}';
}

bool RecordBodySystemMsg::equals(const GatewayMessage& other) const {
    const auto* that = dynamic_cast<const RecordBodySystemMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool RecordBodySystemMsg::operator==(const RecordBodySystemMsg& other) const {
    return msg_ == other.msg_
        && system_code_ == other.system_code_;
}

bool RecordBodySystemMsg::operator!=(const RecordBodySystemMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v3
