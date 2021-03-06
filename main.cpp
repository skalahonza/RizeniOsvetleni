#include <iostream>
#include <sstream>
#include "Perifery.h"
#include "Line.h"
#include "TextBox.h"
#include "DisplayHandler.h"
#include "Rectangle.h"
#include "LightUnit.h"
#include "Broadcaster.h"
#include "Listener.h"
#include "NetTools.h"
#include "global_const.h"
#include "Updater.h"
#include "Icon.h"

#define STEP 5
using namespace std;

void go_home();

void go_manage();

void select_unit();

void scroll_red_value(SPINDIRECTION a, int value);

void scroll_green_value(SPINDIRECTION a, int value);

void scroll_blue_value(SPINDIRECTION a, int value);

void scroll_attribute_list(SPINDIRECTION a, int value);

void scroll_manage_color_list(SPINDIRECTION a, int value);

void update_textboxes();

void confirm_wall_managment();

void confirm_ceil_managment();

void confirm_color_selection();

Rectangle *selection_rectangle = new Rectangle(Color(255, 255, 255), 0, 28, 450,
                                               20);
Rectangle *small_selection_rectangle = new Rectangle(Color(255, 255, 255), 0, 30, 140,
                                                     20);
unsigned int selectedIdx = 0; //selected index for listboxes

std::vector<LightUnit> units;
DisplayHandler &handler = DisplayHandler::getInstance();
Perifery controller = Perifery();
TextBox *unitsTb[10];

TextBox *r_value = new TextBox(20, 50, 200, 200, Color(255, 255, 255));
TextBox *g_value = new TextBox(109, 50, 200, 200, Color(255, 255, 255));
TextBox *b_value = new TextBox(199, 50, 200, 200, Color(255, 255, 255));

unsigned char r = 0, g = 0, b = 0;

//changing colors view:
Rectangle *view_rectangle = new Rectangle(Color(r, g, b), 0, 250, 450,
                                          20);
LightUnit *examined_unit = NULL;

enum SCREEN {
    HOME,
    UNIT_SCREEN,
    UNIT_MANAGMENT_SCREEN,
    COLOR_MANAGMENT
};

SCREEN currentScreen = HOME;

enum SETUP_MODE {
    WALL,
    CEIL
};

SETUP_MODE manage_color_mode = WALL;

void scroll_unit_list(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0 || units.size() == 0) return;

    switch (a) {
        case LEFT:
            selectedIdx--;
            selectedIdx %= units.size();
            break;
        case RIGHT:
            selectedIdx++;
            selectedIdx %= units.size();
            break;
    }
    selection_rectangle->setY_(28 + selectedIdx * 20);
    selection_rectangle->setY2_(selection_rectangle->getY_() + 20);
    handler.Refresh();
}

