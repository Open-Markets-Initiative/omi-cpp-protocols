#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/OriginatingMarketCenterIdentifier.hpp"
#include "../enums/SecurityClass.hpp"
#include "../messages/Message.hpp"
#include "../structs/SaleConditionModifier.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// Relays trade transactions for NextShares exchange traded managed funds, reported as a proxy
// price with the Nav offset to apply to it.
class NextSharesTradeReportMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::NextSharesTradeReportMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 44;

    NextSharesTradeReportMessage() = default;
    NextSharesTradeReportMessage(OriginatingMarketCenterIdentifier originating_market_center_identifier, const std::string& next_shares_symbol, SecurityClass security_class, const std::string& trade_control_number, Decimal proxy_price, std::uint32_t trade_size, Decimal nav_offset_amount, const SaleConditionModifier& sale_condition_modifier, std::uint64_t consolidated_volume);

    // Originating Market Center Identifier: Denotes the Nasdaq market system that generated
    // the trade report message
    OriginatingMarketCenterIdentifier originating_market_center_identifier() const;
    void set_originating_market_center_identifier(OriginatingMarketCenterIdentifier value);

    // Next Shares Symbol: Denotes the NextShares symbol for which the trade report is being
    // generated
    const std::string& next_shares_symbol() const;
    std::string& next_shares_symbol();
    void set_next_shares_symbol(const std::string& value);

    // Security Class: Indicates the primary listing market for the issue
    SecurityClass security_class() const;
    void set_security_class(SecurityClass value);

    // Trade Control Number: Indicates the source's internal control number associated with the
    // given trade transaction
    const std::string& trade_control_number() const;
    std::string& trade_control_number();
    void set_trade_control_number(const std::string& value);

    // Proxy Price: Reported proxy price for the transaction
    Decimal proxy_price() const;
    void set_proxy_price(Decimal value);

    // Trade Size: Indicates the reported number of shares on the trade transaction
    std::uint32_t trade_size() const;
    void set_trade_size(std::uint32_t value);

    // Nav Offset Amount: The Nav offset that should be applied to the Proxy Price
    Decimal nav_offset_amount() const;
    void set_nav_offset_amount(Decimal value);

    // Sale Condition Modifier: Sale condition modifier, consisting of four levels
    const SaleConditionModifier& sale_condition_modifier() const;
    SaleConditionModifier& sale_condition_modifier();
    void set_sale_condition_modifier(const SaleConditionModifier& value);

    // Consolidated Volume: Reflects the volume for the Issue Symbol as reported on the
    // consolidated market data feed at the time the trade message was generated
    std::uint64_t consolidated_volume() const;
    void set_consolidated_volume(std::uint64_t value);

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

    bool operator==(const NextSharesTradeReportMessage& other) const;
    bool operator!=(const NextSharesTradeReportMessage& other) const;

  private:
    OriginatingMarketCenterIdentifier originating_market_center_identifier_{};
    std::string next_shares_symbol_{};
    SecurityClass security_class_{};
    std::string trade_control_number_{};
    Decimal proxy_price_{ 0, -4 };
    std::uint32_t trade_size_{};
    Decimal nav_offset_amount_{ 0, -4 };
    SaleConditionModifier sale_condition_modifier_{};
    std::uint64_t consolidated_volume_{};
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
