#ifndef SRC_BREAKOUT_PADDLER_H_
#define SRC_BREAKOUT_PADDLER_H_

#include <iostream>
#include "../engine/mesh.h"
#include "../engine/window.h"
#include "../engine/event.h"
#include "../engine/object.h"

namespace Breakout {

    class Paddler : public Object {

    public:
        inline Paddler (Window &window) : Object(
            { 0.0, -0.95, 4.0 },
            true,
            new Rectangle2D({ -0.2, 0.0, 0.0 }, 0.4, 0.05),
            new Rectangle2D({ -0.2, 0.0, 0.0 }, 0.4, 0.05),
            new BackgroundColor(Color::rgba(255, 255, 255, 1.0))
        ) {
            window.eraseEvent<Event::MouseMove>("mousemove.paddler");
            window.event<Event::MouseMove>([this] (GLFWwindow *window, double _x, double _y, double posx, double _posy) mutable {
                if (posx > 1.0) {
                    posx = 1.0;
                } else if (posx <= -1.0) {
                    posx = -1.0;
                }
                this->setSpeed({ posx * 0.02, 0.0, 0.0 });
            }, "mousemove.paddler");
        }

        void afterUpdate (double now, unsigned tick) {

            std::valarray<double> position = this->getPosition();
            double border = 1.0 - (static_cast<const Rectangle2D *>(this->getMesh())->getWidth() / 2.0);

            if (position[0] <= -border) {
                position[0] = -border;
                this->setSpeed({ 0.0, 0.0, 0.0 });
            } else if (position[0] >= border) {
                position[0] = border;
                this->setSpeed({ 0.0, 0.0, 0.0 });
            }

            this->setPosition(position);
        }

        virtual inline std::string getType () const { return "breakout_paddler"; }

    };

};

#endif