#include "RecapUpdateMdEntry.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

RecapUpdateMdEntry::RecapUpdateMdEntry(MdEntryType md_entry_type, const MdEntryPx& md_entry_px, std::uint32_t md_entry_size)
  : md_entry_type_(md_entry_type), md_entry_px_(md_entry_px), md_entry_size_(md_entry_size) {}

MdEntryType RecapUpdateMdEntry::md_entry_type() const { return md_entry_type_; }
void RecapUpdateMdEntry::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const MdEntryPx& RecapUpdateMdEntry::md_entry_px() const { return md_entry_px_; }
MdEntryPx& RecapUpdateMdEntry::md_entry_px() { return md_entry_px_; }
void RecapUpdateMdEntry::set_md_entry_px(const MdEntryPx& value) { md_entry_px_ = value; }

std::uint32_t RecapUpdateMdEntry::md_entry_size() const { return md_entry_size_; }
void RecapUpdateMdEntry::set_md_entry_size(std::uint32_t value) { md_entry_size_ = value; }

std::size_t RecapUpdateMdEntry::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RecapUpdateMdEntry", wire_size, length);

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    offset += md_entry_px_.decode(data + offset, length - offset);

    md_entry_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t RecapUpdateMdEntry::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RecapUpdateMdEntry", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    offset += md_entry_px_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(md_entry_size_));
    offset += 4;

    return offset;
}

std::size_t RecapUpdateMdEntry::encoded_size() const {
    return wire_size;
}

void RecapUpdateMdEntry::print(std::ostream& out) const {
    out << "RecapUpdateMdEntry{";
    out << "md_entry_type=";
    out << md_entry_type_;
    out << ", md_entry_px=";
    md_entry_px_.print(out);
    out << ", md_entry_size=";
    out << md_entry_size_;
    out << '}';
}

bool RecapUpdateMdEntry::operator==(const RecapUpdateMdEntry& other) const {
    return md_entry_type_ == other.md_entry_type_
        && md_entry_px_ == other.md_entry_px_
        && md_entry_size_ == other.md_entry_size_;
}

bool RecapUpdateMdEntry::operator!=(const RecapUpdateMdEntry& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RecapUpdateMdEntry& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
