#include "StockDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

StockDirectoryMessage::StockDirectoryMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, MarketCategory market_category, FinancialStatusIndicator financial_status_indicator, std::uint32_t round_lot_size, RoundLotsOnly round_lots_only, IssueClassification issue_classification, const std::string& issue_sub_type, Authenticity authenticity, ShortSaleThresholdIndicator short_sale_threshold_indicator, IpoFlag ipo_flag, LuldReferencePriceTier luld_reference_price_tier, EtpFlag etp_flag, std::uint32_t etp_leverage_factor, InverseIndicator inverse_indicator)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), market_category_(market_category), financial_status_indicator_(financial_status_indicator), round_lot_size_(round_lot_size), round_lots_only_(round_lots_only), issue_classification_(issue_classification), issue_sub_type_(issue_sub_type), authenticity_(authenticity), short_sale_threshold_indicator_(short_sale_threshold_indicator), ipo_flag_(ipo_flag), luld_reference_price_tier_(luld_reference_price_tier), etp_flag_(etp_flag), etp_leverage_factor_(etp_leverage_factor), inverse_indicator_(inverse_indicator) {}

std::uint16_t StockDirectoryMessage::stock_locate() const { return stock_locate_; }
void StockDirectoryMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t StockDirectoryMessage::tracking_number() const { return tracking_number_; }
void StockDirectoryMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds StockDirectoryMessage::timestamp() const { return timestamp_; }
void StockDirectoryMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& StockDirectoryMessage::stock() const { return stock_; }
std::string& StockDirectoryMessage::stock() { return stock_; }
void StockDirectoryMessage::set_stock(const std::string& value) { stock_ = value; }

MarketCategory StockDirectoryMessage::market_category() const { return market_category_; }
void StockDirectoryMessage::set_market_category(MarketCategory value) { market_category_ = value; }

FinancialStatusIndicator StockDirectoryMessage::financial_status_indicator() const { return financial_status_indicator_; }
void StockDirectoryMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

std::uint32_t StockDirectoryMessage::round_lot_size() const { return round_lot_size_; }
void StockDirectoryMessage::set_round_lot_size(std::uint32_t value) { round_lot_size_ = value; }

RoundLotsOnly StockDirectoryMessage::round_lots_only() const { return round_lots_only_; }
void StockDirectoryMessage::set_round_lots_only(RoundLotsOnly value) { round_lots_only_ = value; }

IssueClassification StockDirectoryMessage::issue_classification() const { return issue_classification_; }
void StockDirectoryMessage::set_issue_classification(IssueClassification value) { issue_classification_ = value; }

const std::string& StockDirectoryMessage::issue_sub_type() const { return issue_sub_type_; }
std::string& StockDirectoryMessage::issue_sub_type() { return issue_sub_type_; }
void StockDirectoryMessage::set_issue_sub_type(const std::string& value) { issue_sub_type_ = value; }

Authenticity StockDirectoryMessage::authenticity() const { return authenticity_; }
void StockDirectoryMessage::set_authenticity(Authenticity value) { authenticity_ = value; }

ShortSaleThresholdIndicator StockDirectoryMessage::short_sale_threshold_indicator() const { return short_sale_threshold_indicator_; }
void StockDirectoryMessage::set_short_sale_threshold_indicator(ShortSaleThresholdIndicator value) { short_sale_threshold_indicator_ = value; }

IpoFlag StockDirectoryMessage::ipo_flag() const { return ipo_flag_; }
void StockDirectoryMessage::set_ipo_flag(IpoFlag value) { ipo_flag_ = value; }

LuldReferencePriceTier StockDirectoryMessage::luld_reference_price_tier() const { return luld_reference_price_tier_; }
void StockDirectoryMessage::set_luld_reference_price_tier(LuldReferencePriceTier value) { luld_reference_price_tier_ = value; }

EtpFlag StockDirectoryMessage::etp_flag() const { return etp_flag_; }
void StockDirectoryMessage::set_etp_flag(EtpFlag value) { etp_flag_ = value; }

std::uint32_t StockDirectoryMessage::etp_leverage_factor() const { return etp_leverage_factor_; }
void StockDirectoryMessage::set_etp_leverage_factor(std::uint32_t value) { etp_leverage_factor_ = value; }

