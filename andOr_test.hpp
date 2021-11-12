#ifndef __ADDOR_TEST_HPP__
#define __ADDOR_TEST_HPP__

#include "spreadsheet.hpp"
#include "select.hpp"
#include "gtest/gtest.h"
using namespace std;

class Select_Test : public Select_Column
{
private:
	bool result;
public:
	Select_Test (bool r) : Select_Column(nullptr, "")
	{
		result = r;
	}

	bool select(const Spreadsheet* sheet, int row) const
	{
		return result;
	}

	virtual bool select(const std::string& s) const
	{
		return result;
	}

};


/*
 *  * testing And cases
 *  * can either be TT TF FT FF
*/

TEST(AndTest, AndTrueTrueTest)
{
	Select_And * select = new Select_And(new Select_Test(true), new Select_Test(true));
	EXPECT_EQ(select->select(nullptr,0),  true);
	
	// deallocation
        delete select;
}

TEST(AndTest, AndTrueFalseTest)
{
        Select_And * select = new Select_And(new Select_Test(true), new Select_Test(false));
        EXPECT_EQ(select->select(nullptr,0),  false);

	// deallocation
        delete select;
}

TEST(AndTest, AndFalseTrueTest)
{
        Select_And * select = new Select_And(new Select_Test(false), new Select_Test(true));
        EXPECT_EQ(select->select(nullptr,0),  false);

	// deallocation
        delete select;
}


TEST(AndTest, AndFalseFalseTest)
{
        Select_And * select = new Select_And(new Select_Test(false), new Select_Test(false));
        EXPECT_EQ(select->select(nullptr,0),  false);

	// deallocation
        delete select;
}



/*
 * testing Or cases
 * can either be TT TF FT FF
*/
TEST(OrTest, OrTrueTrueTest)
{
        Select_Or * select = new Select_Or(new Select_Test(true), new Select_Test(true));
        EXPECT_EQ(select->select(nullptr,0),  true);

	// deallocation
        delete select;

}

TEST(OrTest, OrTrueFalseTest)
{
        Select_Or * select = new Select_Or(new Select_Test(true), new Select_Test(false));
        EXPECT_EQ(select->select(nullptr,0),  true);

	// deallocation
        delete select;

}

TEST(OrTest, OrFalseTrueTest)
{
        Select_Or * select = new Select_Or(new Select_Test(false), new Select_Test(true));
        EXPECT_EQ(select->select(nullptr,0),  true);

	// deallocation
	delete select;
	
}

TEST(OrTest, OrFalseFalseTest)
{
        Select_Or * select = new Select_Or(new Select_Test(false), new Select_Test(false));
        EXPECT_EQ(select->select(nullptr,0),  false);

	// deallocation
	delete select;
}

#endif // __ADDOR_TEST_HPP__

