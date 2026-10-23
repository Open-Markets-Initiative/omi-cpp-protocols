#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of OrderID and LastQty entries in Trade Summary message
class IncrementalRefreshTradeSummaryLongOrderIdGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 16;

    IncrementalRefreshTradeSummaryLongOrderIdGroup() = default;
    IncrementalRefreshTradeSummaryLongOrderIdGroup(std::uint64_t order_id, std::int32_t last_qty, const std::array<std::byte, 4>& padding_4);

    // Order Id: Unique Order ID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Last Qty: Quantity bought or sold on this last fill
    std::int32_t last_qty() const;
    void set_last_qty(std::int32_t value);

    // Padding 4: 4 bytes padding
    const std::array<std::byte, 4>& padding_4() const;
    std::array<std::byte, 4>& padding_4();
    void set_padding_4(const std::array<std::byte, 4>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshTradeSummaryLongOrderIdGroup& other) const;
    bool operator!=(const IncrementalRefreshTradeSummaryLongOrderIdGroup& other) const;

  private:
    std::uint64_t order_id_{};
    std::int32_t last_qty_{};
    std::array<std::byte, 4> padding_4_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryLongOrderIdGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
