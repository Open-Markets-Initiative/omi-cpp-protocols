// Eurex.T7.Eobi.Fbe.v13.0: structs/MessageHeaderComp.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../enums/TemplateId.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// Message Header Comp
class MessageHeaderComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    MessageHeaderComp() = default;
    MessageHeaderComp(std::optional<std::uint16_t> body_len, std::optional<TemplateId> template_id, std::optional<std::uint32_t> msg_seq_num);

    // Body Len: Total packet body length in bytes (header + messages)
    std::optional<std::uint16_t> body_len() const;
    void set_body_len(std::optional<std::uint16_t> value);

    // Template Id: SBE template identifier of the packet header (e.g., 13004 RefreshHeader /
    // 13005 BeaconMessage)
    std::optional<TemplateId> template_id() const;
    void set_template_id(std::optional<TemplateId> value);

    // Msg Seq Num: Per-packet sequence number; 0xFFFFFFFF for unsequenced packets (heartbeats)
    std::optional<std::uint32_t> msg_seq_num() const;
    void set_msg_seq_num(std::optional<std::uint32_t> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MessageHeaderComp& other) const;
    bool operator!=(const MessageHeaderComp& other) const;

  private:
    std::optional<std::uint16_t> body_len_{};
    std::optional<TemplateId> template_id_{};
    std::optional<std::uint32_t> msg_seq_num_{};
};

std::ostream& operator<<(std::ostream& out, const MessageHeaderComp& value);

} // namespace eurex::t7::eobi::fbe::v13_0
