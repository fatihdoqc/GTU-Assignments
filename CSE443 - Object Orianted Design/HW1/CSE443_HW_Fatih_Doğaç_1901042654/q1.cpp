#include <iostream>

class Media{
    public:
        // Constructors
        virtual void accept(Visitor* ) = 0;
        
};

class Auido : public Media{
    public:
        void accept(Visitor* v){
            v.visit(*this);
        }
};

class Video : public Media{
    public:
        void accept(Visitor* v){
            v.visit(*this);
        }
};

class Visitor{
    public:
        virtual void visit(Audio* ) = 0;
        virtual void visit(Video* ) = 0;
};

class playVisitor : public Visitor{

    public:
        void visit(Audio* a){
            // play function for Audio
        }

        void visit(Video* a){
            // play function for Video
        }
};

class filterVisitor : public Visitor{

    public:
        void visit(Audio* a){
            // filter function for Audio
        }

        void visit(Video* a){
            // filter function for Video
        }
};

class exportVisitor : public Visitor{

    public:
        void visit(Audio* a){
            // export function for Audio
        }

        void visit(Video* a){
            // export function for Video
        }
};