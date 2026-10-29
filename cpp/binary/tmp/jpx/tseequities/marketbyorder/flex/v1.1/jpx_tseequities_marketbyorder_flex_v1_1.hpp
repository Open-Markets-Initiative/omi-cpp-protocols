// Jpx TseEquities MarketByOrder Flex 1.1 Template Meta Programming

#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

// A member of a struct laid over its bytes: the overload get<Field>() finds it by, and the member
#ifndef FLEXFIELD
#define FLEXFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef FLEXSEQUENCE
#define FLEXSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

/////////////////////////////////////////////////////////////////////
// Wire
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // The types of a struct's members, in wire order: what generic code walks a struct by
    template <typename... Fields>
    struct list {};

    // A repeating group of a message: the type of its entries, each laid over its bytes in turn
    template <typename Entry>
    struct sequence {
        using entry = Entry;
    };

    // An integer as the wire holds it, in the host's order: swapped when the wire's order is not the host's
    template <std::endian Order, typename T>
    constexpr T ordered(T value) noexcept {
        if constexpr (sizeof(T) == 1 || Order == std::endian::native) { return value; }
        else { return std::byteswap(value); }
    }

    // An integer of a width no C++ integer has, assembled from its bytes in the wire's order
    template <std::endian Order, typename T, std::size_t N>
    constexpr T assembled(const std::array<std::byte, N>& bytes) noexcept {
        using U = std::make_unsigned_t<T>;
        U value = 0;
        for (std::size_t index = 0; index < N; ++index) {
            const std::size_t at = Order == std::endian::big ? index : N - 1 - index;
            value = static_cast<U>((value << 8) | std::to_integer<U>(bytes[at]));
        }
        if constexpr (std::is_signed_v<T>) {
            constexpr int spare = static_cast<int>(sizeof(T) - N) * 8;
            return static_cast<T>(static_cast<T>(value << spare) >> spare);
        }
        else { return value; }
    }

    // Text of a fixed width, as the characters before its fill
    template <std::size_t N>
    constexpr std::string_view trimmed(const std::array<char, N>& text, char fill) noexcept {
        std::size_t length = N;
        while (length > 0 && text[length - 1] == fill) { --length; }
        return { text.data(), length };
    }

    // Text of a fixed width justified right, as the characters after its fill
    template <std::size_t N>
    constexpr std::string_view trimmed_front(const std::array<char, N>& text, char fill) noexcept {
        std::size_t start = 0;
        while (start < N && text[start] == fill) { ++start; }
        return { text.data() + start, N - start };
    }

    // The integer the digits of text state, its fill skipped; it ends at anything else
    template <typename T>
    constexpr T number(std::string_view text, char fill) noexcept {
        T value = 0;
        for (const char character : text) {
            if (character == fill) { continue; }
            if (character < '0' || character > '9') { break; }
            value = static_cast<T>(value * 10 + static_cast<T>(character - '0'));
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Types
/////////////////////////////////////////////////////////////////////

// Adopted Pricing Method: Indicates the pricing method in place when the execution occurred
struct adopted_pricing_method {
    enum class type : std::uint8_t {
        itayose_method = 1,
        quote_displayed = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Best Bid: Best bid at the time the execution processing finishes; set to 0 at market close
struct best_bid {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr type no_value = static_cast<type>(0ULL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Offer: Best offer at the time the execution processing finishes; set to 0 at market close
struct best_offer {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr type no_value = static_cast<type>(0ULL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Book Center Price: Set to the book center price while the Itayose method is in place or while a quote is displayed
struct book_center_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Communication Start End Flag: Indicates the start or end of communication
struct communication_start_end_flag {
    enum class type : std::uint8_t {
        health_check_control = 0,
        communication_start = 1,
        communication_end = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Data: Variable length payload of FLEX tags including their packet headers
struct data_type {
    using type = std::span<const std::byte>;
    static constexpr bool dynamic = true;

    constexpr data_type(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { data_, length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Execution Price
struct execution_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Issue Code: Securities Identification Code left aligned with trailing spaces
struct issue_code {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// Last Price: Last price at the time the execution was processed
struct last_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Status: Indicates market status
struct market_status {
    enum class type : std::uint8_t {
        morning_session_order_acceptance_time = 11,
        morning_session_trading_hours = 12,
        end_of_morning_session = 19,
        afternoon_session_order_acceptance_time = 21,
        afternoon_session_trading_hours = 22,
        afternoon_session_pre_closing = 23,
        end_of_afternoon_session = 29,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Match Id: Identifier assigned per issue on an execution basis, unique and sequential each business day
struct match_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Count: Number of tags in the packet
struct message_count {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Type: First byte of the tag identifying the message type used as dispatch key
struct message_type {
    enum class type : char {
        seconds_timestamp_message = 'T',
        trading_status_message = 'O',
        execution_summary_message = 'K',
        add_order_message = 'A',
        order_executed_message = 'E',
        order_executed_with_price_message = 'C',
        order_delete_message = 'D',
        reset_message = 'R',
        communication_control_message = 'L',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Modification Flag: When the A tag is generated by a modification order, indicates whether there is a change of time priority
struct modification_flag {
    enum class type : std::uint8_t {
        cancel_order_or_modification_order_that_changes_time_priority = 0,
        modification_order_that_does_not_change_time_priority = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Multicast Group Number: Multicast Group Number for the request target
struct multicast_group_number {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Next Sequence Number: For retransmission set to 0; for snapshot indicates the next multicast transmission sequence number that should be received after capturing the snapshot
struct next_sequence_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of System Reboots: For retransmission set to the number of times the system has been rebooted; for snapshot set to 0
struct number_of_system_reboots {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Condition: Indicates the order condition
struct order_condition {
    enum class type : std::uint8_t {
        non_conditional = 0,
        on_open = 2,
        on_close = 4,
        funari = 6,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Id: Identifier assigned per issue on an order basis, unique and sequential each business day
struct order_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Packet Length: Length of remaining bytes after this field
struct packet_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Packet Number: Packet number within a multi packet split set always 0 in arrowhead4 0
struct packet_number {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Packet Type: First byte of the Tcp packet identifying the packet type used as dispatch key
struct packet_type {
    enum class type : char {
        login_request_retransmission_message = 'R',
        login_request_snapshot_message = 'L',
        login_result_accepted_message = 'A',
        login_result_rejected_message = 'J',
        message_response_message = 'S',
        end_of_message_message = 'G',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Price: Price registered on the order book; for market orders set to the maximum 64-bit value
struct price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pricing Method: Indicates method of pricing or status of quote display after the tag is delivered
struct pricing_method {
    enum class type : std::uint8_t {
        itayose_method = 1,
        zaraba_method = 2,
        sell_special_quote_displayed = 3,
        buy_special_quote_displayed = 4,
        sell_sequential_trade_quote_displayed = 5,
        buy_sequential_trade_quote_displayed = 6,
        other_than_the_above = 0,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Quantity: Order quantity registered on the order book in number of shares
struct quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
};

// Requested Message Count: For retransmission set to the number of messages from the first sequence number; for snapshot set to 0
struct requested_message_count {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Reset Start End Flag: When TSE needs to reset all distributed data, this indicates the start or end of the process
struct reset_start_end_flag {
    enum class type : std::uint8_t {
        start_of_reset_dissemination = 1,
        end_of_reset_dissemination = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Result Code: Set to the result code of the login request
struct result_code {
    enum class type : char {
        accepted = 'A',
        out_of_service = 'O',
        incorrect_user_id = 'U',
        incorrect_sequence_number = 'S',
        incorrect_packet_type = 'T',
        incorrect_mcg_number = 'M',
        other_error = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sequence Number: For retransmission set to the first sequence number for the request; for snapshot set to 0
struct sequence_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Short Selling Status: Indicates application of the Short Selling Regulation
struct short_selling_status {
    enum class type : std::uint8_t {
        short_selling_regulation_is_not_applied = 0,
        short_selling_regulation_is_applied = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Side: Indicates buy or sell
struct side {
    enum class type : char {
        sell_order = 'S',
        buy_order = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Status Flag: Indicates trading status
struct status_flag {
    using type = std::string_view;
    static constexpr std::size_t size = 2;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 2> value_;
};

// Tag Length: Length in bytes of the Tag Data including the Message Type byte
struct tag_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Test Mode Flag: Indicates production or test
struct test_mode_flag {
    enum class type : std::uint8_t {
        production = 1,
        test = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Time Microseconds: Time to the nearest microsecond
struct time_microseconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Time Seconds: Set to UNIX time (seconds since 1970-01-01 00:00:00 UTC)
struct time_seconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Total Invalidation: Total volume of invalidated orders in number of shares
struct total_invalidation {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
};

// Total Number Of Packets: Total packet count within a multi packet split set always 0 in arrowhead4 0
struct total_number_of_packets {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Total Volume: Total volume of executed orders in number of shares
struct total_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
};

// Triggered Side: Indicates the side whose order triggered the execution
struct triggered_side {
    enum class type : char {
        sell_order = 'S',
        buy_order = 'B',
        itayose_execution = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Update Number: Per issue update number assigned from 1 each business day
struct update_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// User Id: User ID for login authentication
struct user_id {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Utility Flag: Indicates whether another packet follows that was generated by the same transaction
struct utility_flag {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volume: Executed volume in number of shares
struct volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// End Of Message Message: Tcp end of message marker terminating a retransmission or snapshot session.
struct end_of_message_message {
    static constexpr std::string_view name = "End Of Message Message";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        multicast_group_number,
        number_of_system_reboots,
        next_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(multicast_group_number);
    FLEXFIELD(number_of_system_reboots);
    FLEXFIELD(next_sequence_number);
};

static_assert(sizeof(end_of_message_message) == end_of_message_message::size, "end_of_message_message lies over its bytes exactly");

// Message Response Message: Tcp message response carrying tag data including their packet headers in response to a retransmission or snapshot request.
struct message_response_message {
    static constexpr std::string_view name = "Message Response Message";
    static constexpr bool is_message = true;
};

// Login Result Rejected Message: Tcp login response rejecting the request. Same layout as the accepted response; Result Code carries the reason the request failed.
struct login_result_rejected_message {
    static constexpr std::string_view name = "Login Result Rejected Message";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        multicast_group_number,
        result_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(multicast_group_number);
    FLEXFIELD(result_code);
};

static_assert(sizeof(login_result_rejected_message) == login_result_rejected_message::size, "login_result_rejected_message lies over its bytes exactly");

// Login Result Accepted Message: Tcp login response accepting the request. Result Code carries A.
struct login_result_accepted_message {
    static constexpr std::string_view name = "Login Result Accepted Message";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        multicast_group_number,
        result_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(multicast_group_number);
    FLEXFIELD(result_code);
};

static_assert(sizeof(login_result_accepted_message) == login_result_accepted_message::size, "login_result_accepted_message lies over its bytes exactly");

// Login Request Snapshot Message: Tcp login request selecting snapshot, sent by the user. Same layout as the retransmission request; Number of System Reboots, Sequence Number and Requested Message Count are all set to 0.
struct login_request_snapshot_message {
    static constexpr std::string_view name = "Login Request Snapshot Message";
    static constexpr std::size_t size = 15;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        user_id,
        multicast_group_number,
        number_of_system_reboots,
        sequence_number,
        requested_message_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(user_id);
    FLEXFIELD(multicast_group_number);
    FLEXFIELD(number_of_system_reboots);
    FLEXFIELD(sequence_number);
    FLEXFIELD(requested_message_count);
};

static_assert(sizeof(login_request_snapshot_message) == login_request_snapshot_message::size, "login_request_snapshot_message lies over its bytes exactly");

// Login Request Retransmission Message: Tcp login request selecting retransmission, sent by the user. One of the two Packet Type codes the document gives the 18 byte Login Request.
struct login_request_retransmission_message {
    static constexpr std::string_view name = "Login Request Retransmission Message";
    static constexpr std::size_t size = 15;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        user_id,
        multicast_group_number,
        number_of_system_reboots,
        sequence_number,
        requested_message_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(user_id);
    FLEXFIELD(multicast_group_number);
    FLEXFIELD(number_of_system_reboots);
    FLEXFIELD(sequence_number);
    FLEXFIELD(requested_message_count);
};

static_assert(sizeof(login_request_retransmission_message) == login_request_retransmission_message::size, "login_request_retransmission_message lies over its bytes exactly");

// Tcp Payload: Branch
struct tcp_payload {
    static constexpr std::string_view name = "Tcp Payload";
    static constexpr bool is_message = false;
};

// Tcp Packet Header: Jpx Flex Tcp packet header carrying length prefix and packet type discriminator
struct tcp_packet_header {
    static constexpr std::string_view name = "Tcp Packet Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        packet_length,
        packet_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(packet_length);
    FLEXFIELD(packet_type);
};

static_assert(sizeof(tcp_packet_header) == tcp_packet_header::size, "tcp_packet_header lies over its bytes exactly");

// Tcp Packet: Jpx Flex Tcp Packet
struct tcp_packet {
    static constexpr std::string_view name = "Tcp Packet";
    static constexpr bool is_message = false;
};

// Communication Control Message: Provides information about communication control. Delivered when communication starts and ends, and in between at minute intervals.
struct communication_control_message {
    static constexpr std::string_view name = "Communication Control Message";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        test_mode_flag,
        communication_start_end_flag>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(test_mode_flag);
    FLEXFIELD(communication_start_end_flag);
};

static_assert(sizeof(communication_control_message) == communication_control_message::size, "communication_control_message lies over its bytes exactly");

// Reset Message: A tag requesting the resetting (i.e. cancellation) of all distributed information. When the user receives this tag, the user must clear all valid A tags.
struct reset_message {
    static constexpr std::string_view name = "Reset Message";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        reset_start_end_flag>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(reset_start_end_flag);
};

static_assert(sizeof(reset_message) == reset_message::size, "reset_message lies over its bytes exactly");

// Order Delete Message: Provides information about order deletion from the order book. Delivered when an order is deleted via a cancel order or a modification order or when a registered order expires.
struct order_delete_message {
    static constexpr std::string_view name = "Order Delete Message";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_microseconds,
        order_id,
        side,
        modification_flag>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(time_microseconds);
    FLEXFIELD(order_id);
    FLEXFIELD(side);
    FLEXFIELD(modification_flag);
};

static_assert(sizeof(order_delete_message) == order_delete_message::size, "order_delete_message lies over its bytes exactly");

// Order Executed With Price Message: Provides information about registered orders in case of Itayose execution. Delivered when an execution occurs by the Itayose method or while an SQ or STQ is displayed.
struct order_executed_with_price_message {
    static constexpr std::string_view name = "Order Executed With Price Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_microseconds,
        order_id,
        side,
        volume,
        match_id,
        execution_price,
        adopted_pricing_method>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(time_microseconds);
    FLEXFIELD(order_id);
    FLEXFIELD(side);
    FLEXFIELD(volume);
    FLEXFIELD(match_id);
    FLEXFIELD(execution_price);
    FLEXFIELD(adopted_pricing_method);
};

static_assert(sizeof(order_executed_with_price_message) == order_executed_with_price_message::size, "order_executed_with_price_message lies over its bytes exactly");

// Order Executed Message: Provides information about registered orders in case of Zaraba execution. Delivered when an execution occurs in Zaraba.
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 19;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_microseconds,
        order_id,
        side,
        volume,
        match_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(time_microseconds);
    FLEXFIELD(order_id);
    FLEXFIELD(side);
    FLEXFIELD(volume);
    FLEXFIELD(match_id);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Add Order Message: Provides information about book registration. Delivered when a new order or modification order is registered.
struct add_order_message {
    static constexpr std::string_view name = "Add Order Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_microseconds,
        order_id,
        side,
        quantity,
        price,
        order_condition,
        modification_flag>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(time_microseconds);
    FLEXFIELD(order_id);
    FLEXFIELD(side);
    FLEXFIELD(quantity);
    FLEXFIELD(price);
    FLEXFIELD(order_condition);
    FLEXFIELD(modification_flag);
};

static_assert(sizeof(add_order_message) == add_order_message::size, "add_order_message lies over its bytes exactly");

// Execution Summary Message: Provides summary information about execution. Delivered when an execution occurs.
struct execution_summary_message {
    static constexpr std::string_view name = "Execution Summary Message";
    static constexpr std::size_t size = 45;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_microseconds,
        triggered_side,
        total_volume,
        total_invalidation,
        last_price,
        match_id,
        best_offer,
        best_bid>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(time_microseconds);
    FLEXFIELD(triggered_side);
    FLEXFIELD(total_volume);
    FLEXFIELD(total_invalidation);
    FLEXFIELD(last_price);
    FLEXFIELD(match_id);
    FLEXFIELD(best_offer);
    FLEXFIELD(best_bid);
};

static_assert(sizeof(execution_summary_message) == execution_summary_message::size, "execution_summary_message lies over its bytes exactly");

// Trading Status Message: Provides information about the status of trading on a per-issue basis. Delivered when there is a change in the tag.
struct trading_status_message {
    static constexpr std::string_view name = "Trading Status Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_microseconds,
        market_status,
        status_flag,
        short_selling_status,
        pricing_method,
        book_center_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(time_microseconds);
    FLEXFIELD(market_status);
    FLEXFIELD(status_flag);
    FLEXFIELD(short_selling_status);
    FLEXFIELD(pricing_method);
    FLEXFIELD(book_center_price);
};

static_assert(sizeof(trading_status_message) == trading_status_message::size, "trading_status_message lies over its bytes exactly");

// Seconds Timestamp Message: Provides information about the time of processing on the Trading Server to the nearest second. Always delivered at the time the information is generated, except for Reset and Communication Control. Only one tag is delivered per process and stored at the top of the first packet.
struct seconds_timestamp_message {
    static constexpr std::string_view name = "Seconds Timestamp Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_seconds>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(time_seconds);
};

static_assert(sizeof(seconds_timestamp_message) == seconds_timestamp_message::size, "seconds_timestamp_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header: Jpx Flex tag header carrying length prefix and message type discriminator
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        tag_length,
        message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(tag_length);
    FLEXFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message: Jpx Flex tag wrapper
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Packet Header: Jpx Flex 26 byte packet header
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 26;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        multicast_group_number,
        number_of_system_reboots,
        sequence_number,
        issue_code,
        update_number,
        packet_number,
        total_number_of_packets,
        utility_flag,
        message_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    FLEXFIELD(multicast_group_number);
    FLEXFIELD(number_of_system_reboots);
    FLEXFIELD(sequence_number);
    FLEXFIELD(issue_code);
    FLEXFIELD(update_number);
    FLEXFIELD(packet_number);
    FLEXFIELD(total_number_of_packets);
    FLEXFIELD(utility_flag);
    FLEXFIELD(message_count);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Udp Packet: Jpx Flex Udp Packet
struct udp_packet {
    static constexpr std::string_view name = "Udp Packet";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    FLEXSEQUENCE(message);
};

#pragma pack(pop)

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
