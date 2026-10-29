#include "FilePayloadNetOrderImbalanceIndicatorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

FilePayloadNetOrderImbalanceIndicatorMessage::FilePayloadNetOrderImbalanceIndicatorMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t paired_shares, std::uint64_t imbalance_shares, ImbalanceDirection imbalance_direction, const std::string& stock, Decimal far_price, Decimal near_price, Decimal current_reference_price, CrossType cross_type, PriceVariationIndicator price_variation_indicator)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), paired_shares_(paired_shares), imbalance_shares_(imbalance_shares), imbalance_direction_(imbalance_direction), stock_(stock), far_price_(far_price), near_price_(near_price), current_reference_price_(current_reference_price), cross_type_(cross_type), price_variation_indicator_(price_variation_indicator) {}

std::uint16_t FilePayloadNetOrderImbalanceIndicatorMessage::stock_locate() const { return stock_locate_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t FilePayloadNetOrderImbalanceIndicatorMessage::tracking_number() const { return tracking_number_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds FilePayloadNetOrderImbalanceIndicatorMessage::timestamp() const { return timestamp_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t FilePayloadNetOrderImbalanceIndicatorMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t FilePayloadNetOrderImbalanceIndicatorMessage::paired_shares() const { return paired_shares_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_paired_shares(std::uint64_t value) { paired_shares_ = value; }

std::uint64_t FilePayloadNetOrderImbalanceIndicatorMessage::imbalance_shares() const { return imbalance_shares_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_imbalance_shares(std::uint64_t value) { imbalance_shares_ = value; }

ImbalanceDirection FilePayloadNetOrderImbalanceIndicatorMessage::imbalance_direction() const { return imbalance_direction_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_imbalance_direction(ImbalanceDirection value) { imbalance_direction_ = value; }

const std::string& FilePayloadNetOrderImbalanceIndicatorMessage::stock() const { return stock_; }
std::string& FilePayloadNetOrderImbalanceIndicatorMessage::stock() { return stock_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_stock(const std::string& value) { stock_ = value; }

Decimal FilePayloadNetOrderImbalanceIndicatorMessage::far_price() const { return far_price_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_far_price(Decimal value) { far_price_ = value; }

Decimal FilePayloadNetOrderImbalanceIndicatorMessage::near_price() const { return near_price_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_near_price(Decimal value) { near_price_ = value; }

Decimal FilePayloadNetOrderImbalanceIndicatorMessage::current_reference_price() const { return current_reference_price_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_current_reference_price(Decimal value) { current_reference_price_ = value; }

CrossType FilePayloadNetOrderImbalanceIndicatorMessage::cross_type() const { return cross_type_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_cross_type(CrossType value) { cross_type_ = value; }

PriceVariationIndicator FilePayloadNetOrderImbalanceIndicatorMessage::price_variation_indicator() const { return price_variation_indicator_; }
void FilePayloadNetOrderImbalanceIndicatorMessage::set_price_variation_indicator(PriceVariationIndicator value) { price_variation_indicator_ = value; }

FileMessageCode FilePayloadNetOrderImbalanceIndicatorMessage::type() const { return message_type; }

std::string_view FilePayloadNetOrderImbalanceIndicatorMessage::name() const { return "Net Order Imbalance Indicator Message"; }

std::size_t FilePayloadNetOrderImbalanceIndicatorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FilePayloadNetOrderImbalanceIndicatorMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    paired_shares_ = wire::read_u64_be(data + offset);
    offset += 8;

    imbalance_shares_ = wire::read_u64_be(data + offset);
    offset += 8;

    imbalance_direction_ = static_cast<ImbalanceDirection>(wire::read_char(data + offset));
    offset += 1;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    far_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    near_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    current_reference_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    price_variation_indicator_ = static_cast<PriceVariationIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t FilePayloadNetOrderImbalanceIndicatorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FilePayloadNetOrderImbalanceIndicatorMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(paired_shares_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(imbalance_shares_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(imbalance_direction_));
    offset += 1;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(far_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(near_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(current_reference_price_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(price_variation_indicator_));
    offset += 1;

    return offset;
}

std::size_t FilePayloadNetOrderImbalanceIndicatorMessage::encoded_size() const {
    return wire_size;
}

void FilePayloadNetOrderImbalanceIndicatorMessage::accept(FileMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<FileMessage> FilePayloadNetOrderImbalanceIndicatorMessage::clone() const {
    return std::make_unique<FilePayloadNetOrderImbalanceIndicatorMessage>(*this);
}

void FilePayloadNetOrderImbalanceIndicatorMessage::print(std::ostream& out) const {
    out << "FilePayloadNetOrderImbalanceIndicatorMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", paired_shares=";
    out << paired_shares_;
    out << ", imbalance_shares=";
    out << imbalance_shares_;
    out << ", imbalance_direction=";
    out << imbalance_direction_;
    out << ", stock=";
    print::text(out, stock_);
    out << ", far_price=";
    out << far_price_;
    out << ", near_price=";
    out << near_price_;
    out << ", current_reference_price=";
    out << current_reference_price_;
    out << ", cross_type=";
    out << cross_type_;
    out << ", price_variation_indicator=";
    out << price_variation_indicator_;
    out << '}';
}

bool FilePayloadNetOrderImbalanceIndicatorMessage::equals(const FileMessage& other) const {
    const auto* that = dynamic_cast<const FilePayloadNetOrderImbalanceIndicatorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FilePayloadNetOrderImbalanceIndicatorMessage::operator==(const FilePayloadNetOrderImbalanceIndicatorMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && paired_shares_ == other.paired_shares_
        && imbalance_shares_ == other.imbalance_shares_
        && imbalance_direction_ == other.imbalance_direction_
        && stock_ == other.stock_
        && far_price_ == other.far_price_
        && near_price_ == other.near_price_
        && current_reference_price_ == other.current_reference_price_
        && cross_type_ == other.cross_type_
        && price_variation_indicator_ == other.price_variation_indicator_;
}

bool FilePayloadNetOrderImbalanceIndicatorMessage::operator!=(const FilePayloadNetOrderImbalanceIndicatorMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
