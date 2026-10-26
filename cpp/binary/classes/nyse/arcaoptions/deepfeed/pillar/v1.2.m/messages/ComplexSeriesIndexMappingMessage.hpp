#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../enums/MarketId.hpp"
#include "../groups/ComplexSeriesIndexMappingLeg.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class Visitor;

// Published over the real-time data channels at system startup or in the context of a refresh
// sequence. Provides referential data for a single specified options complex series.
class ComplexSeriesIndexMappingMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ComplexSeriesIndexMappingMessage;

    ComplexSeriesIndexMappingMessage() = default;
    ComplexSeriesIndexMappingMessage(std::uint32_t series_index, MarketId market_id, std::uint8_t system_id, std::uint16_t no_of_legs, const std::vector<ComplexSeriesIndexMappingLeg>& complex_series_index_mapping_leg);

    // Series Index: The unique ID of this series within this market.
    std::uint32_t series_index() const;
    void set_series_index(std::uint32_t value);

    // Market Id: ID of the Originating Market.
    MarketId market_id() const;
    void set_market_id(MarketId value);

    // System Id: ID of the Originating matching engine server.
    std::uint8_t system_id() const;
    void set_system_id(std::uint8_t value);

    // No Of Legs: Number of legs in complex symbol. 2 - 12
    std::uint16_t no_of_legs() const;
    void set_no_of_legs(std::uint16_t value);

    // Complex Series Index Mapping Leg:
    const std::vector<ComplexSeriesIndexMappingLeg>& complex_series_index_mapping_leg() const;
    std::vector<ComplexSeriesIndexMappingLeg>& complex_series_index_mapping_leg();
    void set_complex_series_index_mapping_leg(const std::vector<ComplexSeriesIndexMappingLeg>& value);

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

    bool operator==(const ComplexSeriesIndexMappingMessage& other) const;
    bool operator!=(const ComplexSeriesIndexMappingMessage& other) const;

  private:
    std::uint32_t series_index_{};
    MarketId market_id_{};
    std::uint8_t system_id_{};
    std::uint16_t no_of_legs_{};
    std::vector<ComplexSeriesIndexMappingLeg> complex_series_index_mapping_leg_{};
};

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
