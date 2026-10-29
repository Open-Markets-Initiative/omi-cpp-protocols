#include "ImpliedEventId.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

ImpliedEventId::ImpliedEventId(std::uint32_t event_id, std::uint16_t no_related_trades)
  : event_id_(event_id), no_related_trades_(no_related_trades) {}

std::uint32_t ImpliedEventId::event_id() const { return event_id_; }
void ImpliedEventId::set_event_id(std::uint32_t value) { event_id_ = value; }

std::uint16_t ImpliedEventId::no_related_trades() const { return no_related_trades_; }
void ImpliedEventId::set_no_related_trades(std::uint16_t value) { no_related_trades_ = value; }

std::size_t ImpliedEventId::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ImpliedEventId", wire_size, length);

    event_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    no_related_trades_ = wire::read_u16_le(data + offset);
    offset += 2;

    return offset;
}

std::size_t ImpliedEventId::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ImpliedEventId", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(event_id_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(no_related_trades_));
    offset += 2;

    return offset;
}

std::size_t ImpliedEventId::encoded_size() const {
    return wire_size;
}

void ImpliedEventId::print(std::ostream& out) const {
    out << "ImpliedEventId{";
    out << "event_id=";
    out << event_id_;
    out << ", no_related_trades=";
    out << no_related_trades_;
    out << '}';
}

bool ImpliedEventId::operator==(const ImpliedEventId& other) const {
    return event_id_ == other.event_id_
        && no_related_trades_ == other.no_related_trades_;
}

bool ImpliedEventId::operator!=(const ImpliedEventId& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ImpliedEventId& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
