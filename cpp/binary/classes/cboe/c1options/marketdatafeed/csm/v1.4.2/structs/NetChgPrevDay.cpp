#include "NetChgPrevDay.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

NetChgPrevDay::NetChgPrevDay(std::int8_t net_chg_prev_day_exponent, std::int32_t net_chg_prev_day_mantissa)
  : net_chg_prev_day_exponent_(net_chg_prev_day_exponent), net_chg_prev_day_mantissa_(net_chg_prev_day_mantissa) {}

std::int8_t NetChgPrevDay::net_chg_prev_day_exponent() const { return net_chg_prev_day_exponent_; }
void NetChgPrevDay::set_net_chg_prev_day_exponent(std::int8_t value) { net_chg_prev_day_exponent_ = value; }

std::int32_t NetChgPrevDay::net_chg_prev_day_mantissa() const { return net_chg_prev_day_mantissa_; }
void NetChgPrevDay::set_net_chg_prev_day_mantissa(std::int32_t value) { net_chg_prev_day_mantissa_ = value; }

std::size_t NetChgPrevDay::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NetChgPrevDay", wire_size, length);

    net_chg_prev_day_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    net_chg_prev_day_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t NetChgPrevDay::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NetChgPrevDay", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(net_chg_prev_day_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(net_chg_prev_day_mantissa_));
    offset += 4;

    return offset;
}

std::size_t NetChgPrevDay::encoded_size() const {
    return wire_size;
}

void NetChgPrevDay::print(std::ostream& out) const {
    out << "NetChgPrevDay{";
    out << "net_chg_prev_day_exponent=";
    out << static_cast<int>(net_chg_prev_day_exponent_);
    out << ", net_chg_prev_day_mantissa=";
    out << net_chg_prev_day_mantissa_;
    out << '}';
}

bool NetChgPrevDay::operator==(const NetChgPrevDay& other) const {
    return net_chg_prev_day_exponent_ == other.net_chg_prev_day_exponent_
        && net_chg_prev_day_mantissa_ == other.net_chg_prev_day_mantissa_;
}

bool NetChgPrevDay::operator!=(const NetChgPrevDay& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NetChgPrevDay& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
