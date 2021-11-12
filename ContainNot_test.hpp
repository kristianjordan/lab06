#ifndef __CONTAINNOT_TEST_HPP__
#define __CONTAINNOT_TEST_HPP__

#include "spreadsheet.hpp"
#include "select.hpp"
#include "gtest/gtest.h"

using namespace std;

TEST(ContainTest, HasStringTrue){
	Spreadsheet* sheet = new Spreadsheet();
	sheet->set_column_names({"First","Last","Age","Major"});
        sheet->add_row({"Amanda","Andrews","22","business"});
        sheet->add_row({"Brian","Becker","21","computer science"});
	Select* select = new Select_Contains(sheet,"First","Amanda");
	sheet->set_selection(select);
	EXPECT_TRUE(select->select(sheet,0));
	delete sheet;

}


TEST(ContainTest, HasStringFalse){
        Spreadsheet* sheet = new Spreadsheet();
        sheet->set_column_names({"First","Last","Age","Major"});
        sheet->add_row({"Amanda","Andrews","22","business"});
        sheet->add_row({"Brian","Becker","21","computer science"});
        Select* select = new Select_Contains(sheet,"First","Banana");
        sheet->set_selection(select);
        EXPECT_FALSE(select->select(sheet,0));
	delete sheet;
}

TEST(ContainTest, HasLetterTrue){
        Spreadsheet* sheet = new Spreadsheet();
        sheet->set_column_names({"First","Last","Age","Major"});
        sheet->add_row({"Amanda","Andrews","22","business"});
        sheet->add_row({"Brian","Becker","21","computer science"});
        Select* select = new Select_Contains(sheet,"First","a");
        sheet->set_selection(select);
        EXPECT_TRUE(select->select(sheet,0));
	delete sheet;
}

TEST(ContainTest, HasLetterFalse){
        Spreadsheet* sheet = new Spreadsheet();
        sheet->set_column_names({"First","Last","Age","Major"});
        sheet->add_row({"Amanda","Andrews","22","business"});
        sheet->add_row({"Brian","Becker","21","computer science"});
        Select* select = new Select_Contains(sheet,"First","z");
        sheet->set_selection(select);
        EXPECT_FALSE(select->select(sheet,0));
	delete sheet;
}

TEST(NotTest, WithoutString){
        Spreadsheet* sheet = new Spreadsheet();
        sheet->set_column_names({"First","Last","Age","Major"});
        sheet->add_row({"Amanda","Andrews","22","business"});
        sheet->add_row({"Brian","Becker","21","computer science"});
        Select* select = new Select_Not(new Select_Contains(sheet,"First","Joseph"));
        sheet->set_selection(select);
        EXPECT_TRUE(select->select(sheet,0));
	delete sheet;
}

TEST(NotTest, WithString){
        Spreadsheet* sheet = new Spreadsheet();
        sheet->set_column_names({"First","Last","Age","Major"});
        sheet->add_row({"Amanda","Andrews","22","business"});
        sheet->add_row({"Brian","Becker","21","computer science"});
        Select* select = new Select_Not(new Select_Contains(sheet,"First","Amanda"));
        sheet->set_selection(select);
        EXPECT_FALSE(select->select(sheet,0));
	delete sheet;
}

TEST(NotTest, WithoutChar){
        Spreadsheet* sheet = new Spreadsheet();
        sheet->set_column_names({"First","Last","Age","Major"});
        sheet->add_row({"Amanda","Andrews","22","business"});
        sheet->add_row({"Brian","Becker","21","computer science"});
        Select* select = new Select_Not(new Select_Contains(sheet,"First","z"));
        sheet->set_selection(select);
        EXPECT_TRUE(select->select(sheet,0));
	delete sheet;	
}

TEST(NotTest, WithChar){
        Spreadsheet* sheet = new Spreadsheet();
        sheet->set_column_names({"First","Last","Age","Major"});
        sheet->add_row({"Amanda","Andrews","22","business"});
        sheet->add_row({"Brian","Becker","21","computer science"});
        Select* select = new Select_Not(new Select_Contains(sheet,"First","a"));
        sheet->set_selection(select);
        EXPECT_FALSE(select->select(sheet,0));
	delete sheet;	
}





#endif
