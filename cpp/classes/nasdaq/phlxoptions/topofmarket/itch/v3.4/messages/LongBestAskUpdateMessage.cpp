#include "LongBestAskUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

LongBestAskUpdateMessage::LongBestAskUpdateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, QuoteCondition quote_condition, Decimal price_4, std::uint32_t size_4)
  : nanoseconds_(nanoseconds), option_id_(option_id), quote_condition_(quote_condition), price_4_(price_4), size_4_(size_4) {}

std::chrono::nanoseconds LongBestAskUpdateMessage::nanoseconds() const { return nanoseconds_; }
void LongBestAskUpdateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t LongBestAskUpdateMessage::option_id() const { return option_id_; }
void LongBestAskUpdateMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

QuoteCondition LongBestAskUpdateMessage::quote_condition() const { return quote_condition_; }
void LongBestAskUpdateMessage::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

Decimal LongBestAskUpdateMessage::price_4() const { return price_4_; }
void LongBestAskUpdateMessage::set_price_4(Decimal value) { price_4_ = value; }

std::uint32_t LongBestAskUpdateMessage::size_4() const { return size_4_; }
void LongBestAskUpdateMessage::set_size_4(std::uint32_t value) { size_4_ = value; }

SequencedMessageCode LongBestAskUpdateMessage::type() const { return message_type; }

std::string_view LongBestAskUpdateMessage::name() const { return "Long Best Ask Update Message"; }

std::size_t LongBestAskUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LongBestAskUpdateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    price_4_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    size_4_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t LongBestAskUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LongBestAskUpdateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(price_4_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(size_4_));
    offset += 4;

    return offset;
}

std::size_t LongBestAskUpdateMessage::encoded_size() const {
    return wire_size;
}

void LongBestAskUpdateMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> LongBestAskUpdateMessage::clone() const {
    return std::make_unique<LongBestAskUpdateMessage>(*this);
}

void LongBestAskUpdateMessage::print(std::ostream& out) const {
    out << "LongBestAskUpdateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", quote_condition=";
    out << quote_condition_;
    out << ", price_4=";
    out << price_4_;
    out << ", size_4=";
    out << size_4_;
    out << '}';
}

bool LongBestAskUpdateMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const LongBestAskUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LongBestAskUpdateMessage::operator==(const LongBestAskUpdateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && quote_condition_ == other.quote_condition_
        && price_4_ == other.price_4_
        && size_4_ == other.size_4_;
}

bool LongBestAskUpdateMessage::operator!=(const LongBestAskUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
