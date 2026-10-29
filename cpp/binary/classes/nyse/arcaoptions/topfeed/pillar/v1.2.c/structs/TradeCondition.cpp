#include "TradeCondition.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

TradeCondition::TradeCondition(Series series, Opening opening, const std::array<std::byte, 1>& reserved_1, char offical)
  : series_(series), opening_(opening), reserved_1_(reserved_1), offical_(offical) {}

Series TradeCondition::series() const { return series_; }
void TradeCondition::set_series(Series value) { series_ = value; }

Opening TradeCondition::opening() const { return opening_; }
void TradeCondition::set_opening(Opening value) { opening_ = value; }

const std::array<std::byte, 1>& TradeCondition::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& TradeCondition::reserved_1() { return reserved_1_; }
void TradeCondition::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

char TradeCondition::offical() const { return offical_; }
void TradeCondition::set_offical(char value) { offical_ = value; }

std::size_t TradeCondition::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCondition", wire_size, length);

    series_ = static_cast<Series>(wire::read_char(data + offset));
    offset += 1;

    opening_ = static_cast<Opening>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    offical_ = wire::read_char(data + offset);
    offset += 1;

    return offset;
}

std::size_t TradeCondition::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCondition", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(series_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(opening_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, offical_);
    offset += 1;

    return offset;
}

std::size_t TradeCondition::encoded_size() const {
    return wire_size;
}

void TradeCondition::print(std::ostream& out) const {
    out << "TradeCondition{";
    out << "series=";
    out << series_;
    out << ", opening=";
    out << opening_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", offical=";
    print::character(out, offical_);
    out << '}';
}

bool TradeCondition::operator==(const TradeCondition& other) const {
    return series_ == other.series_
        && opening_ == other.opening_
        && reserved_1_ == other.reserved_1_
        && offical_ == other.offical_;
}

bool TradeCondition::operator!=(const TradeCondition& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const TradeCondition& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
