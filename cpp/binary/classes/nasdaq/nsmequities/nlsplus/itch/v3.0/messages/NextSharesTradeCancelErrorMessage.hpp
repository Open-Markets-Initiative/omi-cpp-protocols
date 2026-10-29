#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/MarketCenter.hpp"
#include "../enums/SecurityClass.hpp"
#include "../messages/Message.hpp"
#include "../structs/OriginalSaleConditionModifier.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// Indicates that a previously reported NextShares trade transaction has been cancelled or was
// reported in error.
class NextSharesTradeCancelErrorMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::NextSharesTradeCancelErrorMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 44;

    NextSharesTradeCancelErrorMessage() = default;
    NextSharesTradeCancelErrorMessage(MarketCenter market_center, const std::string& issue_symbol, SecurityClass security_class, const std::string& original_trade_control_number, Decimal original_proxy_price, Decimal original_nav_offset_amount, std::uint32_t original_trade_size, const OriginalSaleConditionModifier& original_sale_condition_modifier, std::uint64_t consolidated_volume);

    // Market Center: Denotes the Nasdaq market system that generated the original trade report
    // message
    MarketCenter market_center() const;
    void set_market_center(MarketCenter value);

    // Issue Symbol: Denotes the Nasdaq-assigned issue symbol of the security for which the
    // trade report is being generated
    const std::string& issue_symbol() const;
    std::string& issue_symbol();
    void set_issue_symbol(const std::string& value);

    // Security Class: Indicates the primary listing market for the issue
    SecurityClass security_class() const;
    void set_security_class(SecurityClass value);

    // Original Trade Control Number: Indicates the source's internal control number associated
    // with the original trade transaction
    const std::string& original_trade_control_number() const;
    std::string& original_trade_control_number();
    void set_original_trade_control_number(const std::string& value);

    // Original Proxy Price: The proxy price reported on the original trade transaction
    Decimal original_proxy_price() const;
    void set_original_proxy_price(Decimal value);

    // Original Nav Offset Amount: The Nav offset originally applied to the Proxy Price
    Decimal original_nav_offset_amount() const;
    void set_original_nav_offset_amount(Decimal value);

    // Original Trade Size: The number of shares reported on the original trade transaction
    std::uint32_t original_trade_size() const;
    void set_original_trade_size(std::uint32_t value);

    // Original Sale Condition Modifier: The sale condition modifier reported on the original
    // trade transaction
    const OriginalSaleConditionModifier& original_sale_condition_modifier() const;
    OriginalSaleConditionModifier& original_sale_condition_modifier();
    void set_original_sale_condition_modifier(const OriginalSaleConditionModifier& value);

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

    bool operator==(const NextSharesTradeCancelErrorMessage& other) const;
    bool operator!=(const NextSharesTradeCancelErrorMessage& other) const;

  private:
    MarketCenter market_center_{};
    std::string issue_symbol_{};
    SecurityClass security_class_{};
    std::string original_trade_control_number_{};
    Decimal original_proxy_price_{ 0, -4 };
    Decimal original_nav_offset_amount_{ 0, -4 };
    std::uint32_t original_trade_size_{};
    OriginalSaleConditionModifier original_sale_condition_modifier_{};
    std::uint64_t consolidated_volume_{};
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
