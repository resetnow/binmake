/*
 * BinStream.h
 *
 *  Created on: 2 janv. 2017
 *  Author: Adel Daouzli
 *  License: MIT License
 */

#ifndef BINSTREAM_H_
#define BINSTREAM_H_

#include <sstream>
#include <string>
#include <vector>

#include "bs_exception.h"

namespace BS
{
    typedef enum
    {
        t_num_hexadecimal,
        t_num_decimal,
        t_num_octal,
        t_num_binary,
        t_string,
        t_none,
        t_error
    } type_t;

    typedef enum
    {
        t_int8,
        t_uint8,
        t_int16,
        t_uint16,
        t_int32,
        t_uint32,
        t_int64,
        t_uint64,
        t_number_error
    } type_number_t;

    typedef enum
    {
        little_endian,
        big_endian
    } endianess_t;

    typedef union
    {
        type_number_t type;
        union
        {
            uint8_t value_i8;
            int8_t value_u8;
            uint16_t value_i16;
            int16_t value_u16;
            uint32_t value_i32;
            int32_t value_u32;
            uint64_t value_i64;
            int64_t value_u64;
        };
    } number_t;

    class BinStream
    {
    private:
        std::stringstream m_input; // the input string to convert to binary
        std::vector<char> m_output; // the output binary data to generate

        endianess_t m_curr_endianess;
        type_t m_curr_numbers;

        bool m_input_ready;
        bool m_output_ready;

        bool m_verbose;

    public:
        BinStream(bool verbose=false);
        BinStream(const BinStream& o);
        ~BinStream();

        void reset(void);
        void reset_modes(void);
        void reset_output(void);
        void reset_input(void);

        void set_verbosity(bool verbose);

        bool input_ready(void) const;
        bool output_ready(void) const;
        bool get_output(std::vector<char>& output) const;
        size_t size(void) const;

        char operator[](const size_t index) const;

        // Stream operators
        BinStream& operator<<(const std::istream & s);
        BinStream& operator<<(const std::ifstream & f);
        BinStream& operator<<(const std::stringstream & desc);
        BinStream& operator<<(const std::string & desc);
        BinStream& operator>>(std::ofstream & f);
        BinStream& operator>>(std::vector<char> & output);

        friend std::ostream& operator<<(std::ostream& stream, const BinStream& bin_stream);
        friend std::istream& operator>>(std::istream& stream, BinStream& bin_stream);

        // Low-level functions for parsing input and generating output
        void parse_input(const std::string & element);
        type_t get_type(const std::string & element);
        bool check_grammar(const std::string & element, type_t elem_type);
        void extract_number(number_t number, const std::string & element,
                const type_number_t & element_type, const endianess_t & endianess, const int size);
        void proceed_element(const std::string & element);
        void update_bin_output(const type_t stype, const endianess_t etype, const std::string& s);

        void bs_log(std::string msg);
    };
}

#endif /* BINSTREAM_H_ */
