#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSizeEncoding.hpp"
#include "../groups/UnderlyingsGroup.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// noUnderlyings Block
class UnderlyingsGroups {
  public:
    static constexpr const char* name = "UnderlyingsGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnderlyingsGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnderlyingsGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return underlyings_group_end(); }

    GroupSizeEncoding group_size_encoding() const { return GroupSizeEncoding{ bytes_.subspan(0) }; }

    view::entries<UnderlyingsGroup> underlyings_group() const { return view::entries<UnderlyingsGroup>{ bytes_.subspan(3), wire::count(group_size_encoding().num_in_group()), wire::count(group_size_encoding().block_length()) }; }

    void print(std::ostream& out) const {
        out << "UnderlyingsGroups{";
        out << "group_size_encoding=";
        group_size_encoding().print(out);
        out << ", underlyings_group=";
        print::sequence(out, underlyings_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t underlyings_group_end() const { return 3 + underlyings_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnderlyingsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
