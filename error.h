#ifndef ERROR_H
#define ERROR_H

struct dataType
{
    string name;
    double value;
    float absERR;
    float relERR;
    bool rules;
    dataType *link;
};

class Error
{
private:
    dataType *anchor;
    dataType *end;
public:
    Error();
    void addEntry(string,double,bool);
    void propRules(dataType*);
    float calcAbsERR(double,float);
    float calcRelERR(double,float);
    float calcERR(float,float);
    void deleteEntry();
    void displayTable();
    void exportTable();
};

#endif
