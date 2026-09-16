#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/CrossType.hpp"
#include "../enums/ImbalanceDirection.hpp"
#include "../enums/PriceVariationIndicator.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// NASDAQ disseminates NOII data
class NetOrderImbalanceIndicatorMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::NetOrderImbalanceIndicatorMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 49;

    NetOrderImbalanceIndicatorMessage() = default;
    NetOrderImbalanceIndicatorMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t paired_shares, std::uint64_t imbalance_shares, ImbalanceDirection imbalance_direction, const std::string& stock, Decimal far_price, Decimal near_price, Decimal current_reference_price, CrossType cross_type, PriceVariationIndicator price_variation_indicator);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Paired Shares: The total number of shares that are eligible to be matched at the Current
    // Reference Price
    std::uint64_t paired_shares() const;
    void set_paired_shares(std::uint64_t value);

    // Imbalance Shares: The number of shares not paired at the Current Reference Price
    std::uint64_t imbalance_shares() const;
    void set_imbalance_shares(std::uint64_t value);

    // Imbalance Direction: The market side of the order imbalance
    ImbalanceDirection imbalance_direction() const;
    void set_imbalance_direction(ImbalanceDirection value);

    // Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Far Price: A hypothetical auction-clearing price for cross orders only
    Decimal far_price() const;
    void set_far_price(Decimal value);

    // Near Price: A hypothetical auction-clearing price for cross orders as well as continuous
    // orders
    Decimal near_price() const;
    void set_near_price(Decimal value);

    // Current Reference Price: The price at which the NOII shares are being calculated
    Decimal current_reference_price() const;
    void set_current_reference_price(Decimal value);

    // Cross Type: The Nasdaq cross session for which the message is being generated
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

    // Price Variation Indicator: Indicates the absolute value of the percentage of deviation
    // of the Near Indicative Clearing Price to the nearest Current Reference Price
    PriceVariationIndicator price_variation_indicator() const;
    void set_price_variation_indicator(PriceVariationIndicator value);

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

    bool operator==(const NetOrderImbalanceIndicatorMessage& other) const;
    bool operator!=(const NetOrderImbalanceIndicatorMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t paired_shares_{};
    std::uint64_t imbalance_shares_{};
    ImbalanceDirection imbalance_direction_{};
    std::string stock_{};
    Decimal far_price_{ 0, -4 };
    Decimal near_price_{ 0, -4 };
    Decimal current_reference_price_{ 0, -4 };
    CrossType cross_type_{};
    PriceVariationIndicator price_variation_indicator_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
