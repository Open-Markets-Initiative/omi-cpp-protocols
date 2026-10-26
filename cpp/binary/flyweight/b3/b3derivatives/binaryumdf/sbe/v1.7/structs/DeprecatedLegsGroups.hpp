#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSizeEncoding.hpp"
#include "../groups/DeprecatedLegsGroup.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// noLegs Block
class DeprecatedLegsGroups {
  public:
    static constexpr const char* name = "DeprecatedLegsGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DeprecatedLegsGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DeprecatedLegsGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return deprecated_legs_group_end(); }

    GroupSizeEncoding group_size_encoding() const { return GroupSizeEncoding{ bytes_.subspan(0) }; }

    view::entries<DeprecatedLegsGroup> deprecated_legs_group() const { return view::entries<DeprecatedLegsGroup>{ bytes_.subspan(3), wire::count(group_size_encoding().num_in_group()), wire::count(group_size_encoding().block_length()) }; }

    void print(std::ostream& out) const {
        out << "DeprecatedLegsGroups{";
        out << "group_size_encoding=";
        group_size_encoding().print(out);
        out << ", deprecated_legs_group=";
        print::sequence(out, deprecated_legs_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t deprecated_legs_group_end() const { return 3 + deprecated_legs_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DeprecatedLegsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
