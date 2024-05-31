#pragma once
#include "pch.h"
#include "Color.h"

namespace rt
{
    template <std::size_t Width, std::size_t Height, class T = Color>
    class Canvas
    {
    public:
        Canvas()
        {
            clear(T());
        }

        void clear(const T &value)
        {
            data.fill(value);
        }

        class RowProxy
        {
        public:
            RowProxy(std::array<T, Width> &row) : row(row) {}

            T &operator[](std::size_t col)
            {
                return row[col];
            }

            const T &operator[](std::size_t col) const
            {
                return row[col];
            }

        private:
            std::array<T, Width> &row;
        };

        RowProxy operator[](std::size_t row)
        {
            return RowProxy(data[row]);
        }
        const RowProxy operator[](std::size_t row) const
        {
            return RowProxy(const_cast<std::array<T, Width> &>(data[row]));
        }

        constexpr std::size_t getWidth() const
        {
            return Width;
        }
        constexpr std::size_t getHeight() const
        {
            return Height;
        }

    private:
        std::array<T, Width * Height> data;
    };

}