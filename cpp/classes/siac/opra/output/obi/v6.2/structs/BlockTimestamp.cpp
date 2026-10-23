#include "BlockTimestamp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::opra::output::obi::v6_2 {

BlockTimestamp::BlockTimestamp(std::chrono::seconds seconds, std::chrono::nanoseconds nanoseconds)
  : seconds_(seconds), nanoseconds_(nanoseconds) {}

std::chrono::seconds BlockTimestamp::seconds() const { return seconds_; }
void BlockTimestamp::set_seconds(std::chrono::seconds value) { seconds_ = value; }

std::chrono::nanoseconds BlockTimestamp::nanoseconds() const { return nanoseconds_; }
void BlockTimestamp::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::size_t BlockTimestamp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BlockTimestamp", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t BlockTimestamp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BlockTimestamp", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    return offset;
}

std::size_t BlockTimestamp::encoded_size() const {
    return wire_size;
}

void BlockTimestamp::print(std::ostream& out) const {
    out << "BlockTimestamp{";
    out << "seconds=";
    out << seconds_.count();
    out << ", nanoseconds=";
    out << nanoseconds_.count();
    out << '}';
}

bool BlockTimestamp::operator==(const BlockTimestamp& other) const {
    return seconds_ == other.seconds_
        && nanoseconds_ == other.nanoseconds_;
}

bool BlockTimestamp::operator!=(const BlockTimestamp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BlockTimestamp& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
