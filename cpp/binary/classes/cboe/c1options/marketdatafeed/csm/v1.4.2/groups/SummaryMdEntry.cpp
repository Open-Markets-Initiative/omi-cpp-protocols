#include "SummaryMdEntry.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

SummaryMdEntry::SummaryMdEntry(MdEntryType md_entry_type, const MdEntryPx& md_entry_px)
  : md_entry_type_(md_entry_type), md_entry_px_(md_entry_px) {}

MdEntryType SummaryMdEntry::md_entry_type() const { return md_entry_type_; }
void SummaryMdEntry::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const MdEntryPx& SummaryMdEntry::md_entry_px() const { return md_entry_px_; }
MdEntryPx& SummaryMdEntry::md_entry_px() { return md_entry_px_; }
void SummaryMdEntry::set_md_entry_px(const MdEntryPx& value) { md_entry_px_ = value; }

std::size_t SummaryMdEntry::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SummaryMdEntry", wire_size, length);

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    offset += md_entry_px_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SummaryMdEntry::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SummaryMdEntry", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    offset += md_entry_px_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SummaryMdEntry::encoded_size() const {
    return wire_size;
}

void SummaryMdEntry::print(std::ostream& out) const {
    out << "SummaryMdEntry{";
    out << "md_entry_type=";
    out << md_entry_type_;
    out << ", md_entry_px=";
    md_entry_px_.print(out);
    out << '}';
}

bool SummaryMdEntry::operator==(const SummaryMdEntry& other) const {
    return md_entry_type_ == other.md_entry_type_
        && md_entry_px_ == other.md_entry_px_;
}

bool SummaryMdEntry::operator!=(const SummaryMdEntry& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SummaryMdEntry& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
