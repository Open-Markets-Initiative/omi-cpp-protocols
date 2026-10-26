#include "IncrementalRefreshTradeSummaryOrderIdGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshTradeSummaryOrderIdGroup::IncrementalRefreshTradeSummaryOrderIdGroup(std::uint64_t order_id, std::int32_t last_qty, const std::array<std::byte, 4>& padding_4)
  : order_id_(order_id), last_qty_(last_qty), padding_4_(padding_4) {}

std::uint64_t IncrementalRefreshTradeSummaryOrderIdGroup::order_id() const { return order_id_; }
void IncrementalRefreshTradeSummaryOrderIdGroup::set_order_id(std::uint64_t value) { order_id_ = value; }

std::int32_t IncrementalRefreshTradeSummaryOrderIdGroup::last_qty() const { return last_qty_; }
void IncrementalRefreshTradeSummaryOrderIdGroup::set_last_qty(std::int32_t value) { last_qty_ = value; }

const std::array<std::byte, 4>& IncrementalRefreshTradeSummaryOrderIdGroup::padding_4() const { return padding_4_; }
std::array<std::byte, 4>& IncrementalRefreshTradeSummaryOrderIdGroup::padding_4() { return padding_4_; }
void IncrementalRefreshTradeSummaryOrderIdGroup::set_padding_4(const std::array<std::byte, 4>& value) { padding_4_ = value; }

std::size_t IncrementalRefreshTradeSummaryOrderIdGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshTradeSummaryOrderIdGroup", wire_size, length);

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    last_qty_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, padding_4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t IncrementalRefreshTradeSummaryOrderIdGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshTradeSummaryOrderIdGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(last_qty_));
    offset += 4;

    wire::write_bytes(data + offset, padding_4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t IncrementalRefreshTradeSummaryOrderIdGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshTradeSummaryOrderIdGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshTradeSummaryOrderIdGroup{";
    out << "order_id=";
    out << order_id_;
    out << ", last_qty=";
    out << last_qty_;
    out << ", padding_4=";
    print::hex(out, padding_4_.data(), padding_4_.size());
    out << '}';
}

bool IncrementalRefreshTradeSummaryOrderIdGroup::operator==(const IncrementalRefreshTradeSummaryOrderIdGroup& other) const {
    return order_id_ == other.order_id_
        && last_qty_ == other.last_qty_
        && padding_4_ == other.padding_4_;
}

bool IncrementalRefreshTradeSummaryOrderIdGroup::operator!=(const IncrementalRefreshTradeSummaryOrderIdGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryOrderIdGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
