#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Authenticity.hpp"
#include "../enums/EtpFlag.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/InverseIndicator.hpp"
#include "../enums/IpoFlag.hpp"
#include "../enums/IssueClassification.hpp"
#include "../enums/IssueSubType.hpp"
#include "../enums/LuldReferencePriceTier.hpp"
#include "../enums/MarketCategory.hpp"
#include "../enums/RoundLotsOnly.hpp"
#include "../enums/ShortSaleThresholdIndicator.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// Identifies the securities eligible for the trading session, disseminated at the start of
// each day.
class StockDirectoryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StockDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    StockDirectoryMessage() = default;
    StockDirectoryMessage(const std::string& stock, MarketCategory market_category, FinancialStatusIndicator financial_status_indicator, std::uint32_t round_lot_size, RoundLotsOnly round_lots_only, IssueClassification issue_classification, const std::string& issue_sub_type, Authenticity authenticity, ShortSaleThresholdIndicator short_sale_threshold_indicator, IpoFlag ipo_flag, LuldReferencePriceTier luld_reference_price_tier, EtpFlag etp_flag, std::uint32_t etp_leverage_factor, InverseIndicator inverse_indicator, const std::string& bloomberg_id);

    // Stock: Denotes the security symbol for the issue in the Nasdaq execution system
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Market Category: Indicates the listing market or listing market tier for the issue
    MarketCategory market_category() const;
    void set_market_category(MarketCategory value);

    // Financial Status Indicator: For Nasdaq listed issues, denotes when an issue is flagged
    // as deficient, delinquent, bankrupt or in a compliance period
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Round Lot Size: Denotes the number of shares that represent a round lot for the issue
    std::uint32_t round_lot_size() const;
    void set_round_lot_size(std::uint32_t value);

    // Round Lots Only: Indicates if Nasdaq system limits order entry for the issue
    RoundLotsOnly round_lots_only() const;
    void set_round_lots_only(RoundLotsOnly value);

    // Issue Classification: Identifies the security class for the issue as assigned by Nasdaq
    IssueClassification issue_classification() const;
    void set_issue_classification(IssueClassification value);

    // Issue Sub Type: Identifies the security sub type for the issue as assigned by Nasdaq
    const std::string& issue_sub_type() const;
    std::string& issue_sub_type();
    void set_issue_sub_type(const std::string& value);

    // Authenticity: Denotes if an issue or quoting participant record is set up in Nasdaq
    // systems in a live, test or demo state
    Authenticity authenticity() const;
    void set_authenticity(Authenticity value);

    // Short Sale Threshold Indicator: Indicates if a security is subject to mandatory
    // close-out of short sales under Sec Rule 203(b)(3)
    ShortSaleThresholdIndicator short_sale_threshold_indicator() const;
    void set_short_sale_threshold_indicator(ShortSaleThresholdIndicator value);

    // Ipo Flag: Indicates if the Nasdaq security is set up for Ipo release
    IpoFlag ipo_flag() const;
    void set_ipo_flag(IpoFlag value);

    // Luld Reference Price Tier: Indicates which Limit Up / Limit Down price band calculation
    // parameter is to be used for the instrument
    LuldReferencePriceTier luld_reference_price_tier() const;
    void set_luld_reference_price_tier(LuldReferencePriceTier value);

    // Etp Flag: Indicates whether the security is an exchange traded product
    EtpFlag etp_flag() const;
    void set_etp_flag(EtpFlag value);

    // Etp Leverage Factor: Tracks the integral relationship of the Etp to the underlying index
    std::uint32_t etp_leverage_factor() const;
    void set_etp_leverage_factor(std::uint32_t value);

    // Inverse Indicator: Indicates the directional relationship between the Etp and the
    // underlying index
    InverseIndicator inverse_indicator() const;
    void set_inverse_indicator(InverseIndicator value);

    // Bloomberg Id: Bloomberg global identifier for the issue
    const std::string& bloomberg_id() const;
    std::string& bloomberg_id();
    void set_bloomberg_id(const std::string& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const StockDirectoryMessage& other) const;
    bool operator!=(const StockDirectoryMessage& other) const;

  private:
    std::string stock_{};
    MarketCategory market_category_{};
    FinancialStatusIndicator financial_status_indicator_{};
    std::uint32_t round_lot_size_{};
    RoundLotsOnly round_lots_only_{};
    IssueClassification issue_classification_{};
    std::string issue_sub_type_{};
    Authenticity authenticity_{};
    ShortSaleThresholdIndicator short_sale_threshold_indicator_{};
    IpoFlag ipo_flag_{};
    LuldReferencePriceTier luld_reference_price_tier_{};
    EtpFlag etp_flag_{};
    std::uint32_t etp_leverage_factor_{};
    InverseIndicator inverse_indicator_{};
    std::string bloomberg_id_{};
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
