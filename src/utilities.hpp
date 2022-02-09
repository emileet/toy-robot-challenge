#pragma once

namespace utility
{
    /**
     * Split a string into a vector of strings
     *
     * @param str string value to be split
     * @param delimiter character to split the string
     * @return vector of strings
     */
    static inline const std::vector< std::string > str_split( std::string_view str, const char& delimiter )
    {
        auto words = str | std::views::split( delimiter ) | std::views::transform( []( const auto& roro_strs ) {
            const auto it = roro_strs | std::views::common;
            return std::string( it.begin(), it.end() );
        } );

        return { words.begin(), words.end() };
    }

    /**
     * Case insensitive string comparison
     *
     * @param str1 string to be used for comparison
     * @param str2 string to be compared against
     * @param chars number of characters to be compared
     * @return true if valid comparison, false if invalid comparison
     */
    static inline const bool str_compare( std::string_view str1, std::string_view str2, const uint32_t& chars = 0 )
    {
        return std::equal( str2.begin(), chars == 0 ? str2.end() : str2.begin() + chars, str1.begin(), []( uint8_t a, uint8_t b ) {
            return std::tolower( a ) == std::tolower( b );
        } );
    }

    /**
     * Check if a string is a number
     *
     * @param str string to check
     * @return true if string is a number, false if string is not a number
     */
    static inline bool is_number( std::string_view str )
    {
        return std::ranges::all_of( str.begin(), str.end(), []( char c ) { return isdigit( c ) != 0; } );
    }
} // namespace utility