InverseIndicator StockDirectoryMessage::inverse_indicator() const { return inverse_indicator_; }
void StockDirectoryMessage::set_inverse_indicator(InverseIndicator value) { inverse_indicator_ = value; }

MessageCode StockDirectoryMessage::type() const { return message_type; }

std::string_view StockDirectoryMessage::name() const { return "Stock Directory Message"; }

std::size_t StockDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StockDirectoryMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    market_category_ = static_cast<MarketCategory>(wire::read_char(data + offset));
    offset += 1;

    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    round_lot_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    round_lots_only_ = static_cast<RoundLotsOnly>(wire::read_char(data + offset));
    offset += 1;

    issue_classification_ = static_cast<IssueClassification>(wire::read_char(data + offset));
    offset += 1;

    issue_sub_type_ = wire::read_text(data + offset, 2, ' ');
    offset += 2;

    authenticity_ = static_cast<Authenticity>(wire::read_char(data + offset));
    offset += 1;

    short_sale_threshold_indicator_ = static_cast<ShortSaleThresholdIndicator>(wire::read_char(data + offset));
    offset += 1;

    ipo_flag_ = static_cast<IpoFlag>(wire::read_char(data + offset));
    offset += 1;

    luld_reference_price_tier_ = static_cast<LuldReferencePriceTier>(wire::read_char(data + offset));
    offset += 1;

    etp_flag_ = static_cast<EtpFlag>(wire::read_char(data + offset));
    offset += 1;

    etp_leverage_factor_ = wire::read_u32_be(data + offset);
    offset += 4;

    inverse_indicator_ = static_cast<InverseIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t StockDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StockDirectoryMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(market_category_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(round_lot_size_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(round_lots_only_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(issue_classification_));
    offset += 1;

    wire::write_text(data + offset, 2, ' ', issue_sub_type_);
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(authenticity_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(short_sale_threshold_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(ipo_flag_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(luld_reference_price_tier_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(etp_flag_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(etp_leverage_factor_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(inverse_indicator_));
    offset += 1;

    return offset;
}

std::size_t StockDirectoryMessage::encoded_size() const {
    return wire_size;
}

void StockDirectoryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StockDirectoryMessage::clone() const {
    return std::make_unique<StockDirectoryMessage>(*this);
}

void StockDirectoryMessage::print(std::ostream& out) const {
    out << "StockDirectoryMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", market_category=";
    out << market_category_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", round_lot_size=";
    out << round_lot_size_;
    out << ", round_lots_only=";
    out << round_lots_only_;
    out << ", issue_classification=";
    out << issue_classification_;
    out << ", issue_sub_type=";
    print::text(out, issue_sub_type_);
    out << ", authenticity=";
    out << authenticity_;
    out << ", short_sale_threshold_indicator=";
    out << short_sale_threshold_indicator_;
    out << ", ipo_flag=";
    out << ipo_flag_;
    out << ", luld_reference_price_tier=";
    out << luld_reference_price_tier_;
    out << ", etp_flag=";
    out << etp_flag_;
    out << ", etp_leverage_factor=";
    out << etp_leverage_factor_;
    out << ", inverse_indicator=";
    out << inverse_indicator_;
    out << '}';
}

bool StockDirectoryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StockDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StockDirectoryMessage::operator==(const StockDirectoryMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && market_category_ == other.market_category_
        && financial_status_indicator_ == other.financial_status_indicator_
        && round_lot_size_ == other.round_lot_size_
        && round_lots_only_ == other.round_lots_only_
        && issue_classification_ == other.issue_classification_
        && issue_sub_type_ == other.issue_sub_type_
        && authenticity_ == other.authenticity_
        && short_sale_threshold_indicator_ == other.short_sale_threshold_indicator_
        && ipo_flag_ == other.ipo_flag_
        && luld_reference_price_tier_ == other.luld_reference_price_tier_
        && etp_flag_ == other.etp_flag_
        && etp_leverage_factor_ == other.etp_leverage_factor_
        && inverse_indicator_ == other.inverse_indicator_;
}

bool StockDirectoryMessage::operator!=(const StockDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
