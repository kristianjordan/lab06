#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>
#include <vector>
class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
	if (sheet != nullptr)
        	column = sheet->get_column_by_name(name);
    }
	
    virtual int getColumn()
    {
        return column;
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Composite : public Select_Column
{
protected:
    std::vector<Select_Column*> selectPtr;

public:
    ~Select_Composite()
    {
        for (int i = 0; i < selectPtr.size(); i ++)
        {
            delete selectPtr[i];
        }	
    }
    Select_Composite(Select_Column* p1, Select_Column* p2) : Select_Column(nullptr, "")
    {
        selectPtr.push_back(p1);
        selectPtr.push_back(p2);
    }
    virtual bool select(const std::string& s) const
    {
        return true;
    }

    // virtual function that children must implement
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};


class Select_Contains : public Select_Column
{
protected:
    std::string isString;
public:
    Select_Contains(Spreadsheet* sheet, const std::string& columnName, const std::string& search) : Select_Column(sheet, columnName)
    {
        isString = search;
    }

    bool select(const std::string& s) const
    {
        return strstr(s.c_str(), isString.c_str()) != nullptr;
    }
};

class Select_Not : public Select_Column
{
private:
    Select_Column* hasNot;
public:
    ~Select_Not()
    {
        delete hasNot;
    }
    Select_Not(Select_Column* s) : Select_Column(nullptr,"")
    {
        hasNot = s;
    }

    bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, hasNot->getColumn()));
    }

    bool select(const std::string& s) const
    {
        return !(hasNot->select(s));
    }
};


class Select_And : public Select_Composite
{
public:
    Select_And(Select_Column* s1, Select_Column* s2) : Select_Composite(s1, s2){}
    bool select(const Spreadsheet* sheet, int row) const
    {
        bool result = true;
        for (Select_Column* select : selectPtr)
            result = result && select->select(sheet,row);
        return result;
    }
};

class Select_Or : public Select_Composite
{
public:
    Select_Or(Select_Column* s1, Select_Column* s2) : Select_Composite(s1, s2){}
    bool select(const Spreadsheet* sheet, int row) const
    {
        bool result = false;
        for (Select_Column* select : selectPtr)
            result = result || select->select(sheet,row);
        return result;
    }
};


#endif //__SELECT_HPP__
