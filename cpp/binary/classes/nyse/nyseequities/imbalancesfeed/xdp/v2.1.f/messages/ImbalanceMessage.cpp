#include "ImbalanceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

ImbalanceMessage::ImbalanceMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t reference_price, std::uint32_t paired_qty, std::uint32_t total_imbalance_qty, std::uint32_t market_imbalance_qty, std::uint16_t auction_time, AuctionType auction_type, ImbalanceSide imbalance_side, std::uint32_t continuous_book_clearing_price, std::uint32_t closing_only_clearing_price, std::uint32_t ssr_filing_price, std::uint32_t indicative_match_price, std::uint32_t upper_collar, std::uint32_t lower_collar, AuctionStatus auction_status, FreezeStatus freeze_status, std::uint8_t num_extensions)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), reference_price_(reference_price), paired_qty_(paired_qty), total_imbalance_qty_(total_imbalance_qty), market_imbalance_qty_(market_imbalance_qty), auction_time_(auction_time), auction_type_(auction_type), imbalance_side_(imbalance_side), continuous_book_clearing_price_(continuous_book_clearing_price), closing_only_clearing_price_(closing_only_clearing_price), ssr_filing_price_(ssr_filing_price), indicative_match_price_(indicative_match_price), upper_collar_(upper_collar), lower_collar_(lower_collar), auction_status_(auction_status), freeze_status_(freeze_status), num_extensions_(num_extensions) {}

std::uint32_t ImbalanceMessage::source_time() const { return source_time_; }
void ImbalanceMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t ImbalanceMessage::source_time_ns() const { return source_time_ns_; }
void ImbalanceMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t ImbalanceMessage::symbol_index() const { return symbol_index_; }
void ImbalanceMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t ImbalanceMessage::symbol_seq_num() const { return symbol_seq_num_; }
void ImbalanceMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t ImbalanceMessage::reference_price() const { return reference_price_; }
void ImbalanceMessage::set_reference_price(std::uint32_t value) { reference_price_ = value; }

std::uint32_t ImbalanceMessage::paired_qty() const { return paired_qty_; }
void ImbalanceMessage::set_paired_qty(std::uint32_t value) { paired_qty_ = value; }

std::uint32_t ImbalanceMessage::total_imbalance_qty() const { return total_imbalance_qty_; }
void ImbalanceMessage::set_total_imbalance_qty(std::uint32_t value) { total_imbalance_qty_ = value; }

std::uint32_t ImbalanceMessage::market_imbalance_qty() const { return market_imbalance_qty_; }
void ImbalanceMessage::set_market_imbalance_qty(std::uint32_t value) { market_imbalance_qty_ = value; }

std::uint16_t ImbalanceMessage::auction_time() const { return auction_time_; }
void ImbalanceMessage::set_auction_time(std::uint16_t value) { auction_time_ = value; }

AuctionType ImbalanceMessage::auction_type() const { return auction_type_; }
void ImbalanceMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

ImbalanceSide ImbalanceMessage::imbalance_side() const { return imbalance_side_; }
void ImbalanceMessage::set_imbalance_side(ImbalanceSide value) { imbalance_side_ = value; }

std::uint32_t ImbalanceMessage::continuous_book_clearing_price() const { return continuous_book_clearing_price_; }
void ImbalanceMessage::set_continuous_book_clearing_price(std::uint32_t value) { continuous_book_clearing_price_ = value; }

std::uint32_t ImbalanceMessage::closing_only_clearing_price() const { return closing_only_clearing_price_; }
void ImbalanceMessage::set_closing_only_clearing_price(std::uint32_t value) { closing_only_clearing_price_ = value; }

std::uint32_t ImbalanceMessage::ssr_filing_price() const { return ssr_filing_price_; }
void ImbalanceMessage::set_ssr_filing_price(std::uint32_t value) { ssr_filing_price_ = value; }

std::uint32_t ImbalanceMessage::indicative_match_price() const { return indicative_match_price_; }
void ImbalanceMessage::set_indicative_match_price(std::uint32_t value) { indicative_match_price_ = value; }

std::uint32_t ImbalanceMessage::upper_collar() const { return upper_collar_; }
void ImbalanceMessage::set_upper_collar(std::uint32_t value) { upper_collar_ = value; }

std::uint32_t ImbalanceMessage::lower_collar() const { return lower_collar_; }
void ImbalanceMessage::set_lower_collar(std::uint32_t value) { lower_collar_ = value; }

AuctionStatus ImbalanceMessage::auction_status() const { return auction_status_; }
void ImbalanceMessage::set_auction_status(AuctionStatus value) { auction_status_ = value; }

