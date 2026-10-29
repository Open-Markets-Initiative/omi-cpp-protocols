#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/PositionChange.hpp"
#include "../messages/Message.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

class Visitor;

// A Modify Order message is sent when the price or volume of an order is changed due to an
// event other than a cancel-replace, or full or partial execution. The content of the price
// and volume fields represent the new values after modification.
class ModifyOrderMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ModifyOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 31;

    ModifyOrderMessage() = default;
    ModifyOrderMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::uint32_t price, std::uint32_t volume, PositionChange position_change, std::uint8_t prev_price_parity_splits, std::uint8_t new_price_parity_splits);

    // Source Time Ns: The nanosecond offset from the SourceTime
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Symbol Index: The unique ID of this symbol for all products within this market. This ID
    // cannot be used to cross reference a security between markets.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: Reserved for future use. Ignore any content. This usage will become
    // standard across all products in future releases.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Order Id: The unique ID assigned by the matching engine to this order . Can be used to
    // match this message to the gateway Order Report.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Price: The order price. Use with the Price Scale from the symbol-mapping index.
    std::uint32_t price() const;
    void set_price(std::uint32_t value);

    // Volume: The order quantity in shares
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Position Change: Currently defaulted to 0.
    PositionChange position_change() const;
    void set_position_change(PositionChange value);

    // Prev Price Parity Splits: Resulting number of splits at the previous price Defaulted to
    // 0. Future use by NYSE only.
    std::uint8_t prev_price_parity_splits() const;
    void set_prev_price_parity_splits(std::uint8_t value);

    // New Price Parity Splits: Resulting number of splits at the new price. Defaulted to 0.
    // Future use by NYSE only.
    std::uint8_t new_price_parity_splits() const;
    void set_new_price_parity_splits(std::uint8_t value);

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

    bool operator==(const ModifyOrderMessage& other) const;
    bool operator!=(const ModifyOrderMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint64_t order_id_{};
    std::uint32_t price_{};
    std::uint32_t volume_{};
    PositionChange position_change_{};
    std::uint8_t prev_price_parity_splits_{};
    std::uint8_t new_price_parity_splits_{};
};

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
