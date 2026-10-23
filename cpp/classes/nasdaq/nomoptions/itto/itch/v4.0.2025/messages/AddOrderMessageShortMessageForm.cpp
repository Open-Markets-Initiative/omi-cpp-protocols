#include "AddOrderMessageShortMessageForm.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

AddOrderMessageShortMessageForm::AddOrderMessageShortMessageForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, MarketSide market_side, std::uint32_t option_id, Decimal price_short, std::uint16_t volume_short)
  : tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number), market_side_(market_side), option_id_(option_id), price_short_(price_short), volume_short_(volume_short) {}

std::uint16_t AddOrderMessageShortMessageForm::tracking_number() const { return tracking_number_; }
void AddOrderMessageShortMessageForm::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds AddOrderMessageShortMessageForm::timestamp() const { return timestamp_; }
void AddOrderMessageShortMessageForm::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t AddOrderMessageShortMessageForm::order_reference_number() const { return order_reference_number_; }
void AddOrderMessageShortMessageForm::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

MarketSide AddOrderMessageShortMessageForm::market_side() const { return market_side_; }
void AddOrderMessageShortMessageForm::set_market_side(MarketSide value) { market_side_ = value; }

std::uint32_t AddOrderMessageShortMessageForm::option_id() const { return option_id_; }
void AddOrderMessageShortMessageForm::set_option_id(std::uint32_t value) { option_id_ = value; }

Decimal AddOrderMessageShortMessageForm::price_short() const { return price_short_; }
void AddOrderMessageShortMessageForm::set_price_short(Decimal value) { price_short_ = value; }

std::uint16_t AddOrderMessageShortMessageForm::volume_short() const { return volume_short_; }
void AddOrderMessageShortMessageForm::set_volume_short(std::uint16_t value) { volume_short_ = value; }

SequencedMessageCode AddOrderMessageShortMessageForm::type() const { return message_type; }

std::string_view AddOrderMessageShortMessageForm::name() const { return "Add Order Message Short Message Form"; }

std::size_t AddOrderMessageShortMessageForm::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderMessageShortMessageForm", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    market_side_ = static_cast<MarketSide>(wire::read_char(data + offset));
    offset += 1;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -4);
    offset += 2;

    volume_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t AddOrderMessageShortMessageForm::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderMessageShortMessageForm", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(market_side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(volume_short_));
    offset += 2;

    return offset;
}

std::size_t AddOrderMessageShortMessageForm::encoded_size() const {
    return wire_size;
}

void AddOrderMessageShortMessageForm::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> AddOrderMessageShortMessageForm::clone() const {
    return std::make_unique<AddOrderMessageShortMessageForm>(*this);
}

void AddOrderMessageShortMessageForm::print(std::ostream& out) const {
    out << "AddOrderMessageShortMessageForm{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", market_side=";
    out << market_side_;
    out << ", option_id=";
    out << option_id_;
    out << ", price_short=";
    out << price_short_;
    out << ", volume_short=";
    out << volume_short_;
    out << '}';
}

bool AddOrderMessageShortMessageForm::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const AddOrderMessageShortMessageForm*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderMessageShortMessageForm::operator==(const AddOrderMessageShortMessageForm& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_
        && market_side_ == other.market_side_
        && option_id_ == other.option_id_
        && price_short_ == other.price_short_
        && volume_short_ == other.volume_short_;
}

bool AddOrderMessageShortMessageForm::operator!=(const AddOrderMessageShortMessageForm& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
