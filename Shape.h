//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_IDRAWABLE_H
#define UDPTASK_IDRAWABLE_H


#include <bits/types.h>

class Shape {
public:
    /**
     * Renders the object on target display
     * @param display Pointer to display 320x480
     */
    virtual void Render(__uint16_t display[320][480]) = 0;

    unsigned short int GetX() const;

    unsigned short int GetY() const;

    bool IsVisible;

    void Show();

    void Hide();

protected:
    unsigned short int x_;
    unsigned short int y_;

    inline int signum(int number);
};


#endif //UDPTASK_IDRAWABLE_H
