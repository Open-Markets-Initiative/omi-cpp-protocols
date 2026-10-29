#include "ChannelResetGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

ChannelResetGroup::ChannelResetGroup(std::int16_t appl_id)
  : appl_id_(appl_id) {}

std::int16_t ChannelResetGroup::appl_id() const { return appl_id_; }
void ChannelResetGroup::set_appl_id(std::int16_t value) { appl_id_ = value; }

std::size_t ChannelResetGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ChannelResetGroup", wire_size, length);

    appl_id_ = wire::read_i16_le(data + offset);
    offset += 2;

    return offset;
}

std::size_t ChannelResetGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ChannelResetGroup", wire_size, capacity);

    wire::write_i16_le(data + offset, static_cast<std::int16_t>(appl_id_));
    offset += 2;

    return offset;
}

std::size_t ChannelResetGroup::encoded_size() const {
    return wire_size;
}

void ChannelResetGroup::print(std::ostream& out) const {
    out << "ChannelResetGroup{";
    out << "appl_id=";
    out << appl_id_;
    out << '}';
}

bool ChannelResetGroup::operator==(const ChannelResetGroup& other) const {
    return appl_id_ == other.appl_id_;
}

bool ChannelResetGroup::operator!=(const ChannelResetGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ChannelResetGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
