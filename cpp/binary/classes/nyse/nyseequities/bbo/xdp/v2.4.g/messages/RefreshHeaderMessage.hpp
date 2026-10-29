#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/FullRefreshHeader.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

class Visitor;

// The first message in each packet of refresh messages published over the Refresh multicast
// channels is of this type.
class RefreshHeaderMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RefreshHeaderMessage;

    RefreshHeaderMessage() = default;
    RefreshHeaderMessage(std::uint16_t current_refresh_pkt, std::uint16_t total_refresh_pkts, const std::optional<FullRefreshHeader>& full_refresh_header);

    // Current Refresh Pkt: The current refresh packet in the update
    std::uint16_t current_refresh_pkt() const;
    void set_current_refresh_pkt(std::uint16_t value);

    // Total Refresh Pkts: The total number of refresh packets you should expect in the update
    std::uint16_t total_refresh_pkts() const;
    void set_total_refresh_pkts(std::uint16_t value);

    // Full Refresh Header: Sequence number fields that only the full Refresh Header carries.
    const std::optional<FullRefreshHeader>& full_refresh_header() const;
    std::optional<FullRefreshHeader>& full_refresh_header();
    void set_full_refresh_header(const std::optional<FullRefreshHeader>& value);

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

    bool operator==(const RefreshHeaderMessage& other) const;
    bool operator!=(const RefreshHeaderMessage& other) const;

  private:
    std::uint16_t current_refresh_pkt_{};
    std::uint16_t total_refresh_pkts_{};
    std::optional<FullRefreshHeader> full_refresh_header_{};
};

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
