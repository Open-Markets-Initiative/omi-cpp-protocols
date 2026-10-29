#include "TransactionBegin.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

TransactionBegin::TransactionBegin(std::chrono::nanoseconds time_offset)
  : time_offset_(time_offset) {}

std::chrono::nanoseconds TransactionBegin::time_offset() const { return time_offset_; }
void TransactionBegin::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

MessageCode TransactionBegin::type() const { return message_type; }

std::string_view TransactionBegin::name() const { return "Transaction Begin"; }

std::size_t TransactionBegin::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TransactionBegin", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    return offset;
}

std::size_t TransactionBegin::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TransactionBegin", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    return offset;
}

std::size_t TransactionBegin::encoded_size() const {
    return wire_size;
}

void TransactionBegin::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TransactionBegin::clone() const {
    return std::make_unique<TransactionBegin>(*this);
}

void TransactionBegin::print(std::ostream& out) const {
    out << "TransactionBegin{";
    out << "time_offset=";
    out << time_offset_.count();
    out << '}';
}

bool TransactionBegin::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TransactionBegin*>(&other);
    return that != nullptr && *this == *that;
}

bool TransactionBegin::operator==(const TransactionBegin& other) const {
    return time_offset_ == other.time_offset_;
}

bool TransactionBegin::operator!=(const TransactionBegin& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
