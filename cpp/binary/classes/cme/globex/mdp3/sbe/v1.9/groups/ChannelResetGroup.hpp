#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_9 {

// Number of entries in Market Data message
class ChannelResetGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 2;

    ChannelResetGroup() = default;
    ChannelResetGroup(std::int16_t appl_id);

    // Appl Id: The channel ID as defined in the XML Configuration file
    std::int16_t appl_id() const;
    void set_appl_id(std::int16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ChannelResetGroup& other) const;
    bool operator!=(const ChannelResetGroup& other) const;

  private:
    std::int16_t appl_id_{};
};

std::ostream& operator<<(std::ostream& out, const ChannelResetGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_9
