#include "OhlcvMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

OhlcvMsg::OhlcvMsg(std::optional<Decimal> open, std::optional<Decimal> high, std::optional<Decimal> low, std::optional<Decimal> close, std::uint64_t volume)
  : open_(open), high_(high), low_(low), close_(close), volume_(volume) {}

std::optional<Decimal> OhlcvMsg::open() const { return open_; }
void OhlcvMsg::set_open(std::optional<Decimal> value) { open_ = value; }

std::optional<Decimal> OhlcvMsg::high() const { return high_; }
void OhlcvMsg::set_high(std::optional<Decimal> value) { high_ = value; }

std::optional<Decimal> OhlcvMsg::low() const { return low_; }
void OhlcvMsg::set_low(std::optional<Decimal> value) { low_ = value; }

std::optional<Decimal> OhlcvMsg::close() const { return close_; }
void OhlcvMsg::set_close(std::optional<Decimal> value) { close_ = value; }

std::uint64_t OhlcvMsg::volume() const { return volume_; }
void OhlcvMsg::set_volume(std::uint64_t value) { volume_ = value; }

MessageCode OhlcvMsg::type() const { return message_type; }

std::string_view OhlcvMsg::name() const { return "Ohlcv Msg"; }

std::size_t OhlcvMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OhlcvMsg", wire_size, length);

    open_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    high_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    low_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    close_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    volume_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t OhlcvMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OhlcvMsg", wire_size, capacity);

    wire::write_i64_le(data + offset, open_ ? static_cast<std::int64_t>(open_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, high_ ? static_cast<std::int64_t>(high_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_ ? static_cast<std::int64_t>(low_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, close_ ? static_cast<std::int64_t>(close_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(volume_));
    offset += 8;

    return offset;
}

std::size_t OhlcvMsg::encoded_size() const {
    return wire_size;
}

void OhlcvMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OhlcvMsg::clone() const {
    return std::make_unique<OhlcvMsg>(*this);
}

void OhlcvMsg::print(std::ostream& out) const {
    out << "OhlcvMsg{";
    out << "open=";
    print::optional(out, open_);
    out << ", high=";
    print::optional(out, high_);
    out << ", low=";
    print::optional(out, low_);
    out << ", close=";
    print::optional(out, close_);
    out << ", volume=";
    out << volume_;
    out << '}';
}

bool OhlcvMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OhlcvMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool OhlcvMsg::operator==(const OhlcvMsg& other) const {
    return open_ == other.open_
        && high_ == other.high_
        && low_ == other.low_
        && close_ == other.close_
        && volume_ == other.volume_;
}

bool OhlcvMsg::operator!=(const OhlcvMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v2
