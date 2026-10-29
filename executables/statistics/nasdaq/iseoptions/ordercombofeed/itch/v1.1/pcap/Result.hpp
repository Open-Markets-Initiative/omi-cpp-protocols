#pragma once

namespace packet {

    enum class result {
        nasdaq_iseoptions_ordercombofeed_itch_v1_1,
        error,
        end_of_file,
        unknown
    };

}