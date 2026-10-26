#include "IncrementalRefreshVolumeGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

IncrementalRefreshVolumeGroup::IncrementalRefreshVolumeGroup(std::int32_t md_entry_size, std::int32_t security_id, std::uint32_t rpt_seq, MdUpdateAction md_update_action, const std::array<std::byte, 3>& padding_3)
  : md_entry_size_(md_entry_size), security_id_(security_id), rpt_seq_(rpt_seq), md_update_action_(md_update_action), padding_3_(padding_3) {}

std::int32_t IncrementalRefreshVolumeGroup::md_entry_size() const { return md_entry_size_; }
void IncrementalRefreshVolumeGroup::set_md_entry_size(std::int32_t value) { md_entry_size_ = value; }

std::int32_t IncrementalRefreshVolumeGroup::security_id() const { return security_id_; }
void IncrementalRefreshVolumeGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t IncrementalRefreshVolumeGroup::rpt_seq() const { return rpt_seq_; }
void IncrementalRefreshVolumeGroup::set_rpt_seq(std::uint32_t value) { rpt_seq_ = value; }

MdUpdateAction IncrementalRefreshVolumeGroup::md_update_action() const { return md_update_action_; }
void IncrementalRefreshVolumeGroup::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

const std::array<std::byte, 3>& IncrementalRefreshVolumeGroup::padding_3() const { return padding_3_; }
std::array<std::byte, 3>& IncrementalRefreshVolumeGroup::padding_3() { return padding_3_; }
void IncrementalRefreshVolumeGroup::set_padding_3(const std::array<std::byte, 3>& value) { padding_3_ = value; }

std::size_t IncrementalRefreshVolumeGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshVolumeGroup", wire_size, length);

    md_entry_size_ = wire::read_i32_le(data + offset);
    offset += 4;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    rpt_seq_ = wire::read_u32_le(data + offset);
    offset += 4;

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t IncrementalRefreshVolumeGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshVolumeGroup", wire_size, capacity);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(md_entry_size_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(rpt_seq_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_bytes(data + offset, padding_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t IncrementalRefreshVolumeGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshVolumeGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshVolumeGroup{";
    out << "md_entry_size=";
    out << md_entry_size_;
    out << ", security_id=";
    out << security_id_;
    out << ", rpt_seq=";
    out << rpt_seq_;
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", padding_3=";
    print::hex(out, padding_3_.data(), padding_3_.size());
    out << '}';
}

bool IncrementalRefreshVolumeGroup::operator==(const IncrementalRefreshVolumeGroup& other) const {
    return md_entry_size_ == other.md_entry_size_
        && security_id_ == other.security_id_
        && rpt_seq_ == other.rpt_seq_
        && md_update_action_ == other.md_update_action_
        && padding_3_ == other.padding_3_;
}

bool IncrementalRefreshVolumeGroup::operator!=(const IncrementalRefreshVolumeGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshVolumeGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
