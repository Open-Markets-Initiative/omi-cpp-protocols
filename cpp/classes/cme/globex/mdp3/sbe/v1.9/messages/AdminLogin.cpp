#include "AdminLogin.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

AdminLogin::AdminLogin(std::int8_t heart_bt_int)
  : heart_bt_int_(heart_bt_int) {}

std::int8_t AdminLogin::heart_bt_int() const { return heart_bt_int_; }
void AdminLogin::set_heart_bt_int(std::int8_t value) { heart_bt_int_ = value; }

MktdataPayloadCode AdminLogin::type() const { return message_type; }

std::string_view AdminLogin::name() const { return "Admin Login"; }

std::size_t AdminLogin::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AdminLogin", wire_size, length);

    heart_bt_int_ = wire::read_i8(data + offset);
    offset += 1;

    return offset;
}

std::size_t AdminLogin::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AdminLogin", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(heart_bt_int_));
    offset += 1;

    return offset;
}

std::size_t AdminLogin::encoded_size() const {
    return wire_size;
}

void AdminLogin::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> AdminLogin::clone() const {
    return std::make_unique<AdminLogin>(*this);
}

void AdminLogin::print(std::ostream& out) const {
    out << "AdminLogin{";
    out << "heart_bt_int=";
    out << static_cast<int>(heart_bt_int_);
    out << '}';
}

bool AdminLogin::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const AdminLogin*>(&other);
    return that != nullptr && *this == *that;
}

bool AdminLogin::operator==(const AdminLogin& other) const {
    return heart_bt_int_ == other.heart_bt_int_;
}

bool AdminLogin::operator!=(const AdminLogin& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
