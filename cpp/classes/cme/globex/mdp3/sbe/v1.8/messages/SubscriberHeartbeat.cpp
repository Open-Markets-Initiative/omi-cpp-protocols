#include "SubscriberHeartbeat.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

MdpsessionmgmtPayloadCode SubscriberHeartbeat::type() const { return message_type; }

std::string_view SubscriberHeartbeat::name() const { return "Subscriber Heartbeat"; }

std::size_t SubscriberHeartbeat::decode(const std::byte* data, std::size_t length) {
    (void)data;
    (void)length;
    return 0;
}

std::size_t SubscriberHeartbeat::encode(std::byte* data, std::size_t capacity) const {
    (void)data;
    (void)capacity;
    return 0;
}

std::size_t SubscriberHeartbeat::encoded_size() const {
    return wire_size;
}

void SubscriberHeartbeat::accept(MdpsessionmgmtPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MdpsessionmgmtPayload> SubscriberHeartbeat::clone() const {
    return std::make_unique<SubscriberHeartbeat>(*this);
}

void SubscriberHeartbeat::print(std::ostream& out) const {
    out << "SubscriberHeartbeat{";
    out << '}';
}

bool SubscriberHeartbeat::equals(const MdpsessionmgmtPayload& other) const {
    const auto* that = dynamic_cast<const SubscriberHeartbeat*>(&other);
    return that != nullptr && *this == *that;
}

bool SubscriberHeartbeat::operator==(const SubscriberHeartbeat& other) const {
    (void)other;
    return true;
}

bool SubscriberHeartbeat::operator!=(const SubscriberHeartbeat& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_8
