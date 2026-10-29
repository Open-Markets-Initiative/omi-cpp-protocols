#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Data.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

class DataVisitor;

// used to publish MIAX Futures Onyx Best Bid and Offer (MBBO) of a Simple Instrument or
// Complex Instrument
class BestBidAndOfferMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::BestBidAndOfferMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    BestBidAndOfferMessage() = default;
    BestBidAndOfferMessage(std::chrono::nanoseconds timestamp, std::uint32_t instrument_id, Decimal mbb_price, std::uint32_t mbb_size, Decimal mbo_price, std::uint32_t mbo_size);

    // Timestamp: Matching Engine time
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Instrument Id: Unique ID assigned by MIAX Futures Onyx
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Mbb Price: Will be provided for updates as a result of any changes to the prices or
    // sizes of the MBBO for an Simple Instrument or a Complex Instrument
    Decimal mbb_price() const;
    void set_mbb_price(Decimal value);

    // Mbb Size: Aggregate size in contracts at the displayed offer price
    std::uint32_t mbb_size() const;
    void set_mbb_size(std::uint32_t value);

    // Mbo Price: Will be provided for updates as a result of any changes to the prices or
    // sizes of the MBBO for an Simple Instrument or a Complex Instrumen
    Decimal mbo_price() const;
    void set_mbo_price(Decimal value);

    // Mbo Size: Aggregate size in contracts at the displayed offer price
    std::uint32_t mbo_size() const;
    void set_mbo_size(std::uint32_t value);

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

    bool operator==(const BestBidAndOfferMessage& other) const;
    bool operator!=(const BestBidAndOfferMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t instrument_id_{};
    Decimal mbb_price_{ 0, -9 };
    std::uint32_t mbb_size_{};
    Decimal mbo_price_{ 0, -9 };
    std::uint32_t mbo_size_{};
};

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
