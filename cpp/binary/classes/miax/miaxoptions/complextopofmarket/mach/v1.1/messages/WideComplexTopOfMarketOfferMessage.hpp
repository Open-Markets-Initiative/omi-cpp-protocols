#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/TopOfMarketQuoteCondition.hpp"
#include "../messages/Data.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

class DataVisitor;

// This is the message format that will be used to disseminate MIAX Complex Top of Market for
// strategies with high net price or large aggregate MIAX Best Offer (MBBO) size.
class WideComplexTopOfMarketOfferMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::WideComplexTopOfMarketOfferMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    WideComplexTopOfMarketOfferMessage() = default;
    WideComplexTopOfMarketOfferMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, Decimal wide_price, std::uint32_t wide_size, const std::array<std::byte, 4>& reserved_4, TopOfMarketQuoteCondition top_of_market_quote_condition);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Strategy Id: MIAX Strategy ID is assigned per trading day and is valid only for that
    // day.
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Wide Price: MIAX Best price at the time stated in Timestamp and side specified in
    // Message Type.
    Decimal wide_price() const;
    void set_wide_price(Decimal value);

    // Wide Size: Aggregate size at MIAX Best Price at the time stated in Timestamp and side
    // specified in Message Type
    std::uint32_t wide_size() const;
    void set_wide_size(std::uint32_t value);

    // Reserved 4: Reserved for future use
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Top Of Market Quote Condition: Top of Strategy Market Quote Conditions
    TopOfMarketQuoteCondition top_of_market_quote_condition() const;
    void set_top_of_market_quote_condition(TopOfMarketQuoteCondition value);

    // Data
    DataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(DataVisitor& visitor) const override;
    std::unique_ptr<Data> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Data& other) const override;

    bool operator==(const WideComplexTopOfMarketOfferMessage& other) const;
    bool operator!=(const WideComplexTopOfMarketOfferMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t strategy_id_{};
    Decimal wide_price_{ 0, -4 };
    std::uint32_t wide_size_{};
    std::array<std::byte, 4> reserved_4_{};
    TopOfMarketQuoteCondition top_of_market_quote_condition_{};
};

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
