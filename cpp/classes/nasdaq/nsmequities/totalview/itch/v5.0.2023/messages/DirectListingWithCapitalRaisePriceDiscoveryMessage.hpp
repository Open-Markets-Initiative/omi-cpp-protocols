#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/OpenEligibilityStatus.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// This message is disseminated only for Direct Listing with Capital Raise (DLCR) securities
class DirectListingWithCapitalRaisePriceDiscoveryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::DirectListingWithCapitalRaisePriceDiscoveryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 47;

    DirectListingWithCapitalRaisePriceDiscoveryMessage() = default;
    DirectListingWithCapitalRaisePriceDiscoveryMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, OpenEligibilityStatus open_eligibility_status, Decimal minimum_allowable_price, Decimal maximum_allowable_price, Decimal near_execution_price, std::uint64_t near_execution_time, Decimal lower_price_range_collar, Decimal upper_price_range_collar);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Open Eligibility Status: Indicates if the security is eligible to be released for
    // trading
    OpenEligibilityStatus open_eligibility_status() const;
    void set_open_eligibility_status(OpenEligibilityStatus value);

    // Minimum Allowable Price: 20% below Registration Statement Lower Price
    Decimal minimum_allowable_price() const;
    void set_minimum_allowable_price(Decimal value);

    // Maximum Allowable Price: 80% above Registration Statement Highest Price
    Decimal maximum_allowable_price() const;
    void set_maximum_allowable_price(Decimal value);

    // Near Execution Price: The current reference price when the DLCR volatility test has
    // successfully passed
    Decimal near_execution_price() const;
    void set_near_execution_price(Decimal value);

    // Near Execution Time: The time at which the Near Execution Price was determined
    std::uint64_t near_execution_time() const;
    void set_near_execution_time(std::uint64_t value);

    // Lower Price Range Collar: Indicates the price of the Lower Auction Collar Threshold
    Decimal lower_price_range_collar() const;
    void set_lower_price_range_collar(Decimal value);

    // Upper Price Range Collar: Indicates the price of the Upper Auction Collar Threshold
    Decimal upper_price_range_collar() const;
    void set_upper_price_range_collar(Decimal value);

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

    bool operator==(const DirectListingWithCapitalRaisePriceDiscoveryMessage& other) const;
    bool operator!=(const DirectListingWithCapitalRaisePriceDiscoveryMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::string stock_{};
    OpenEligibilityStatus open_eligibility_status_{};
    Decimal minimum_allowable_price_{ 0, -4 };
    Decimal maximum_allowable_price_{ 0, -4 };
    Decimal near_execution_price_{ 0, -4 };
    std::uint64_t near_execution_time_{};
    Decimal lower_price_range_collar_{ 0, -4 };
    Decimal upper_price_range_collar_{ 0, -4 };
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