FreezeStatus ImbalanceMessage::freeze_status() const { return freeze_status_; }
void ImbalanceMessage::set_freeze_status(FreezeStatus value) { freeze_status_ = value; }

std::uint8_t ImbalanceMessage::num_extensions() const { return num_extensions_; }
void ImbalanceMessage::set_num_extensions(std::uint8_t value) { num_extensions_ = value; }

MessageCode ImbalanceMessage::type() const { return message_type; }

std::string_view ImbalanceMessage::name() const { return "Imbalance Message"; }

std::size_t ImbalanceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ImbalanceMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    reference_price_ = wire::read_u32_le(data + offset);
    offset += 4;

    paired_qty_ = wire::read_u32_le(data + offset);
    offset += 4;

    total_imbalance_qty_ = wire::read_u32_le(data + offset);
    offset += 4;

    market_imbalance_qty_ = wire::read_u32_le(data + offset);
    offset += 4;

    auction_time_ = wire::read_u16_le(data + offset);
    offset += 2;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    imbalance_side_ = static_cast<ImbalanceSide>(wire::read_char(data + offset));
    offset += 1;

    continuous_book_clearing_price_ = wire::read_u32_le(data + offset);
    offset += 4;

    closing_only_clearing_price_ = wire::read_u32_le(data + offset);
    offset += 4;

    ssr_filing_price_ = wire::read_u32_le(data + offset);
    offset += 4;

    indicative_match_price_ = wire::read_u32_le(data + offset);
    offset += 4;

    upper_collar_ = wire::read_u32_le(data + offset);
    offset += 4;

    lower_collar_ = wire::read_u32_le(data + offset);
    offset += 4;

    auction_status_ = static_cast<AuctionStatus>(wire::read_u8(data + offset));
    offset += 1;

    freeze_status_ = static_cast<FreezeStatus>(wire::read_u8(data + offset));
    offset += 1;

    num_extensions_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t ImbalanceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ImbalanceMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(reference_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(paired_qty_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(total_imbalance_qty_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(market_imbalance_qty_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(auction_time_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(imbalance_side_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(continuous_book_clearing_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(closing_only_clearing_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ssr_filing_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(indicative_match_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(upper_collar_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(lower_collar_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(auction_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(freeze_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(num_extensions_));
    offset += 1;

    return offset;
}

std::size_t ImbalanceMessage::encoded_size() const {
    return wire_size;
}

void ImbalanceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ImbalanceMessage::clone() const {
    return std::make_unique<ImbalanceMessage>(*this);
}

void ImbalanceMessage::print(std::ostream& out) const {
    out << "ImbalanceMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", reference_price=";
    out << reference_price_;
    out << ", paired_qty=";
    out << paired_qty_;
    out << ", total_imbalance_qty=";
    out << total_imbalance_qty_;
    out << ", market_imbalance_qty=";
    out << market_imbalance_qty_;
    out << ", auction_time=";
    out << auction_time_;
    out << ", auction_type=";
    out << auction_type_;
    out << ", imbalance_side=";
    out << imbalance_side_;
    out << ", continuous_book_clearing_price=";
    out << continuous_book_clearing_price_;
    out << ", closing_only_clearing_price=";
    out << closing_only_clearing_price_;
    out << ", ssr_filing_price=";
    out << ssr_filing_price_;
    out << ", indicative_match_price=";
    out << indicative_match_price_;
    out << ", upper_collar=";
    out << upper_collar_;
    out << ", lower_collar=";
    out << lower_collar_;
    out << ", auction_status=";
    out << auction_status_;
    out << ", freeze_status=";
    out << freeze_status_;
    out << ", num_extensions=";
    out << static_cast<int>(num_extensions_);
    out << '}';
}

bool ImbalanceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ImbalanceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ImbalanceMessage::operator==(const ImbalanceMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && reference_price_ == other.reference_price_
        && paired_qty_ == other.paired_qty_
        && total_imbalance_qty_ == other.total_imbalance_qty_
        && market_imbalance_qty_ == other.market_imbalance_qty_
        && auction_time_ == other.auction_time_
        && auction_type_ == other.auction_type_
        && imbalance_side_ == other.imbalance_side_
        && continuous_book_clearing_price_ == other.continuous_book_clearing_price_
        && closing_only_clearing_price_ == other.closing_only_clearing_price_
        && ssr_filing_price_ == other.ssr_filing_price_
        && indicative_match_price_ == other.indicative_match_price_
        && upper_collar_ == other.upper_collar_
        && lower_collar_ == other.lower_collar_
        && auction_status_ == other.auction_status_
        && freeze_status_ == other.freeze_status_
        && num_extensions_ == other.num_extensions_;
}

bool ImbalanceMessage::operator!=(const ImbalanceMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f
