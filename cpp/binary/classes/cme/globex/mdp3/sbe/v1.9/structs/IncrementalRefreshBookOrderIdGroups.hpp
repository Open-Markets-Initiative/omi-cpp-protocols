#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/IncrementalRefreshBookOrderIdGroup.hpp"
#include "../structs/GroupSize8Byte.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// NoOrderIDEntries Block
class IncrementalRefreshBookOrderIdGroups {
  public:

    IncrementalRefreshBookOrderIdGroups() = default;
    IncrementalRefreshBookOrderIdGroups(const GroupSize8Byte& group_size_8_byte, const std::vector<IncrementalRefreshBookOrderIdGroup>& incremental_refresh_book_order_id_group);

    // Group Size 8 Byte: 8 Byte aligned repeating group dimensions
    const GroupSize8Byte& group_size_8_byte() const;
    GroupSize8Byte& group_size_8_byte();
    void set_group_size_8_byte(const GroupSize8Byte& value);

    // Incremental Refresh Book Order Id Group: Number of OrderID entries
    const std::vector<IncrementalRefreshBookOrderIdGroup>& incremental_refresh_book_order_id_group() const;
    std::vector<IncrementalRefreshBookOrderIdGroup>& incremental_refresh_book_order_id_group();
    void set_incremental_refresh_book_order_id_group(const std::vector<IncrementalRefreshBookOrderIdGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshBookOrderIdGroups& other) const;
    bool operator!=(const IncrementalRefreshBookOrderIdGroups& other) const;

  private:
    GroupSize8Byte group_size_8_byte_{};
    std::vector<IncrementalRefreshBookOrderIdGroup> incremental_refresh_book_order_id_group_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookOrderIdGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_9
