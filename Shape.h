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
    virtual void Render(int16_t display[320][480]) = 0;

    void Show();

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

    bool InsideDisplay(int x, int y);

    inline int signum(int number);
};


#endif //UDPTASK_IDRAWABLE_H
