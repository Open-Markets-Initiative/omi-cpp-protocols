#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Data.hpp"
#include "../structs/CompactBid.hpp"
#include "../structs/CompactOffer.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

class DataVisitor;

// This is the message format that will be used to disseminate both sides of the MIAX top of
// market for strategies (cMBBO) with low net price and small aggregate size.
class CompactComplexDoubleSidedTopOfMarketMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::CompactComplexDoubleSidedTopOfMarketMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 22;

    CompactComplexDoubleSidedTopOfMarketMessage() = default;
    CompactComplexDoubleSidedTopOfMarketMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, const CompactBid& compact_bid, const CompactOffer& compact_offer);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Strategy Id: MIAX Strategy ID is assigned per trading day and is valid only for that
    // day.
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Compact Bid: Compact Bid
    const CompactBid& compact_bid() const;
    CompactBid& compact_bid();
    void set_compact_bid(const CompactBid& value);

    // Compact Offer: Compact Offer
    const CompactOffer& compact_offer() const;
    CompactOffer& compact_offer();
    void set_compact_offer(const CompactOffer& value);

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

    bool operator==(const CompactComplexDoubleSidedTopOfMarketMessage& other) const;
    bool operator!=(const CompactComplexDoubleSidedTopOfMarketMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t strategy_id_{};
    CompactBid compact_bid_{};
    CompactOffer compact_offer_{};
};

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
