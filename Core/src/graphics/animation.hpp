#ifndef ANIMATION_H
#define ANIMATION_H

struct Animation {
    int start;
    int end;
    int fallback;
    int speed; //NOTE: in fps or in ms?

    Animation(int start, int end, int fallback = -1)
    : start(start), end(end), fallback(fallback) { }

};

#endif /* end of include guard: ANIMATION_H */
