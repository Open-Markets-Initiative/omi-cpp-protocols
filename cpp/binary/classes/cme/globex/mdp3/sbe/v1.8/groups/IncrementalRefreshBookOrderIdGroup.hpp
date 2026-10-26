#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../enums/OrderUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of OrderID entries
class IncrementalRefreshBookOrderIdGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 24;

    IncrementalRefreshBookOrderIdGroup() = default;
    IncrementalRefreshBookOrderIdGroup(std::uint64_t order_id, std::optional<std::uint64_t> md_order_priority, std::optional<std::int32_t> md_display_qty_optional, std::optional<std::uint8_t> reference_id, OrderUpdateAction order_update_action, const std::array<std::byte, 2>& padding_2);

    // Order Id: Unique Order ID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Md Order Priority: Order priority for execution on the order book
    std::optional<std::uint64_t> md_order_priority() const;
    void set_md_order_priority(std::optional<std::uint64_t> value);

    // Md Display Qty Optional: Visible qty of order
    std::optional<std::int32_t> md_display_qty_optional() const;
    void set_md_display_qty_optional(std::optional<std::int32_t> value);

    // Reference Id: Reference to corresponding Price and Security ID, sequence of MD entry in
    // the message
    std::optional<std::uint8_t> reference_id() const;
    void set_reference_id(std::optional<std::uint8_t> value);

    // Order Update Action: Order book update action to be applied to the order referenced by
    // OrderID
    OrderUpdateAction order_update_action() const;
    void set_order_update_action(OrderUpdateAction value);

    // Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& padding_2() const;
    std::array<std::byte, 2>& padding_2();
    void set_padding_2(const std::array<std::byte, 2>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshBookOrderIdGroup& other) const;
    bool operator!=(const IncrementalRefreshBookOrderIdGroup& other) const;

  private:
    std::uint64_t order_id_{};
    std::optional<std::uint64_t> md_order_priority_{};
    std::optional<std::int32_t> md_display_qty_optional_{};
    std::optional<std::uint8_t> reference_id_{};
    OrderUpdateAction order_update_action_{};
    std::array<std::byte, 2> padding_2_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookOrderIdGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_8
