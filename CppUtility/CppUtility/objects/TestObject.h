#pragma once

class BaseObject {
public:
    virtual int CalculateTruth() = 0;
    virtual ~BaseObject() {};
protected:
    long long large = 2;
    double    decimal = 3.14;
    bool      truth = false;
};

class ComplicatedObject : public BaseObject {
public:
    int CalculateTruth() override {
        if (truth) {
            return static_cast<int>(large * decimal);
        }
        else {
            return static_cast<int>(-1.0 * large * decimal);
        }
    }
};
