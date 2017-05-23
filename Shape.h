//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_IDRAWABLE_H
#define UDPTASK_IDRAWABLE_H


#include <sys/param.h>
#include "Color.h"

class Shape {
public:
    /**
     * Renders the object on target display
     * @param display Pointer to display 320x480
     */
    virtual void Render(uint16_t display[320][480]) = 0;

    /**
     * Hides shape, prevents rendering - requires display refresh
     */
    void Show();

    /**
     * Shows shape, enabled by default - requires display refresh
     */
    void Hide();

    bool IsVisible;

    float getX_() const;

    void setX_(float x_);

    float getY_() const;

    void setY_(float y_);

    const Color &getStroke_() const;

    void setStroke_(const Color &stroke_);

protected:
    Shape(float x, float y, Color Stroke);

    Shape();
    Shape(Color Stroke);
    float x_;
    float y_;
    Color stroke_;

    /**
     * Checks whether the point is inside a display
     * @param x Display coordinate
     * @param y Display coordinate
     * @return False if the point is out of the display
     */
    bool InsideDisplay(int x, int y);

    inline int signum(int number);
};


#endif //UDPTASK_IDRAWABLE_H
