#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSizeEncoding.hpp"
#include "../groups/DeprecatedInstrAttribsGroup.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// noInstrAttribs Block
class DeprecatedInstrAttribsGroups {
  public:
    static constexpr const char* name = "DeprecatedInstrAttribsGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DeprecatedInstrAttribsGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DeprecatedInstrAttribsGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return deprecated_instr_attribs_group_end(); }

    GroupSizeEncoding group_size_encoding() const { return GroupSizeEncoding{ bytes_.subspan(0) }; }

    view::entries<DeprecatedInstrAttribsGroup> deprecated_instr_attribs_group() const { return view::entries<DeprecatedInstrAttribsGroup>{ bytes_.subspan(3), static_cast<std::size_t>(group_size_encoding().num_in_group()), static_cast<std::size_t>(group_size_encoding().block_length()) }; }

    void print(std::ostream& out) const {
        out << "DeprecatedInstrAttribsGroups{";
        out << "group_size_encoding=";
        group_size_encoding().print(out);
        out << ", deprecated_instr_attribs_group=";
        print::sequence(out, deprecated_instr_attribs_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t deprecated_instr_attribs_group_end() const { return 3 + deprecated_instr_attribs_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DeprecatedInstrAttribsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
