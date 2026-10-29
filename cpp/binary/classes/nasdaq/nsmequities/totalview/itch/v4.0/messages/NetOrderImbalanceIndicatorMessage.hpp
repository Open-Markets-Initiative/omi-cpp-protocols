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
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class SequencedMessageVisitor;

// NASDAQ disseminates NOII data at 5-second intervals in the minutes leading up to the NASDAQ
// Opening Cross and NASDAQ Closing Cross.
class NetOrderImbalanceIndicatorMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = 'I';
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 41;

    NetOrderImbalanceIndicatorMessage() = default;
    NetOrderImbalanceIndicatorMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t paired_shares, std::uint64_t imbalance_shares, ImbalanceDirection imbalance_direction, const std::string& stock, Decimal far_price, Decimal near_price, Decimal current_reference_price, CrossType cross_type, PriceVariationIndicator price_variation_indicator);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Paired Shares: The total number of shares that are eligible to be matched at the Current
    // Reference Price.
    std::uint64_t paired_shares() const;
    void set_paired_shares(std::uint64_t value);

    // Imbalance Shares: The number of shares not paired at the Current Reference Price.
    std::uint64_t imbalance_shares() const;
    void set_imbalance_shares(std::uint64_t value);

    // Imbalance Direction: The market side of the order imbalance.
    ImbalanceDirection imbalance_direction() const;
    void set_imbalance_direction(ImbalanceDirection value);

    // Stock: Denotes the security symbol for the issue in NASDAQ Single Book. Refer to
    // Appendix NASDAQ Single Book stock symbol convention information.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Far Price: A hypothetical auction-clearing price for cross orders only. Refer to Data
    // Types for field processing notes.
    Decimal far_price() const;
    void set_far_price(Decimal value);

    // Near Price: A hypothetical auction-clearing price for cross orders as well as continuous
    // orders. Refer to Data Types for field processing notes.
    Decimal near_price() const;
    void set_near_price(Decimal value);

    // Current Reference Price: The price at which the NOII shares are being calculated. Refer
    // to Data Types for field processing notes.
    Decimal current_reference_price() const;
    void set_current_reference_price(Decimal value);

    // Cross Type: The NASDAQ cross session for which the message is being generated.
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

    // Price Variation Indicator: This field indicates the absolute value of the percentage of
    // deviation of the Near Indicative Clearing Price to the nearest Current Reference Price.
    PriceVariationIndicator price_variation_indicator() const;
    void set_price_variation_indicator(PriceVariationIndicator value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const NetOrderImbalanceIndicatorMessage& other) const;
    bool operator!=(const NetOrderImbalanceIndicatorMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
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

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
