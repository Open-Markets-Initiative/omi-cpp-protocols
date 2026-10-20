#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSizeEncoding.hpp"
#include "../groups/InstrAttribsGroup.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// noInstrAttribs Block
class InstrAttribsGroups {
  public:
    static constexpr const char* name = "InstrAttribsGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrAttribsGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrAttribsGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return instr_attribs_group_end(); }

    GroupSizeEncoding group_size_encoding() const { return GroupSizeEncoding{ bytes_.subspan(0) }; }

    view::entries<InstrAttribsGroup> instr_attribs_group() const { return view::entries<InstrAttribsGroup>{ bytes_.subspan(3), static_cast<std::size_t>(group_size_encoding().num_in_group()), static_cast<std::size_t>(group_size_encoding().block_length()) }; }

    void print(std::ostream& out) const {
        out << "InstrAttribsGroups{";
        out << "group_size_encoding=";
        group_size_encoding().print(out);
        out << ", instr_attribs_group=";
        print::sequence(out, instr_attribs_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t instr_attribs_group_end() const { return 3 + instr_attribs_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrAttribsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
