#include "AdminHeartbeat.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

MktdataPayloadCode AdminHeartbeat::type() const { return message_type; }

std::string_view AdminHeartbeat::name() const { return "Admin Heartbeat"; }

std::size_t AdminHeartbeat::decode(const std::byte* data, std::size_t length) {
    (void)data;
    (void)length;
    return 0;
}

std::size_t AdminHeartbeat::encode(std::byte* data, std::size_t capacity) const {
    (void)data;
    (void)capacity;
    return 0;
}

std::size_t AdminHeartbeat::encoded_size() const {
    return wire_size;
}

void AdminHeartbeat::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> AdminHeartbeat::clone() const {
    return std::make_unique<AdminHeartbeat>(*this);
}

void AdminHeartbeat::print(std::ostream& out) const {
    out << "AdminHeartbeat{";
    out << '}';
}

bool AdminHeartbeat::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const AdminHeartbeat*>(&other);
    return that != nullptr && *this == *that;
}

bool AdminHeartbeat::operator==(const AdminHeartbeat& other) const {
    (void)other;
    return true;
}

bool AdminHeartbeat::operator!=(const AdminHeartbeat& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