void unit_management_screen(SETUP_MODE mode) {
    currentScreen = UNIT_SCREEN;
    controller.Clear_R_Callbacks();
    controller.Clear_G_Callbacks();
    controller.Clear_B_Callbacks();
    controller.Clear_G_Pressed_Callbacks();

    controller.Register_R_Callback(scroll_red_value, "scroll_attribute_list");
    controller.Register_G_Callback(scroll_green_value, "scroll_attribute_list");
    controller.Register_B_Callback(scroll_blue_value, "scroll_attribute_list");

    handler.clearDisplay();
    Color light_green = Color(152, 251, 152);
    TextBox *unitName_text = new TextBox(1, 1, 200, 200, light_green);
    unitName_text->setText_(examined_unit->getLabel_());
    handler.addShape(unitName_text);

    TextBox *color_text = new TextBox(1, 230, 200, 200, Color(255, 255, 255));
    color_text->setText_("Color: ");
    TextBox *changingName_text = new TextBox(1, 20, 200, 200, light_green);

    TextBox *r_text = new TextBox(1, 50, 200, 200, Color(255, 0, 0));
    r_text->setText_("R: ");
    handler.addShape(r_text);


    TextBox *g_text = new TextBox(90, 50, 200, 200, Color(0, 255, 0));
    g_text->setText_("G: ");
    handler.addShape(g_text);


    TextBox *b_text = new TextBox(180, 50, 200, 200, Color(0, 0, 255));
    b_text->setText_("B: ");
    handler.addShape(b_text);


    stringstream streamr;
    stringstream streamg;
    stringstream streamb;

    switch (mode) {
        case WALL:
            changingName_text->setText_("Wall:");
            r = (unsigned char) examined_unit->getWall_().getRGB888().r;
            g = (unsigned char) examined_unit->getWall_().getRGB888().g;
            b = (unsigned char) examined_unit->getWall_().getRGB888().b;

            streamr << examined_unit->getWall_().getRGB888().r;
            streamg << examined_unit->getWall_().getRGB888().g;
            streamb << examined_unit->getWall_().getRGB888().b;

            controller.Register_G_Pressed_Callback(confirm_wall_managment, "confirm_wall_managment");
            break;
        case CEIL:
            changingName_text->setText_("Ceil:");

            r = (unsigned char) examined_unit->getCeil_().getRGB888().r;
            g = (unsigned char) examined_unit->getCeil_().getRGB888().g;
            b = (unsigned char) examined_unit->getCeil_().getRGB888().b;

            streamr << examined_unit->getCeil_().getRGB888().r;
            streamg << examined_unit->getCeil_().getRGB888().g;
            streamb << examined_unit->getCeil_().getRGB888().b;

            controller.Register_G_Pressed_Callback(confirm_ceil_managment, "confirm_ceil_managment");
            break;
    }
    r_value->setText_(streamr.str());
    g_value->setText_(streamg.str());
    b_value->setText_(streamb.str());
    handler.addShape(changingName_text);
    // handler.addShape(color_text);
    handler.addShape(r_value);
    handler.addShape(g_value);
    handler.addShape(b_value);
    /* *view_rectangle = Rectangle(Color(r, g, b), 0, 250, 450,
                                 20);
     handler.addShape(view_rectangle);*/
    handler.Refresh();
}

void unit_screen() {
    currentScreen = UNIT_SCREEN;
    handler.clearDisplay();
    examined_unit = &units[selectedIdx];

    controller.Clear_R_Callbacks();
    controller.Clear_G_Callbacks();
    controller.Clear_B_Callbacks();
    controller.Clear_G_Pressed_Callbacks();

    controller.Register_R_Callback(scroll_attribute_list, "scroll_attribute_list");
    controller.Register_G_Callback(scroll_attribute_list, "scroll_attribute_list");
    controller.Register_B_Callback(scroll_attribute_list, "scroll_attribute_list");

    controller.Register_G_Pressed_Callback(go_manage, "greenclick");

    Color light_green = Color(152, 251, 152);
    selectedIdx = 0;
    selection_rectangle = new Rectangle(Color(255, 255, 255), 0, 50, 450,
                                        20);
    handler.addShape(selection_rectangle);

    TextBox *chooseChange_text = new TextBox(1, 1, 200, 200, light_green);
    chooseChange_text->setText_(examined_unit->getLabel_());
    handler.addShape(chooseChange_text);

    TextBox *first_text = new TextBox(1, 30, 200, 200, light_green);
    first_text->setText_("CONFIGURE:");
    handler.addShape(first_text);

    TextBox *wallValue = new TextBox(1, 50, 200, 200, Color(255, 255, 255));
    stringstream stream;
    stream << "Wall color:  R: " << examined_unit->getWall_().getRGB888().r << " G: "
           << examined_unit->getWall_().getRGB888().g << " B: "
           << examined_unit->getWall_().getRGB888().b;
    wallValue->setText_(stream.str());
    handler.addShape(wallValue);

    TextBox *ceilValue = new TextBox(1, 70, 200, 200, Color(255, 255, 255));
    stringstream stream2;
    stream2 << "Ceiling color:  R: " << examined_unit->getCeil_().getRGB888().r << " G: "
            << examined_unit->getCeil_().getRGB888().g
            << " B: "
            << examined_unit->getCeil_().getRGB888().b;
    ceilValue->setText_(stream2.str());
    handler.addShape(ceilValue);

    TextBox *turn_offCeil = new TextBox(1, 90, 200, 200, Color(220, 220, 220));
    turn_offCeil->setText_("TURN OFF WALL");
    handler.addShape(turn_offCeil);

    TextBox *turn_offWall = new TextBox(1, 110, 200, 200, Color(220, 220, 220));
    turn_offWall->setText_("TURN OFF CEILING");
    handler.addShape(turn_offWall);
    handler.Refresh();

    TextBox *turn_onWall = new TextBox(1, 130, 200, 200, Color(150, 150, 150));
    turn_onWall->setText_("TURN ON WALL (select from 16 colors)");
    handler.addShape(turn_onWall);

    TextBox *turn_onCeil = new TextBox(1, 150, 200, 200, Color(150, 150, 150));
    turn_onCeil->setText_("TURN ON CEILING (select from 16 colors)");
    handler.addShape(turn_onCeil);
    handler.Refresh();
}

