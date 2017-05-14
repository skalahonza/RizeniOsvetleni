//
// Created by skala on 14.5.17.
//

#include "TextBox.h"
#include "font_prop14x16.h"

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
        font_bits_t charracter = winFreeSystem14x16_bits[text_[i]];

        //Draw letter using bit shifting

    }
}
