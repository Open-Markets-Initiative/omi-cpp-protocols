#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of repeating FeedType entries
class FeedTypesGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    FeedTypesGroup() = default;
    FeedTypesGroup(const std::string& md_feed_type, std::int8_t market_depth);

    // Md Feed Type: Describes a class of service for a given data feed. GBX- Real Book,
    // GBI-Implied Book
    const std::string& md_feed_type() const;
    std::string& md_feed_type();
    void set_md_feed_type(const std::string& value);

    // Market Depth: Book depth
    std::int8_t market_depth() const;
    void set_market_depth(std::int8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const FeedTypesGroup& other) const;
    bool operator!=(const FeedTypesGroup& other) const;

  private:
    std::string md_feed_type_{};
    std::int8_t market_depth_{};
};

std::ostream& operator<<(std::ostream& out, const FeedTypesGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_8
