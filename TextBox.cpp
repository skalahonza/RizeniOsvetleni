//
// Created by skala on 14.5.17.
//

#include "TextBox.h"
#include "font_rom8x16.h"

TextBox::TextBox(float x, float y, Color Stroke, int width, int height) :
        Shape(x, y, Stroke), width_(width), height_(height) {

}

int TextBox::getWidth_() const {
    return width_;
}

void TextBox::setWidth_(int width_) {
    TextBox::width_ = width_;
}

int TextBox::getHeight_() const {
    return height_;
}

void TextBox::setHeight_(int height_) {
    TextBox::height_ = height_;
}

const std::string &TextBox::getText_() const {
    return text_;
}

void TextBox::setText_(const std::string &text_) {
    TextBox::text_ = text_;
}

void TextBox::Render(int16_t display[320][480]) {
    if (!IsVisible) return;

    //Iterate through all letters - without null terminator
    for (int i = 0; i < text_.length(); ++i) {
        //GEt letter pattern from array

        //Draw letter using bit shifting
        for (int y = 0; y < 16; ++y) {
            font_bits_t character = rom8x16_bits[text_[i] * 16 + y];
            for (int x = 0; x < 8; ++x) {
                int mask = 0b10000000;
                if ((mask >> x) & character)
                    display[(int) (y_ + y)][(int) (x_ + x)] = stroke_.getRGB565();
            }
        }
    }
}
