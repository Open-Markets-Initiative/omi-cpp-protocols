#include "FutureLeg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

FutureLeg::FutureLeg(std::int32_t leg_ratio, const std::string& leg_symbol)
  : leg_ratio_(leg_ratio), leg_symbol_(leg_symbol) {}

std::int32_t FutureLeg::leg_ratio() const { return leg_ratio_; }
void FutureLeg::set_leg_ratio(std::int32_t value) { leg_ratio_ = value; }

const std::string& FutureLeg::leg_symbol() const { return leg_symbol_; }
std::string& FutureLeg::leg_symbol() { return leg_symbol_; }
void FutureLeg::set_leg_symbol(const std::string& value) { leg_symbol_ = value; }

std::size_t FutureLeg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FutureLeg", wire_size, length);

    leg_ratio_ = wire::read_i32_le(data + offset);
    offset += 4;

    leg_symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    return offset;
}

std::size_t FutureLeg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FutureLeg", wire_size, capacity);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(leg_ratio_));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', leg_symbol_);
    offset += 6;

    return offset;
}

std::size_t FutureLeg::encoded_size() const {
    return wire_size;
}

void FutureLeg::print(std::ostream& out) const {
    out << "FutureLeg{";
    out << "leg_ratio=";
    out << leg_ratio_;
    out << ", leg_symbol=";
    print::text(out, leg_symbol_);
    out << '}';
}

bool FutureLeg::operator==(const FutureLeg& other) const {
    return leg_ratio_ == other.leg_ratio_
        && leg_symbol_ == other.leg_symbol_;
}

bool FutureLeg::operator!=(const FutureLeg& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FutureLeg& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
