#ifndef WHEEL_H
#define WHEEL_H

class Wheel {
public:
  int spin();

private:
  int wheel[16]{-1,  0,   100,  200,  100,  200,  100,  200,
                500, 500, 1000, 1000, 1500, 2000, 3000, 5000};
};

#endif