void color_management_screen(SETUP_MODE mode) {
    currentScreen = COLOR_MANAGMENT;
    manage_color_mode = mode;
    selectedIdx = 0;
    handler.clearDisplay();
    small_selection_rectangle = new Rectangle(Color(255, 255, 255), 0, 30, 140,
                                              20);

    controller.Clear_R_Callbacks();
    controller.Clear_G_Callbacks();
    controller.Clear_B_Callbacks();
    controller.Clear_G_Pressed_Callbacks();

    controller.Register_R_Callback(scroll_manage_color_list, "scroll colors");
    controller.Register_G_Callback(scroll_manage_color_list, "scroll colors");
    controller.Register_B_Callback(scroll_manage_color_list, "scroll colors");

    controller.Register_G_Pressed_Callback(confirm_color_selection, "greenclick");

    TextBox *colorTb[16];
    Color colors_list[] = {Color::black(), Color::white(), Color::red(), Color::lime(), Color::blue(),
                           Color::yellow(), Color::cyan(), Color::magenta(), Color::silver(), Color::gray(),
                           Color::maroon(),
                           Color::olive(), Color::green(), Color::purple(), Color::teal(), Color::navy()};


    for (int i = 0; i < 8; i++) {
        colorTb[i] = new TextBox(1, i * 20 + 30, 200, 200, Color(255, 255, 255));
        colorTb[i]->setText_(colors_list[i].getName_());
        handler.addShape(colorTb[i]);
    }

    for (int i = 8; i < 16; i++) {
        colorTb[i] = new TextBox(160, (i - 8) * 20 + 30, 200, 200, Color(255, 255, 255));
        colorTb[i]->setText_(colors_list[i].getName_());
        handler.addShape(colorTb[i]);
    }
    handler.addShape(small_selection_rectangle);
    handler.Refresh();

}

void home_screen() {
    currentScreen = HOME;
    selectedIdx = 0;
    handler.clearDisplay();

    controller.Clear_R_Callbacks();
    controller.Clear_G_Callbacks();
    controller.Clear_B_Callbacks();
    controller.Clear_G_Pressed_Callbacks();

    controller.Register_R_Callback(scroll_unit_list, "printer");
    controller.Register_G_Callback(scroll_unit_list, "printer");
    controller.Register_B_Callback(scroll_unit_list, "printer");

    controller.Register_R_Pressed_Callback(go_home, "redclick");
    controller.Register_G_Pressed_Callback(select_unit, "greenclick");

    Color stroke = Color(255, 255, 255);
    Color light_green = Color(152, 251, 152);

    selection_rectangle = new Rectangle(Color(255, 255, 255), 0, 28, 450,
                                        20);

    Line *green_line = new Line(0, 16, 115, 16, light_green);
    TextBox *first_text = new TextBox(1, 1, 200, 200, light_green);
    TextBox *use_text1 = new TextBox(1, 280, 200, 200, Color(255, 0, 0));
    TextBox *use_text2 = new TextBox(1, 300, 200, 200, Color(255, 0, 0));
    first_text->setText_("LIGHT CONTROL:");
    use_text1->setText_("Rotate button, select device,");
    use_text2->setText_("press green to confirm, press red to go home.");

    //UNITS LIST
    for (int i = 0; i < units.size(); ++i) {
        //add label
        unitsTb[i] = new TextBox(20, i * 20 + 30, 200, 200, stroke);
        unitsTb[i]->setText_(units[i].debugString());
        handler.addShape((unitsTb[i]));
        //add icon
        Icon *icon = new Icon(2, i * 20 + 30, (uint16_t *) units[i].getIcon());
        handler.addShape(icon);
    }

    handler.addShape(first_text);
    handler.addShape(green_line);
    handler.addShape(selection_rectangle);
    handler.addShape(use_text1);
    handler.addShape(use_text2);
    handler.Refresh();
    controller.update_ceil_led(units[0].getCeil_());
    controller.update_wall_led(units[0].getWall_());
}

