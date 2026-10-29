#include "FullRefreshHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

FullRefreshHeader::FullRefreshHeader(std::uint32_t last_seq_num, std::uint32_t last_symbol_seq_num)
  : last_seq_num_(last_seq_num), last_symbol_seq_num_(last_symbol_seq_num) {}

std::uint32_t FullRefreshHeader::last_seq_num() const { return last_seq_num_; }
void FullRefreshHeader::set_last_seq_num(std::uint32_t value) { last_seq_num_ = value; }

std::uint32_t FullRefreshHeader::last_symbol_seq_num() const { return last_symbol_seq_num_; }
void FullRefreshHeader::set_last_symbol_seq_num(std::uint32_t value) { last_symbol_seq_num_ = value; }

std::size_t FullRefreshHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FullRefreshHeader", wire_size, length);

    last_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    last_symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t FullRefreshHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FullRefreshHeader", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(last_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(last_symbol_seq_num_));
    offset += 4;

    return offset;
}

std::size_t FullRefreshHeader::encoded_size() const {
    return wire_size;
}

void FullRefreshHeader::print(std::ostream& out) const {
    out << "FullRefreshHeader{";
    out << "last_seq_num=";
    out << last_seq_num_;
    out << ", last_symbol_seq_num=";
    out << last_symbol_seq_num_;
    out << '}';
}

bool FullRefreshHeader::operator==(const FullRefreshHeader& other) const {
    return last_seq_num_ == other.last_seq_num_
        && last_symbol_seq_num_ == other.last_symbol_seq_num_;
}

bool FullRefreshHeader::operator!=(const FullRefreshHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FullRefreshHeader& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
