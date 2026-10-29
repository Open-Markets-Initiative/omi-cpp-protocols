#include "IndexValueMdEntry.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

IndexValueMdEntry::IndexValueMdEntry(MdEntryType md_entry_type, const MdEntryPx& md_entry_px)
  : md_entry_type_(md_entry_type), md_entry_px_(md_entry_px) {}

MdEntryType IndexValueMdEntry::md_entry_type() const { return md_entry_type_; }
void IndexValueMdEntry::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const MdEntryPx& IndexValueMdEntry::md_entry_px() const { return md_entry_px_; }
MdEntryPx& IndexValueMdEntry::md_entry_px() { return md_entry_px_; }
void IndexValueMdEntry::set_md_entry_px(const MdEntryPx& value) { md_entry_px_ = value; }

std::size_t IndexValueMdEntry::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IndexValueMdEntry", wire_size, length);

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    offset += md_entry_px_.decode(data + offset, length - offset);

    return offset;
}

std::size_t IndexValueMdEntry::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IndexValueMdEntry", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    offset += md_entry_px_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t IndexValueMdEntry::encoded_size() const {
    return wire_size;
}

void IndexValueMdEntry::print(std::ostream& out) const {
    out << "IndexValueMdEntry{";
    out << "md_entry_type=";
    out << md_entry_type_;
    out << ", md_entry_px=";
    md_entry_px_.print(out);
    out << '}';
}

bool IndexValueMdEntry::operator==(const IndexValueMdEntry& other) const {
    return md_entry_type_ == other.md_entry_type_
        && md_entry_px_ == other.md_entry_px_;
}

bool IndexValueMdEntry::operator!=(const IndexValueMdEntry& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IndexValueMdEntry& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
