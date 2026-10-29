#include "OptionsImbalanceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

OptionsImbalanceMessage::OptionsImbalanceMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, const std::array<std::byte, 4>& reserved_4, std::uint32_t paired_qty, std::uint32_t total_imbalance_qty, std::uint32_t market_imbalance_qty, const std::array<std::byte, 2>& reserved_2, AuctionType auction_type, ImbalanceSide imbalance_side, std::int32_t continuous_book_clearing_price, std::int32_t auction_interest_clearing_price, const std::array<std::byte, 4>& second_reserved_4, std::int32_t indicative_match_price, std::int32_t upper_collar, std::int32_t lower_collar, AuctionStatus auction_status)
  : source_time_(source_time), source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), reserved_4_(reserved_4), paired_qty_(paired_qty), total_imbalance_qty_(total_imbalance_qty), market_imbalance_qty_(market_imbalance_qty), reserved_2_(reserved_2), auction_type_(auction_type), imbalance_side_(imbalance_side), continuous_book_clearing_price_(continuous_book_clearing_price), auction_interest_clearing_price_(auction_interest_clearing_price), second_reserved_4_(second_reserved_4), indicative_match_price_(indicative_match_price), upper_collar_(upper_collar), lower_collar_(lower_collar), auction_status_(auction_status) {}

std::uint32_t OptionsImbalanceMessage::source_time() const { return source_time_; }
void OptionsImbalanceMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t OptionsImbalanceMessage::source_time_ns() const { return source_time_ns_; }
void OptionsImbalanceMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsImbalanceMessage::series_index() const { return series_index_; }
void OptionsImbalanceMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsImbalanceMessage::series_seq_num() const { return series_seq_num_; }
void OptionsImbalanceMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

const std::array<std::byte, 4>& OptionsImbalanceMessage::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& OptionsImbalanceMessage::reserved_4() { return reserved_4_; }
void OptionsImbalanceMessage::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

std::uint32_t OptionsImbalanceMessage::paired_qty() const { return paired_qty_; }
void OptionsImbalanceMessage::set_paired_qty(std::uint32_t value) { paired_qty_ = value; }

std::uint32_t OptionsImbalanceMessage::total_imbalance_qty() const { return total_imbalance_qty_; }
void OptionsImbalanceMessage::set_total_imbalance_qty(std::uint32_t value) { total_imbalance_qty_ = value; }

std::uint32_t OptionsImbalanceMessage::market_imbalance_qty() const { return market_imbalance_qty_; }
void OptionsImbalanceMessage::set_market_imbalance_qty(std::uint32_t value) { market_imbalance_qty_ = value; }

const std::array<std::byte, 2>& OptionsImbalanceMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& OptionsImbalanceMessage::reserved_2() { return reserved_2_; }
void OptionsImbalanceMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

AuctionType OptionsImbalanceMessage::auction_type() const { return auction_type_; }
void OptionsImbalanceMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

ImbalanceSide OptionsImbalanceMessage::imbalance_side() const { return imbalance_side_; }
void OptionsImbalanceMessage::set_imbalance_side(ImbalanceSide value) { imbalance_side_ = value; }

std::int32_t OptionsImbalanceMessage::continuous_book_clearing_price() const { return continuous_book_clearing_price_; }
void OptionsImbalanceMessage::set_continuous_book_clearing_price(std::int32_t value) { continuous_book_clearing_price_ = value; }

std::int32_t OptionsImbalanceMessage::auction_interest_clearing_price() const { return auction_interest_clearing_price_; }
void OptionsImbalanceMessage::set_auction_interest_clearing_price(std::int32_t value) { auction_interest_clearing_price_ = value; }

const std::array<std::byte, 4>& OptionsImbalanceMessage::second_reserved_4() const { return second_reserved_4_; }
std::array<std::byte, 4>& OptionsImbalanceMessage::second_reserved_4() { return second_reserved_4_; }
void OptionsImbalanceMessage::set_second_reserved_4(const std::array<std::byte, 4>& value) { second_reserved_4_ = value; }

std::int32_t OptionsImbalanceMessage::indicative_match_price() const { return indicative_match_price_; }
void OptionsImbalanceMessage::set_indicative_match_price(std::int32_t value) { indicative_match_price_ = value; }