void go_home() {
    home_screen();
}

void go_manage() {
    cout << selectedIdx << "\n";
    switch (selectedIdx) {
        case 0: //configure wall
            unit_management_screen(WALL);
            break;
        case 1: //configure ceiling
            unit_management_screen(CEIL);
            break;
        case 2: //turn off wall
            r = 0;
            g = 0;
            b = 0;
            confirm_wall_managment();
            break;
        case 3: //turn off ceil
            r = 0;
            g = 0;
            b = 0;
            confirm_ceil_managment();
            break;
        case 4: //choose color of wall
            color_management_screen(WALL);
            break;
        case 5: //choose color of ceiling
            color_management_screen(CEIL);
            break;
    }
}

void select_unit() {
    unit_screen();
}

void scroll_attribute_list(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0 || units.size() == 0) return;

    switch (a) {
        case LEFT:
            selectedIdx--;
            selectedIdx %= 6;
            break;
        case RIGHT:
            selectedIdx++;
            selectedIdx %= 6;
            break;
    }

    selection_rectangle->setY_(50 + selectedIdx * 20);
    selection_rectangle->setY2_(selection_rectangle->getY_() + 20);
    handler.Refresh();
}

void scroll_manage_color_list(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0 || units.size() == 0) return;

    switch (a) {
        case LEFT:
            selectedIdx--;
            selectedIdx %= 16;
            break;
        case RIGHT:
            selectedIdx++;
            selectedIdx %= 16;
            break;
    }

    if (selectedIdx < 8) {
        small_selection_rectangle->setX_(0);
        small_selection_rectangle->setX2_(140);
        small_selection_rectangle->setY_(30 + selectedIdx * 20);
        small_selection_rectangle->setY2_(small_selection_rectangle->getY_() + 20);
    } else {
        small_selection_rectangle->setX_(159);
        small_selection_rectangle->setX2_(300);
        small_selection_rectangle->setY_(30 + (selectedIdx - 8) * 20);
        small_selection_rectangle->setY2_(small_selection_rectangle->getY_() + 20);
    }
    handler.Refresh();
}

void scroll_red_value(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0) return;
    switch (a) {
        case LEFT:
            r -= STEP;
            break;
        case RIGHT:
            r += STEP;
            break;
    }
    update_textboxes();
}

void scroll_green_value(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0) return;
    switch (a) {
        case LEFT:
            g -= STEP;
            break;
        case RIGHT:
            g += STEP;
            break;
    }
    update_textboxes();
}

void scroll_blue_value(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0) return;
    switch (a) {
        case LEFT:
            b -= STEP;
            break;
        case RIGHT:
            b += STEP;
            break;
    }
    update_textboxes();
}

void update_textboxes() {
    stringstream streamr;
    stringstream streamg;
    stringstream streamb;

    streamr << (int) r;
    streamg << (int) g;
    streamb << (int) b;

    r_value->setText_(streamr.str());
    g_value->setText_(streamg.str());
    b_value->setText_(streamb.str());
    *view_rectangle = Rectangle(Color(r, g, b), 0, 250, 450,
                                20);
    handler.Refresh();
}

void update_examined() {
    if (!examined_unit->isIsHost_()) {
        cout << "Updating " << examined_unit->debugString() << "\n";
        Updater updater = Updater(*examined_unit);
        updater.sendUpdate();
        cout << "Update send.\n";
    }
    examined_unit = NULL;
    home_screen();
}

