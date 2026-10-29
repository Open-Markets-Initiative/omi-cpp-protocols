#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/MarketId.hpp"
#include "../enums/PutOrCall.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

class Visitor;

// On system startup, each multicast channel sends all the symbols on its channel. Underlying
// Index Mapping messages are published first, followed by all Series Index Mapping messages,
// and for the Complex feed, Complex Symbol Definitions last of all.
class SeriesIndexMappingMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SeriesIndexMappingMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 56;

    SeriesIndexMappingMessage() = default;
    SeriesIndexMappingMessage(std::uint32_t series_index, std::uint8_t channel_id, const std::array<std::byte, 1>& reserved_a_1, MarketId market_id, std::uint8_t system_id, const std::array<std::byte, 1>& reserved_b_1, std::uint16_t stream_id, std::uint32_t underlying_index, std::uint16_t contract_multiplier, const std::string& maturity_date, PutOrCall put_or_call, const std::string& strike_price, std::uint8_t price_scale_code, const std::string& underlying_symbol, const std::string& option_symbol_root, std::uint32_t group_id);

    // Series Index: The unique ID of the symbol in the Series Index message
    std::uint32_t series_index() const;
    void set_series_index(std::uint32_t value);

    // Channel Id: Multicast channel ID of the symbols being provided.
    std::uint8_t channel_id() const;
    void set_channel_id(std::uint8_t value);

    // Reserved A 1: Filler
    const std::array<std::byte, 1>& reserved_a_1() const;
    std::array<std::byte, 1>& reserved_a_1();
    void set_reserved_a_1(const std::array<std::byte, 1>& value);

    // Market Id: Identifies originating market
    MarketId market_id() const;
    void set_market_id(MarketId value);

    // System Id: ID of the Originating System
    std::uint8_t system_id() const;
    void set_system_id(std::uint8_t value);

    // Reserved B 1: Filler
    const std::array<std::byte, 1>& reserved_b_1() const;
    std::array<std::byte, 1>& reserved_b_1();
    void set_reserved_b_1(const std::array<std::byte, 1>& value);

    // Stream Id: Identifies Stream on which this symbol will be updated
    std::uint16_t stream_id() const;
    void set_stream_id(std::uint16_t value);

    // Underlying Index: The unique ID of the symbol in the Series Index message
    std::uint32_t underlying_index() const;
    void set_underlying_index(std::uint32_t value);

    // Contract Multiplier: Contract quantity
    std::uint16_t contract_multiplier() const;
    void set_contract_multiplier(std::uint16_t value);

    // Maturity Date: YY MM DD
    const std::string& maturity_date() const;
    std::string& maturity_date();
    void set_maturity_date(const std::string& value);

    // Put Or Call: Put or Call
    PutOrCall put_or_call() const;
    void set_put_or_call(PutOrCall value);

    // Strike Price: Strike price. ASCII 0-9 with optional decimal point. EG: 51.75, 123
    const std::string& strike_price() const;
    std::string& strike_price();
    void set_strike_price(const std::string& value);

    // Price Scale Code: Price Scale Code for price conversion of the symbol. See Price
    // Formats.
    std::uint8_t price_scale_code() const;
    void set_price_scale_code(std::uint8_t value);

    // Underlying Symbol: Full symbol in NYSE Symbology.
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Option Symbol Root: OCC root of option symbol
    const std::string& option_symbol_root() const;
    std::string& option_symbol_root();
    void set_option_symbol_root(const std::string& value);

    // Group Id: Used by Market Makers. Predefined group of series within a given underlying
    // symbol.
    std::uint32_t group_id() const;
    void set_group_id(std::uint32_t value);

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

    bool operator==(const SeriesIndexMappingMessage& other) const;
    bool operator!=(const SeriesIndexMappingMessage& other) const;

  private:
    std::uint32_t series_index_{};
    std::uint8_t channel_id_{};
    std::array<std::byte, 1> reserved_a_1_{};
    MarketId market_id_{};
    std::uint8_t system_id_{};
    std::array<std::byte, 1> reserved_b_1_{};
    std::uint16_t stream_id_{};
    std::uint32_t underlying_index_{};
    std::uint16_t contract_multiplier_{};
    std::string maturity_date_{};
    PutOrCall put_or_call_{};
    std::string strike_price_{};
    std::uint8_t price_scale_code_{};
    std::string underlying_symbol_{};
    std::string option_symbol_root_{};
    std::uint32_t group_id_{};
};

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
