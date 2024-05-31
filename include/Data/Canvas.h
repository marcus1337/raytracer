#pragma once
#include "pch.h"
#include "Pixel.h"

namespace rt
{
    template <std::size_t Width, std::size_t Height>
    class Canvas
    {
    public:
        Canvas()
        {
            clear(Pixel());
        }

        void clear(const Pixel &value)
        {
            data.fill(value);
        }

        class RowProxy
        {
        public:
            RowProxy(std::array<Pixel, Width> &row) : row(row) {}

            Pixel &operator[](std::size_t col)
            {
                return row[col];
            }

            const Pixel &operator[](std::size_t col) const
            {
                return row[col];
            }

        private:
            std::array<Pixel, Width> &row;
        };

        RowProxy operator[](std::size_t row)
        {
            return RowProxy(data[row]);
        }
        const RowProxy operator[](std::size_t row) const
        {
            return RowProxy(const_cast<std::array<Pixel, Width> &>(data[row]));
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
        std::array<Pixel, Width * Height> data;
    };

}