void confirm_wall_managment() {
    examined_unit->setWall_(Color(r, g, b));
    update_examined();
    examined_unit = NULL;
    home_screen();
}

void confirm_ceil_managment() {
    examined_unit->setCeil_(Color(r, g, b));
    update_examined();

    examined_unit = NULL;
    home_screen();
}

void confirm_color_selection() {
    Color colors_list2[] = {Color::black(), Color::white(), Color::red(), Color::lime(), Color::blue(),
                            Color::yellow(), Color::cyan(), Color::magenta(), Color::silver(), Color::gray(),
                            Color::maroon(),
                            Color::olive(), Color::green(), Color::purple().Color::teal(), Color::navy()};
    if (manage_color_mode == WALL) {
        examined_unit->setWall_(colors_list2[selectedIdx]);
    } else if (manage_color_mode == CEIL) {
        examined_unit->setCeil_(colors_list2[selectedIdx]);
    }
    update_examined();
    examined_unit = NULL;
    home_screen();
};

void *broadcast_loop(void *) {
    while (true) {
        // child process
        if (units.size() > 0) {
            Broadcaster::getInstance().broadcastData(units[0]);
        }
        sleep(BROADCAST_DELAY);
    }
    return NULL;
}

void statusUpdate(StateMessage message) {
    bool found = false;

    //Seek list
    for (int i = 0; i < units.size(); ++i) {
        //update existing - ignore host, self update
        if (i != 0)
            if (units[i].getALC1_() == message.getUnit_().getALC1_()) {
                cout << "Received " << message.getUnit_().broadcstDebugString() << "\n";
                units[i].Update(message.getUnit_());
                cout << "Updating: " << message.getUnit_().getLabel_() << "\n";
                units[i].resetIdle();
                found = true;
                break;
            }
    }

    bool newAdded = false;
    //add if not host
    if (!found && units[0].getALC1_() != message.getUnit_().getALC1_()) {
        //not found - add new
        cout << "Received " << message.getUnit_().broadcstDebugString() << "\n";
        units.push_back(message.getUnit_());
        cout << "Adding to list: " << message.getUnit_().getLabel_() << "\n";
        newAdded = true;
    }

    bool deleted = false;
    //increase idles . remove idle units - ignore host
    for (int i = 0; i < units.size(); ++i)
        if (i != 0) {
            units[i].incrementIdle();
            if (units[i].isIdle()) {
                units.erase(units.begin() + i);
                deleted = true;
            }
        }

    //refresh list
    if (currentScreen == HOME && units.size() > 1 && (deleted || newAdded))
        home_screen();
}

void recvError() {
    cout << "Invalid message received...\n";
}

void nodeUpdate(UpdateMessage message) {
    //RESOLVE UPDATE
    cout << "Update received for: " << message.getUnit_().broadcstDebugString() << "\n";
    if (units[0].getALC1_() == message.getUnit_().getALC1_()) {
        units[0].Update(message.getUnit_());
        controller.update_ceil_led(units[0].getCeil_());
        controller.update_wall_led(units[0].getWall_());
        cout << "Host updated\n";
    } else {
        cout << "Update denied\n";
    }

}

void *listen(void *) {
    Listener listener = Listener(statusUpdate, recvError, nodeUpdate);
    listener.startListening();
}

int main(int argc, char *argv[]) {
    LightUnit host = LightUnit(NetTools::getMyIp(), "new host room");
    host.setCeil_(Color(100, 200, 30));
    host.setWall_(Color(10, 20, 30));
    host.setIsHost_(true);

    units.push_back(host);

    home_screen();

    //Broadcast thread
    pthread_t t1;
    pthread_create(&t1, NULL, &broadcast_loop, NULL);

    //listening thread
    pthread_t t2;
    pthread_create(&t2, NULL, &listen, NULL);


    controller.Init();

    char *b;
    pthread_join(t1, (void **) &b);
    pthread_join(t2, (void **) &b);
    return 0;
}
