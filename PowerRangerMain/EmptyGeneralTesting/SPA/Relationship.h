#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <string>

class Relationship
{
    private:
        std::string relName;
        std::string token1;
        std::string token2;

    public:
        enum RelType{FOLLOWS, FOLLOWSSTAR, PARENT, PARENTSTAR};

        Relationship(std::string, std::string, std::string);

        RelType getRelType();
        std::string getToken1();
        std::string getToken2();
};

#endif // RELATIONSHIP_H_INCLUDED