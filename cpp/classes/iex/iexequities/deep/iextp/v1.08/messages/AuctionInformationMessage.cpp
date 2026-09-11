#include "AuctionInformationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

AuctionInformationMessage::AuctionInformationMessage(AuctionType auction_type, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t paired_shares, Decimal reference_price, Decimal indicative_clearing_price, std::uint32_t imbalance_shares, ImbalanceSide imbalance_side, char extension_number, std::chrono::seconds scheduled_auction_time, Decimal auction_book_clearing_price, Decimal collar_reference_price, Decimal lower_auction_collar, Decimal upper_auction_collar)
  : auction_type_(auction_type), timestamp_(timestamp), symbol_(symbol), paired_shares_(paired_shares), reference_price_(reference_price), indicative_clearing_price_(indicative_clearing_price), imbalance_shares_(imbalance_shares), imbalance_side_(imbalance_side), extension_number_(extension_number), scheduled_auction_time_(scheduled_auction_time), auction_book_clearing_price_(auction_book_clearing_price), collar_reference_price_(collar_reference_price), lower_auction_collar_(lower_auction_collar), upper_auction_collar_(upper_auction_collar) {}

AuctionType AuctionInformationMessage::auction_type() const { return auction_type_; }
void AuctionInformationMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

std::chrono::nanoseconds AuctionInformationMessage::timestamp() const { return timestamp_; }
void AuctionInformationMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& AuctionInformationMessage::symbol() const { return symbol_; }
std::string& AuctionInformationMessage::symbol() { return symbol_; }
void AuctionInformationMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t AuctionInformationMessage::paired_shares() const { return paired_shares_; }
void AuctionInformationMessage::set_paired_shares(std::uint32_t value) { paired_shares_ = value; }

Decimal AuctionInformationMessage::reference_price() const { return reference_price_; }
void AuctionInformationMessage::set_reference_price(Decimal value) { reference_price_ = value; }

Decimal AuctionInformationMessage::indicative_clearing_price() const { return indicative_clearing_price_; }
void AuctionInformationMessage::set_indicative_clearing_price(Decimal value) { indicative_clearing_price_ = value; }

std::uint32_t AuctionInformationMessage::imbalance_shares() const { return imbalance_shares_; }
void AuctionInformationMessage::set_imbalance_shares(std::uint32_t value) { imbalance_shares_ = value; }

ImbalanceSide AuctionInformationMessage::imbalance_side() const { return imbalance_side_; }
void AuctionInformationMessage::set_imbalance_side(ImbalanceSide value) { imbalance_side_ = value; }

char AuctionInformationMessage::extension_number() const { return extension_number_; }
void AuctionInformationMessage::set_extension_number(char value) { extension_number_ = value; }

std::chrono::seconds AuctionInformationMessage::scheduled_auction_time() const { return scheduled_auction_time_; }
void AuctionInformationMessage::set_scheduled_auction_time(std::chrono::seconds value) { scheduled_auction_time_ = value; }

Decimal AuctionInformationMessage::auction_book_clearing_price() const { return auction_book_clearing_price_; }
void AuctionInformationMessage::set_auction_book_clearing_price(Decimal value) { auction_book_clearing_price_ = value; }

Decimal AuctionInformationMessage::collar_reference_price() const { return collar_reference_price_; }
void AuctionInformationMessage::set_collar_reference_price(Decimal value) { collar_reference_price_ = value; }

Decimal AuctionInformationMessage::lower_auction_collar() const { return lower_auction_collar_; }
void AuctionInformationMessage::set_lower_auction_collar(Decimal value) { lower_auction_collar_ = value; }

Decimal AuctionInformationMessage::upper_auction_collar() const { return upper_auction_collar_; }
void AuctionInformationMessage::set_upper_auction_collar(Decimal value) { upper_auction_collar_ = value; }

MessageCode AuctionInformationMessage::type() const { return message_type; }

std::string_view AuctionInformationMessage::name() const { return "Auction Information Message"; }

std::size_t AuctionInformationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionInformationMessage", wire_size, length);

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    paired_shares_ = wire::read_u32_le(data + offset);
    offset += 4;

    reference_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    indicative_clearing_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    imbalance_shares_ = wire::read_u32_le(data + offset);
    offset += 4;

    imbalance_side_ = static_cast<ImbalanceSide>(wire::read_char(data + offset));
    offset += 1;

    extension_number_ = wire::read_char(data + offset);
    offset += 1;

    scheduled_auction_time_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    auction_book_clearing_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    collar_reference_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    lower_auction_collar_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    upper_auction_collar_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t AuctionInformationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionInformationMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(paired_shares_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(reference_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(indicative_clearing_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(imbalance_shares_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(imbalance_side_));
    offset += 1;

    wire::write_char(data + offset, extension_number_);
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(scheduled_auction_time_.count()));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(auction_book_clearing_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(collar_reference_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(lower_auction_collar_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(upper_auction_collar_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t AuctionInformationMessage::encoded_size() const {
    return wire_size;
}

void AuctionInformationMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AuctionInformationMessage::clone() const {
    return std::make_unique<AuctionInformationMessage>(*this);
}

void AuctionInformationMessage::print(std::ostream& out) const {
    out << "AuctionInformationMessage{";
    out << "auction_type=";
    out << auction_type_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", paired_shares=";
    out << paired_shares_;
    out << ", reference_price=";
    out << reference_price_;
    out << ", indicative_clearing_price=";
    out << indicative_clearing_price_;
    out << ", imbalance_shares=";
    out << imbalance_shares_;
    out << ", imbalance_side=";
    out << imbalance_side_;
    out << ", extension_number=";
    print::character(out, extension_number_);
    out << ", scheduled_auction_time=";
    out << scheduled_auction_time_.count();
    out << ", auction_book_clearing_price=";
    out << auction_book_clearing_price_;
    out << ", collar_reference_price=";
    out << collar_reference_price_;
    out << ", lower_auction_collar=";
    out << lower_auction_collar_;
    out << ", upper_auction_collar=";
    out << upper_auction_collar_;
    out << '}';
}

bool AuctionInformationMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionInformationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionInformationMessage::operator==(const AuctionInformationMessage& other) const {
    return auction_type_ == other.auction_type_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && paired_shares_ == other.paired_shares_
        && reference_price_ == other.reference_price_
        && indicative_clearing_price_ == other.indicative_clearing_price_
        && imbalance_shares_ == other.imbalance_shares_
        && imbalance_side_ == other.imbalance_side_
        && extension_number_ == other.extension_number_
        && scheduled_auction_time_ == other.scheduled_auction_time_
        && auction_book_clearing_price_ == other.auction_book_clearing_price_
        && collar_reference_price_ == other.collar_reference_price_
        && lower_auction_collar_ == other.lower_auction_collar_
        && upper_auction_collar_ == other.upper_auction_collar_;
}

bool AuctionInformationMessage::operator!=(const AuctionInformationMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deep::iextp::v1_08
