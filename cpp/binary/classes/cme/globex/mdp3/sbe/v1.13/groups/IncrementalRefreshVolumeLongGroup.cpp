#include "IncrementalRefreshVolumeLongGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshVolumeLongGroup::IncrementalRefreshVolumeLongGroup(std::uint64_t md_entry_size, std::int32_t security_id, std::uint32_t rpt_seq, MdUpdateAction md_update_action, const std::array<std::byte, 7>& padding_7)
  : md_entry_size_(md_entry_size), security_id_(security_id), rpt_seq_(rpt_seq), md_update_action_(md_update_action), padding_7_(padding_7) {}

std::uint64_t IncrementalRefreshVolumeLongGroup::md_entry_size() const { return md_entry_size_; }
void IncrementalRefreshVolumeLongGroup::set_md_entry_size(std::uint64_t value) { md_entry_size_ = value; }

std::int32_t IncrementalRefreshVolumeLongGroup::security_id() const { return security_id_; }
void IncrementalRefreshVolumeLongGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t IncrementalRefreshVolumeLongGroup::rpt_seq() const { return rpt_seq_; }
void IncrementalRefreshVolumeLongGroup::set_rpt_seq(std::uint32_t value) { rpt_seq_ = value; }

MdUpdateAction IncrementalRefreshVolumeLongGroup::md_update_action() const { return md_update_action_; }
void IncrementalRefreshVolumeLongGroup::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

const std::array<std::byte, 7>& IncrementalRefreshVolumeLongGroup::padding_7() const { return padding_7_; }
std::array<std::byte, 7>& IncrementalRefreshVolumeLongGroup::padding_7() { return padding_7_; }
void IncrementalRefreshVolumeLongGroup::set_padding_7(const std::array<std::byte, 7>& value) { padding_7_ = value; }

std::size_t IncrementalRefreshVolumeLongGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshVolumeLongGroup", wire_size, length);

    md_entry_size_ = wire::read_u64_le(data + offset);
    offset += 8;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    rpt_seq_ = wire::read_u32_le(data + offset);
    offset += 4;

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_7_.data(), 7);
    offset += 7;

    return offset;
}

std::size_t IncrementalRefreshVolumeLongGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshVolumeLongGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(md_entry_size_));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(rpt_seq_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_bytes(data + offset, padding_7_.data(), 7);
    offset += 7;

    return offset;
}

std::size_t IncrementalRefreshVolumeLongGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshVolumeLongGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshVolumeLongGroup{";
    out << "md_entry_size=";
    out << md_entry_size_;
    out << ", security_id=";
    out << security_id_;
    out << ", rpt_seq=";
    out << rpt_seq_;
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", padding_7=";
    print::hex(out, padding_7_.data(), padding_7_.size());
    out << '}';
}

bool IncrementalRefreshVolumeLongGroup::operator==(const IncrementalRefreshVolumeLongGroup& other) const {
    return md_entry_size_ == other.md_entry_size_
        && security_id_ == other.security_id_
        && rpt_seq_ == other.rpt_seq_
        && md_update_action_ == other.md_update_action_
        && padding_7_ == other.padding_7_;
}

bool IncrementalRefreshVolumeLongGroup::operator!=(const IncrementalRefreshVolumeLongGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshVolumeLongGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
