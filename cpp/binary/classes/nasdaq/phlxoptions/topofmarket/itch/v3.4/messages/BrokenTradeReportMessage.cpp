#include "BrokenTradeReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

BrokenTradeReportMessage::BrokenTradeReportMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, std::uint32_t original_cross_id, Decimal original_price, std::uint32_t original_volume)
  : nanoseconds_(nanoseconds), option_id_(option_id), original_cross_id_(original_cross_id), original_price_(original_price), original_volume_(original_volume) {}

std::chrono::nanoseconds BrokenTradeReportMessage::nanoseconds() const { return nanoseconds_; }
void BrokenTradeReportMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t BrokenTradeReportMessage::option_id() const { return option_id_; }
void BrokenTradeReportMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

std::uint32_t BrokenTradeReportMessage::original_cross_id() const { return original_cross_id_; }
void BrokenTradeReportMessage::set_original_cross_id(std::uint32_t value) { original_cross_id_ = value; }

Decimal BrokenTradeReportMessage::original_price() const { return original_price_; }
void BrokenTradeReportMessage::set_original_price(Decimal value) { original_price_ = value; }

std::uint32_t BrokenTradeReportMessage::original_volume() const { return original_volume_; }
void BrokenTradeReportMessage::set_original_volume(std::uint32_t value) { original_volume_ = value; }

SequencedMessageCode BrokenTradeReportMessage::type() const { return message_type; }

std::string_view BrokenTradeReportMessage::name() const { return "Broken Trade Report Message"; }

std::size_t BrokenTradeReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BrokenTradeReportMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    original_cross_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    original_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    original_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t BrokenTradeReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BrokenTradeReportMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_cross_id_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(original_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_volume_));
    offset += 4;

    return offset;
}

std::size_t BrokenTradeReportMessage::encoded_size() const {
    return wire_size;
}

void BrokenTradeReportMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> BrokenTradeReportMessage::clone() const {
    return std::make_unique<BrokenTradeReportMessage>(*this);
}

void BrokenTradeReportMessage::print(std::ostream& out) const {
    out << "BrokenTradeReportMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", original_cross_id=";
    out << original_cross_id_;
    out << ", original_price=";
    out << original_price_;
    out << ", original_volume=";
    out << original_volume_;
    out << '}';
}

bool BrokenTradeReportMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const BrokenTradeReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool BrokenTradeReportMessage::operator==(const BrokenTradeReportMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && original_cross_id_ == other.original_cross_id_
        && original_price_ == other.original_price_
        && original_volume_ == other.original_volume_;
}

bool BrokenTradeReportMessage::operator!=(const BrokenTradeReportMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
