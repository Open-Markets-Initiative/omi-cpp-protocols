#include "PartialOrderExecutionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

PartialOrderExecutionMessage::PartialOrderExecutionMessage(Side side, const std::array<std::byte, 7>& pad_7, Decimal price, std::chrono::nanoseconds trd_reg_ts_time_priority, std::int64_t security_id, std::uint32_t trd_match_id, const std::array<std::byte, 4>& pad_4, std::int64_t last_qty, Decimal last_px)
  : side_(side), pad_7_(pad_7), price_(price), trd_reg_ts_time_priority_(trd_reg_ts_time_priority), security_id_(security_id), trd_match_id_(trd_match_id), pad_4_(pad_4), last_qty_(last_qty), last_px_(last_px) {}

Side PartialOrderExecutionMessage::side() const { return side_; }
void PartialOrderExecutionMessage::set_side(Side value) { side_ = value; }

const std::array<std::byte, 7>& PartialOrderExecutionMessage::pad_7() const { return pad_7_; }
std::array<std::byte, 7>& PartialOrderExecutionMessage::pad_7() { return pad_7_; }
void PartialOrderExecutionMessage::set_pad_7(const std::array<std::byte, 7>& value) { pad_7_ = value; }

Decimal PartialOrderExecutionMessage::price() const { return price_; }
void PartialOrderExecutionMessage::set_price(Decimal value) { price_ = value; }

std::chrono::nanoseconds PartialOrderExecutionMessage::trd_reg_ts_time_priority() const { return trd_reg_ts_time_priority_; }
void PartialOrderExecutionMessage::set_trd_reg_ts_time_priority(std::chrono::nanoseconds value) { trd_reg_ts_time_priority_ = value; }

std::int64_t PartialOrderExecutionMessage::security_id() const { return security_id_; }
void PartialOrderExecutionMessage::set_security_id(std::int64_t value) { security_id_ = value; }

std::uint32_t PartialOrderExecutionMessage::trd_match_id() const { return trd_match_id_; }
void PartialOrderExecutionMessage::set_trd_match_id(std::uint32_t value) { trd_match_id_ = value; }

const std::array<std::byte, 4>& PartialOrderExecutionMessage::pad_4() const { return pad_4_; }
std::array<std::byte, 4>& PartialOrderExecutionMessage::pad_4() { return pad_4_; }
void PartialOrderExecutionMessage::set_pad_4(const std::array<std::byte, 4>& value) { pad_4_ = value; }

std::int64_t PartialOrderExecutionMessage::last_qty() const { return last_qty_; }
void PartialOrderExecutionMessage::set_last_qty(std::int64_t value) { last_qty_ = value; }

Decimal PartialOrderExecutionMessage::last_px() const { return last_px_; }
void PartialOrderExecutionMessage::set_last_px(Decimal value) { last_px_ = value; }

MessageCode PartialOrderExecutionMessage::type() const { return message_type; }

std::string_view PartialOrderExecutionMessage::name() const { return "Partial Order Execution Message"; }

std::size_t PartialOrderExecutionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PartialOrderExecutionMessage", wire_size, length);

    side_ = static_cast<Side>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, pad_7_.data(), 7);
    offset += 7;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    trd_reg_ts_time_priority_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    trd_match_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, pad_4_.data(), 4);
    offset += 4;

    last_qty_ = wire::read_i64_le(data + offset);
    offset += 8;

    last_px_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t PartialOrderExecutionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PartialOrderExecutionMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(side_));
    offset += 1;

    wire::write_bytes(data + offset, pad_7_.data(), 7);
    offset += 7;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trd_reg_ts_time_priority_.count()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trd_match_id_));
    offset += 4;

    wire::write_bytes(data + offset, pad_4_.data(), 4);
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(last_qty_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(last_px_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t PartialOrderExecutionMessage::encoded_size() const {
    return wire_size;
}

void PartialOrderExecutionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PartialOrderExecutionMessage::clone() const {
    return std::make_unique<PartialOrderExecutionMessage>(*this);
}

void PartialOrderExecutionMessage::print(std::ostream& out) const {
    out << "PartialOrderExecutionMessage{";
    out << "side=";
    out << side_;
    out << ", pad_7=";
    print::hex(out, pad_7_.data(), pad_7_.size());
    out << ", price=";
    out << price_;
    out << ", trd_reg_ts_time_priority=";
    out << trd_reg_ts_time_priority_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", trd_match_id=";
    out << trd_match_id_;
    out << ", pad_4=";
    print::hex(out, pad_4_.data(), pad_4_.size());
    out << ", last_qty=";
    out << last_qty_;
    out << ", last_px=";
    out << last_px_;
    out << '}';
}

bool PartialOrderExecutionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PartialOrderExecutionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PartialOrderExecutionMessage::operator==(const PartialOrderExecutionMessage& other) const {
    return side_ == other.side_
        && pad_7_ == other.pad_7_
        && price_ == other.price_
        && trd_reg_ts_time_priority_ == other.trd_reg_ts_time_priority_
        && security_id_ == other.security_id_
        && trd_match_id_ == other.trd_match_id_
        && pad_4_ == other.pad_4_
        && last_qty_ == other.last_qty_
        && last_px_ == other.last_px_;
}

bool PartialOrderExecutionMessage::operator!=(const PartialOrderExecutionMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
