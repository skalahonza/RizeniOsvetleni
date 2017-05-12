//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_IDRAWABLE_H
#define UDPTASK_IDRAWABLE_H


#include <sys/param.h>

class Shape {
public:
    /**
     * Renders the object on target display
     * @param display Pointer to display 320x480
     */
    virtual void Render(int16_t display[320][480]) = 0;

    float getX() const;

    float getY() const;

    void setX(float x_);

    void setY(float y_);

    void Show();

    void Hide();

    bool IsVisible;

protected:
    float x_;
    float y_;


    inline int signum(int number);
};


#endif //UDPTASK_IDRAWABLE_H
