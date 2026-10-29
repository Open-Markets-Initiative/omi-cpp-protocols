#include "SettlementValueMdEntry.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

SettlementValueMdEntry::SettlementValueMdEntry(MdEntryType md_entry_type, const MdEntryPx& md_entry_px)
  : md_entry_type_(md_entry_type), md_entry_px_(md_entry_px) {}

MdEntryType SettlementValueMdEntry::md_entry_type() const { return md_entry_type_; }
void SettlementValueMdEntry::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const MdEntryPx& SettlementValueMdEntry::md_entry_px() const { return md_entry_px_; }
MdEntryPx& SettlementValueMdEntry::md_entry_px() { return md_entry_px_; }
void SettlementValueMdEntry::set_md_entry_px(const MdEntryPx& value) { md_entry_px_ = value; }

std::size_t SettlementValueMdEntry::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SettlementValueMdEntry", wire_size, length);

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    offset += md_entry_px_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SettlementValueMdEntry::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SettlementValueMdEntry", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    offset += md_entry_px_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SettlementValueMdEntry::encoded_size() const {
    return wire_size;
}

void SettlementValueMdEntry::print(std::ostream& out) const {
    out << "SettlementValueMdEntry{";
    out << "md_entry_type=";
    out << md_entry_type_;
    out << ", md_entry_px=";
    md_entry_px_.print(out);
    out << '}';
}

bool SettlementValueMdEntry::operator==(const SettlementValueMdEntry& other) const {
    return md_entry_type_ == other.md_entry_type_
        && md_entry_px_ == other.md_entry_px_;
}

bool SettlementValueMdEntry::operator!=(const SettlementValueMdEntry& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SettlementValueMdEntry& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
