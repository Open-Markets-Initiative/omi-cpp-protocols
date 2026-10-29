#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/CrossType.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

class Visitor;

// A Cross Trade message is published on completion of a crossing auction, and shows the bulk
// volume that traded in the auction. The Reason Code field indicates the auction type.
// Additionally, a non-printable Order Execution or Trade message will be published for each
// order that traded.
class CrossTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::CrossTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    CrossTradeMessage() = default;
    CrossTradeMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t cross_id, std::uint32_t price, std::uint32_t volume, CrossType cross_type);

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

    // Cross Id: Unique identifier for this Cross Trade. Used in Cross Correction message to
    // identify the Cross Trade to correct.
    std::uint32_t cross_id() const;
    void set_cross_id(std::uint32_t value);

    // Price: The order price. Use with the Price Scale from the symbol-mapping index.
    std::uint32_t price() const;
    void set_price(std::uint32_t value);

    // Volume: The order quantity in shares
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Cross Type: Reason for the crossing auction.
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

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

    bool operator==(const CrossTradeMessage& other) const;
    bool operator!=(const CrossTradeMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint32_t cross_id_{};
    std::uint32_t price_{};
    std::uint32_t volume_{};
    CrossType cross_type_{};
};

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
