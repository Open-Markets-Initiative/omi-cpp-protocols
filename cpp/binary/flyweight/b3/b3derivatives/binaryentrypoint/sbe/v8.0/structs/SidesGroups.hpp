#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSizeEncoding.hpp"
#include "../groups/SidesGroup.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// noSides Block
class SidesGroups {
  public:
    static constexpr const char* name = "SidesGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SidesGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SidesGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return sides_group_end(); }

    GroupSizeEncoding group_size_encoding() const { return GroupSizeEncoding{ bytes_.subspan(0) }; }

    view::entries<SidesGroup> sides_group() const { return view::entries<SidesGroup>{ bytes_.subspan(3), wire::count(group_size_encoding().num_in_group()), wire::count(group_size_encoding().block_length()) }; }

    void print(std::ostream& out) const {
        out << "SidesGroups{";
        out << "group_size_encoding=";
        group_size_encoding().print(out);
        out << ", sides_group=";
        print::sequence(out, sides_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t sides_group_end() const { return 3 + sides_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SidesGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
