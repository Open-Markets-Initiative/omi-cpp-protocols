#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

class Visitor;

// The Add Order Refresh message can be sent in either of two contexts: 1) If a client sends a
// Refresh Request to the Request Controller, an Add Order Refresh message is sent over the
// Refresh channels as part of the refresh response for every order currently sitting on the
// book. 2) If NYSE Operations refreshes a symbol, a Symbol Clear message is published,
// followed by a full refresh. The refresh includes an Add Order Refresh message for every
// order currently sitting on the book of the symbol.
class AddOrderRefreshMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddOrderRefreshMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    AddOrderRefreshMessage() = default;
    AddOrderRefreshMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::uint32_t price, std::uint32_t volume, Side side, const std::string& firm_id, std::uint8_t num_parity_splits);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

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

    // Side: The side of the order. Valid values: ‘B’ – Buy ‘S’ – Sell
    Side side() const;
    void set_side(Side value);

    // Firm Id: The market participant’s firm ID. Blank-filled if a firm ID was not specified.
    const std::string& firm_id() const;
    std::string& firm_id();
    void set_firm_id(const std::string& value);

    // Num Parity Splits: Resulting number of splits at this price level Defaulted to 0. Future
    // use by NYSE only.
    std::uint8_t num_parity_splits() const;
    void set_num_parity_splits(std::uint8_t value);

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

    bool operator==(const AddOrderRefreshMessage& other) const;
    bool operator!=(const AddOrderRefreshMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint64_t order_id_{};
    std::uint32_t price_{};
    std::uint32_t volume_{};
    Side side_{};
    std::string firm_id_{};
    std::uint8_t num_parity_splits_{};
};

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
