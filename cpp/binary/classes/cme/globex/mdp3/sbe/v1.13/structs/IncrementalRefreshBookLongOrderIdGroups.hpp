#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/IncrementalRefreshBookLongOrderIdGroup.hpp"
#include "../structs/GroupSize8Byte.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoOrderIDEntries Block
class IncrementalRefreshBookLongOrderIdGroups {
  public:

    IncrementalRefreshBookLongOrderIdGroups() = default;
    IncrementalRefreshBookLongOrderIdGroups(const GroupSize8Byte& group_size_8_byte, const std::vector<IncrementalRefreshBookLongOrderIdGroup>& incremental_refresh_book_long_order_id_group);

    // Group Size 8 Byte: 8 Byte aligned repeating group dimensions
    const GroupSize8Byte& group_size_8_byte() const;
    GroupSize8Byte& group_size_8_byte();
    void set_group_size_8_byte(const GroupSize8Byte& value);

    // Incremental Refresh Book Long Order Id Group: Number of OrderID entries
    const std::vector<IncrementalRefreshBookLongOrderIdGroup>& incremental_refresh_book_long_order_id_group() const;
    std::vector<IncrementalRefreshBookLongOrderIdGroup>& incremental_refresh_book_long_order_id_group();
    void set_incremental_refresh_book_long_order_id_group(const std::vector<IncrementalRefreshBookLongOrderIdGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshBookLongOrderIdGroups& other) const;
    bool operator!=(const IncrementalRefreshBookLongOrderIdGroups& other) const;

  private:
    GroupSize8Byte group_size_8_byte_{};
    std::vector<IncrementalRefreshBookLongOrderIdGroup> incremental_refresh_book_long_order_id_group_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookLongOrderIdGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_13
