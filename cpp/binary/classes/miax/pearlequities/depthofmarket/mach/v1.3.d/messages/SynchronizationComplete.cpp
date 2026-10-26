#include "SynchronizationComplete.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

SynchronizationComplete::SynchronizationComplete(std::uint8_t number_of_matching_engines)
  : number_of_matching_engines_(number_of_matching_engines) {}

std::uint8_t SynchronizationComplete::number_of_matching_engines() const { return number_of_matching_engines_; }
void SynchronizationComplete::set_number_of_matching_engines(std::uint8_t value) { number_of_matching_engines_ = value; }

TcpMessageCode SynchronizationComplete::type() const { return message_type; }

std::string_view SynchronizationComplete::name() const { return "Synchronization Complete"; }

std::size_t SynchronizationComplete::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SynchronizationComplete", wire_size, length);

    number_of_matching_engines_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t SynchronizationComplete::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SynchronizationComplete", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_matching_engines_));
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
    out << "number_of_matching_engines=";
    out << static_cast<int>(number_of_matching_engines_);
    out << '}';
}

bool SynchronizationComplete::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const SynchronizationComplete*>(&other);
    return that != nullptr && *this == *that;
}

bool SynchronizationComplete::operator==(const SynchronizationComplete& other) const {
    return number_of_matching_engines_ == other.number_of_matching_engines_;
}

bool SynchronizationComplete::operator!=(const SynchronizationComplete& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
