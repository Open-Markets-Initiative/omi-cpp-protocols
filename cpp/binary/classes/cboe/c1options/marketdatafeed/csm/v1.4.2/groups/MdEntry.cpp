#include "MdEntry.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

MdEntry::MdEntry(MdEntryType md_entry_type, const MdEntryPx& md_entry_px, std::uint32_t md_entry_size, MdVolumeType md_volume_type)
  : md_entry_type_(md_entry_type), md_entry_px_(md_entry_px), md_entry_size_(md_entry_size), md_volume_type_(md_volume_type) {}

MdEntryType MdEntry::md_entry_type() const { return md_entry_type_; }
void MdEntry::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const MdEntryPx& MdEntry::md_entry_px() const { return md_entry_px_; }
MdEntryPx& MdEntry::md_entry_px() { return md_entry_px_; }
void MdEntry::set_md_entry_px(const MdEntryPx& value) { md_entry_px_ = value; }

std::uint32_t MdEntry::md_entry_size() const { return md_entry_size_; }
void MdEntry::set_md_entry_size(std::uint32_t value) { md_entry_size_ = value; }

MdVolumeType MdEntry::md_volume_type() const { return md_volume_type_; }
void MdEntry::set_md_volume_type(MdVolumeType value) { md_volume_type_ = value; }

std::size_t MdEntry::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MdEntry", wire_size, length);

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    offset += md_entry_px_.decode(data + offset, length - offset);

    md_entry_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    md_volume_type_ = static_cast<MdVolumeType>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t MdEntry::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdEntry", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    offset += md_entry_px_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(md_entry_size_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_volume_type_));
    offset += 1;

    return offset;
}

std::size_t MdEntry::encoded_size() const {
    return wire_size;
}

void MdEntry::print(std::ostream& out) const {
    out << "MdEntry{";
    out << "md_entry_type=";
    out << md_entry_type_;
    out << ", md_entry_px=";
    md_entry_px_.print(out);
    out << ", md_entry_size=";
    out << md_entry_size_;
    out << ", md_volume_type=";
    out << md_volume_type_;
    out << '}';
}

bool MdEntry::operator==(const MdEntry& other) const {
    return md_entry_type_ == other.md_entry_type_
        && md_entry_px_ == other.md_entry_px_
        && md_entry_size_ == other.md_entry_size_
        && md_volume_type_ == other.md_volume_type_;
}

bool MdEntry::operator!=(const MdEntry& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MdEntry& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
