#pragma once

#include "../types/Side.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OrderId.hpp"
#include "../types/Size.hpp"
#include "../types/Price.hpp"
#include "../messages/SnapshotDataMessage.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

#pragma pack(push, 1)

// A displayed order that has been added to the IEX Book
struct AddOrderMessage {

    Side side;
    Timestamp timestamp;
    Symbol symbol;
    OrderId order_id;
    Size size;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'a';

    // parse method
    static AddOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderMessage*>(buffer);
    }

    // parse method const
    static const AddOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderMessage* parse(const SnapshotDataMessage* header) {
        return reinterpret_cast<const AddOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SnapshotDataMessage));
    }
};

#pragma pack(pop)
}