std::int32_t OptionsImbalanceMessage::upper_collar() const { return upper_collar_; }
void OptionsImbalanceMessage::set_upper_collar(std::int32_t value) { upper_collar_ = value; }

std::int32_t OptionsImbalanceMessage::lower_collar() const { return lower_collar_; }
void OptionsImbalanceMessage::set_lower_collar(std::int32_t value) { lower_collar_ = value; }

AuctionStatus OptionsImbalanceMessage::auction_status() const { return auction_status_; }
void OptionsImbalanceMessage::set_auction_status(AuctionStatus value) { auction_status_ = value; }

MessageCode OptionsImbalanceMessage::type() const { return message_type; }

std::string_view OptionsImbalanceMessage::name() const { return "Options Imbalance Message"; }

std::size_t OptionsImbalanceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsImbalanceMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    paired_qty_ = wire::read_u32_le(data + offset);
    offset += 4;

    total_imbalance_qty_ = wire::read_u32_le(data + offset);
    offset += 4;

    market_imbalance_qty_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    imbalance_side_ = static_cast<ImbalanceSide>(wire::read_char(data + offset));
    offset += 1;

    continuous_book_clearing_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    auction_interest_clearing_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, second_reserved_4_.data(), 4);
    offset += 4;

    indicative_match_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    upper_collar_ = wire::read_i32_le(data + offset);
    offset += 4;

    lower_collar_ = wire::read_i32_le(data + offset);
    offset += 4;

    auction_status_ = static_cast<AuctionStatus>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t OptionsImbalanceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsImbalanceMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_seq_num_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(paired_qty_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(total_imbalance_qty_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(market_imbalance_qty_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(imbalance_side_));
    offset += 1;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(continuous_book_clearing_price_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(auction_interest_clearing_price_));
    offset += 4;

    wire::write_bytes(data + offset, second_reserved_4_.data(), 4);
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(indicative_match_price_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(upper_collar_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(lower_collar_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(auction_status_));
    offset += 1;

    return offset;
}

std::size_t OptionsImbalanceMessage::encoded_size() const {
    return wire_size;
}

void OptionsImbalanceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsImbalanceMessage::clone() const {
    return std::make_unique<OptionsImbalanceMessage>(*this);
}

void OptionsImbalanceMessage::print(std::ostream& out) const {
    out << "OptionsImbalanceMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", series_seq_num=";
    out << series_seq_num_;
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", paired_qty=";
    out << paired_qty_;
    out << ", total_imbalance_qty=";
    out << total_imbalance_qty_;
    out << ", market_imbalance_qty=";
    out << market_imbalance_qty_;
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << ", auction_type=";
    out << auction_type_;
    out << ", imbalance_side=";
    out << imbalance_side_;
    out << ", continuous_book_clearing_price=";
    out << continuous_book_clearing_price_;
    out << ", auction_interest_clearing_price=";
    out << auction_interest_clearing_price_;
    out << ", second_reserved_4=";
    print::hex(out, second_reserved_4_.data(), second_reserved_4_.size());
    out << ", indicative_match_price=";
    out << indicative_match_price_;
    out << ", upper_collar=";
    out << upper_collar_;
    out << ", lower_collar=";
    out << lower_collar_;
    out << ", auction_status=";
    out << auction_status_;
    out << '}';
}

bool OptionsImbalanceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsImbalanceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsImbalanceMessage::operator==(const OptionsImbalanceMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && reserved_4_ == other.reserved_4_
        && paired_qty_ == other.paired_qty_
        && total_imbalance_qty_ == other.total_imbalance_qty_
        && market_imbalance_qty_ == other.market_imbalance_qty_
        && reserved_2_ == other.reserved_2_
        && auction_type_ == other.auction_type_
        && imbalance_side_ == other.imbalance_side_
        && continuous_book_clearing_price_ == other.continuous_book_clearing_price_
        && auction_interest_clearing_price_ == other.auction_interest_clearing_price_
        && second_reserved_4_ == other.second_reserved_4_
        && indicative_match_price_ == other.indicative_match_price_
        && upper_collar_ == other.upper_collar_
        && lower_collar_ == other.lower_collar_
        && auction_status_ == other.auction_status_;
}

bool OptionsImbalanceMessage::operator!=(const OptionsImbalanceMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
