// Eurex.T7.Eobi.Fbe.v15.0: structs/MessageHeaderComp.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TemplateId.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class MessageHeaderComp {
  public:
    static constexpr const char* name = "MessageHeaderComp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MessageHeaderComp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MessageHeaderComp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::optional<std::uint16_t> body_len() const { return wire::nullable(wire::read_u16_le(at(0)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<TemplateId> template_id() const { return wire::nullable_enum<TemplateId>(wire::read_u16_le(at(2)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<std::uint32_t> msg_seq_num() const { return wire::nullable(wire::read_u32_le(at(4)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    void print(std::ostream& out) const {
        out << "MessageHeaderComp{";
        out << "body_len=";
        print::optional(out, body_len());
        out << ", template_id=";
        print::optional(out, template_id());
        out << ", msg_seq_num=";
        print::optional(out, msg_seq_num());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MessageHeaderComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
