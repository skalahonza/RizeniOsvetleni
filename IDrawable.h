//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_IDRAWABLE_H
#define UDPTASK_IDRAWABLE_H


class IDrawable {
public:
    /**
     * Renders the object on target display
     * @param display Pointer to display 320x480
     */
    virtual void Render(char display[320][480]) = 0;

protected:
    unsigned short int x_;
    unsigned short int y_;
};


#endif //UDPTASK_IDRAWABLE_H
