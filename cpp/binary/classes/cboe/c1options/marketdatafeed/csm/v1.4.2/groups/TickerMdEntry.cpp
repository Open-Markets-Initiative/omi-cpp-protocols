#include "TickerMdEntry.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

TickerMdEntry::TickerMdEntry(MdEntryType md_entry_type, const MdEntryPx& md_entry_px, std::uint32_t md_entry_size, const TradeCondition& trade_condition)
  : md_entry_type_(md_entry_type), md_entry_px_(md_entry_px), md_entry_size_(md_entry_size), trade_condition_(trade_condition) {}

MdEntryType TickerMdEntry::md_entry_type() const { return md_entry_type_; }
void TickerMdEntry::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const MdEntryPx& TickerMdEntry::md_entry_px() const { return md_entry_px_; }
MdEntryPx& TickerMdEntry::md_entry_px() { return md_entry_px_; }
void TickerMdEntry::set_md_entry_px(const MdEntryPx& value) { md_entry_px_ = value; }

std::uint32_t TickerMdEntry::md_entry_size() const { return md_entry_size_; }
void TickerMdEntry::set_md_entry_size(std::uint32_t value) { md_entry_size_ = value; }

const TradeCondition& TickerMdEntry::trade_condition() const { return trade_condition_; }
TradeCondition& TickerMdEntry::trade_condition() { return trade_condition_; }
void TickerMdEntry::set_trade_condition(const TradeCondition& value) { trade_condition_ = value; }

std::size_t TickerMdEntry::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("TickerMdEntry", offset + 1, length);
    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    offset += md_entry_px_.decode(data + offset, length - offset);

    wire::require("TickerMdEntry", offset + 4, length);
    md_entry_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += trade_condition_.decode(data + offset, length - offset);

    return offset;
}

std::size_t TickerMdEntry::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TickerMdEntry", encoded_size(), capacity);

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    offset += md_entry_px_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(md_entry_size_));
    offset += 4;

    offset += trade_condition_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t TickerMdEntry::encoded_size() const {
    return 1 + md_entry_px_.encoded_size() + 4 + trade_condition_.encoded_size();
}

void TickerMdEntry::print(std::ostream& out) const {
    out << "TickerMdEntry{";
    out << "md_entry_type=";
    out << md_entry_type_;
    out << ", md_entry_px=";
    md_entry_px_.print(out);
    out << ", md_entry_size=";
    out << md_entry_size_;
    out << ", trade_condition=";
    trade_condition_.print(out);
    out << '}';
}

bool TickerMdEntry::operator==(const TickerMdEntry& other) const {
    return md_entry_type_ == other.md_entry_type_
        && md_entry_px_ == other.md_entry_px_
        && md_entry_size_ == other.md_entry_size_
        && trade_condition_ == other.trade_condition_;
}

bool TickerMdEntry::operator!=(const TickerMdEntry& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const TickerMdEntry& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
