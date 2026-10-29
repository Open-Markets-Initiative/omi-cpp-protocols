#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TemplateId.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

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

    std::uint16_t body_len() const { return wire::read_u16_le(at(0)); }

    TemplateId template_id() const { return static_cast<TemplateId>(wire::read_u16_le(at(2))); }

    std::uint32_t msg_seq_num() const { return wire::read_u32_le(at(4)); }

    void print(std::ostream& out) const {
        out << "MessageHeaderComp{";
        out << "body_len=";
        out << body_len();
        out << ", template_id=";
        out << template_id();
        out << ", msg_seq_num=";
        out << msg_seq_num();
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

} // namespace eurex::t7::eobi::fbe::v6_0
