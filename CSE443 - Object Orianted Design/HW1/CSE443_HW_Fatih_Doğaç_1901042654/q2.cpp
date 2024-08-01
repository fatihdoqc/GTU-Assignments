#include <iostream>

class Implementor{
    public:
        virtual void play() = 0;
}

class playImplementor: public Implementor{
    public:
        void play(){
            // play code
        }
}

class Media{

    Implementor playImpl;
};

class Auido : public Media{
};

class Video : public Media{
};

class Speakers : public Media{
};

class Headphones : public Media{
};

int main(){
    Audio a;
    a.playImpl.play();
}

