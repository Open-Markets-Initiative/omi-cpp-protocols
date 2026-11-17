// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/SynchronizationComplete.cpp
#include "SynchronizationComplete.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

SynchronizationComplete::SynchronizationComplete(std::uint8_t matching_engine_id)
  : matching_engine_id_(matching_engine_id) {}

std::uint8_t SynchronizationComplete::matching_engine_id() const { return matching_engine_id_; }
void SynchronizationComplete::set_matching_engine_id(std::uint8_t value) { matching_engine_id_ = value; }

TcpMessageCode SynchronizationComplete::type() const { return message_type; }

std::string_view SynchronizationComplete::name() const { return "Synchronization Complete"; }

std::size_t SynchronizationComplete::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SynchronizationComplete", wire_size, length);

    matching_engine_id_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t SynchronizationComplete::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SynchronizationComplete", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(matching_engine_id_));
    offset += 1;

    return offset;
}

std::size_t SynchronizationComplete::encoded_size() const {
    return wire_size;
}

void SynchronizationComplete::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> SynchronizationComplete::clone() const {
    return std::make_unique<SynchronizationComplete>(*this);
}

void SynchronizationComplete::print(std::ostream& out) const {
    out << "SynchronizationComplete{";
    out << "matching_engine_id=";
    out << static_cast<int>(matching_engine_id_);
    out << '}';
}

bool SynchronizationComplete::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const SynchronizationComplete*>(&other);
    return that != nullptr && *this == *that;
}

bool SynchronizationComplete::operator==(const SynchronizationComplete& other) const {
    return matching_engine_id_ == other.matching_engine_id_;
}

bool SynchronizationComplete::operator!=(const SynchronizationComplete& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
